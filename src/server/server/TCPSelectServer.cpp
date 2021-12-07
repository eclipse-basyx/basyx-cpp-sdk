/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
 * TCPSelectServer.cpp
 *
 *      Author: wendel
 */

#include <BaSyx/server/TCPSelectServer.h>
#include <BaSyx/vab/backend//connector/native/frame/Frame.h>
#include <BaSyx/vab/provider/native/frame/BaSyxNativeFrameProcessor.h>
#include <BaSyx/abstraction/net/Buffer.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <chrono>

namespace basyx {
namespace vab {
namespace provider {
namespace native {

TCPSelectServer::TCPSelectServer(core::IModelProvider* backend, int port, int timeout_ms, int listen_backlog)
    : port(port)
    , initialized(false)
    , backend(backend)
    , log("TCPSelectServer")
    , listen_backlog(listen_backlog)
{
    frame_processor = std::unique_ptr<frame::BaSyxNativeFrameProcessor>(new frame::BaSyxNativeFrameProcessor(backend));
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
}

TCPSelectServer::~TCPSelectServer()
{
    this->clean_up();
}

void TCPSelectServer::Init()
{
    int rc, on = 1;
    // create socket to accept incoming connections
    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0) {
        log.error("socket() failed");
        exit(-1);
    }

    // set socket reusable
    int setsocketopt_state = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    if (setsocketopt_state < 0) {
        log.error("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }

    // Set socket to nonblocking state (FIONBIO -> non-blocking io)
    int ioctl_state = ioctl(listen_sd, FIONBIO, (char*)&on);
    if (ioctl_state < 0) {
        log.error("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }

    // bind socket
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    memset(&addr.sin_addr, INADDR_ANY, sizeof(INADDR_ANY));
    //memcpy(&addr.sin_addr, INADDR_ANY, sizeof(INADDR_ANY));
    addr.sin_port = htons(port);

    int bind_state = bind(listen_sd, (struct sockaddr*)&addr, sizeof(addr));
    if (bind_state < 0) {
        log.error("bind() failed");
        close(listen_sd);
        exit(-1);
    }

    int listen_state = listen(listen_sd, listen_backlog);
    if (listen_state < 0) {
        log.error("listen() failed");
        close(listen_sd);
        exit(-1);
    }

    //init master filedescriptor
    FD_ZERO(&master_set);
    max_socket = listen_sd;
    FD_SET(listen_sd, &master_set);

    log.info("Select server initialized. Listen socket-descriptor({})", listen_sd);
    this->initialized = true;
}

int TCPSelectServer::Update()
{
    if (not initialized)
        log.warn("Select server not initialized");

    int rc;
    fd_set working_set;

    // copy filedescriptor
    memcpy(&working_set, &master_set, sizeof(master_set));

    log.info("Waiting on select()...");
    rc = select(max_socket + 1, &working_set, nullptr, nullptr, &timeout);

    // check select state
    if (rc < 0) {
        log.error("select() failed");
        return -1;
    }
    if (rc == 0) {
        log.info("select() timed out.  End program.");
        return -2;
    }

    desc_ready = rc;
    // check which descriptors are readable
    for (int fd = 0; fd <= max_socket && desc_ready > 0; ++fd) {
        // Check readiness of descriptors
        if (FD_ISSET(fd, &working_set)) {
            // decrease number of readable descriptors, if all found stop looking for them
            desc_ready -= 1;

            if (fd == listen_sd)
                this->accept_incoming_connections();
            else //if not listen socket, socket should be readable
            {
                log.info("Descriptor {} is readable", fd);
                close_connection = false;
                this->receive_incoming_data(fd);

                // if connection is closed, clean up
                if (close_connection) {
                    close(fd);
                    log.info("Connection {} closed", fd);
                    FD_CLR(fd, &master_set);
                    if (fd == max_socket) {
                        while (FD_ISSET(max_socket, &master_set) == false) {
                            max_socket -= 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void TCPSelectServer::Close()
{
    this->clean_up();
}

bool TCPSelectServer::isRunning()
{
    log.warn("Not implemented!");
    return false;
}

void TCPSelectServer::clean_up()
{
    for (int i = 0; i <= max_socket; ++i) {
        if (FD_ISSET(i, &master_set)) {
            close(i);
        }
    }
}

void TCPSelectServer::accept_incoming_connections()
{
    log.info("Listening socket is readable");
    int new_sd;
    do {
        // accept incoming connections
        new_sd = accept(listen_sd, nullptr, nullptr);
        if (new_sd < 0) {
            // if not EWOULDBLOCK -> all incomminng connections are accepted
            if (errno != EWOULDBLOCK) {
                log.error("accept() failed");
                end_server = true;
            }
            break;
        }

        log.info("New incoming connection - {}", new_sd);

        // add incoming connections to master read set
        FD_SET(new_sd, &master_set);
        if (new_sd > max_socket) {
            max_socket = new_sd;
        }
    } while (new_sd != -1);
}

void TCPSelectServer::receive_incoming_data(int fd)
{
    do {
        // receive data
        int receive_state = recv(fd, recv_buffer.data(), recv_buffer.size(), 0);
        if (receive_state < 0) {
            log.debug("receive state {}", receive_state);
            if (errno != EWOULDBLOCK) {
                log.error("recv() failed {}", errno);
                close_connection = true;
            }
            break;
        }

        // if 0, client closed connection
        if (receive_state == 0) {
            log.info("Connection closed");
            close_connection = true;
            break;
        }

        int len = receive_state;
        log.info("{} bytes received", len);

        // Determine input frame size and create frame
        auto input_size = *reinterpret_cast<uint32_t*>(recv_buffer.data());
        auto input_frame = connector::native::Frame::read_from_buffer(basyx::net::make_buffer(this->recv_buffer.data() + BASYX_FRAMESIZE_SIZE, input_size));

        // Process frame to obtain output frame
        auto output_frame = frame_processor->processInputFrame(input_frame);

        // Write the output frame to an output buffer
        net::Buffer out_buffer = basyx::net::make_buffer(send_buffer.data() + BASYX_FRAMESIZE_SIZE, default_buffer_size - BASYX_FRAMESIZE_SIZE);
        connector::native::Frame::write_to_buffer(out_buffer, output_frame);

        // Add size of the containing frame to buffer
        auto size_field = reinterpret_cast<uint32_t*>(&send_buffer[0]);
        *size_field = output_frame.size();

        // answer client
        int send_state = send(fd, send_buffer.data(), output_frame.size() + BASYX_FRAMESIZE_SIZE, 0);
        if (send_state < 0)
        {
          log.error("send() failed");
          close_connection = true;
          break;
        }

    } while (true);
}

}
}
}
}
