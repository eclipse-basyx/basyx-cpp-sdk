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
 * socket_windows.cpp
 *
 *  Created on: 06.11.2018
 *      Author: schnicke
 */

#include <BaSyx/abstraction/impl/acceptor_impl.h>
#include <BaSyx/abstraction/impl/socket_impl.h>

#include <BaSyx/util/util.h>

#include <cstring>
#include <iostream>
#include <unistd.h>

namespace basyx {
namespace net {
    namespace impl {

        acceptor_impl::~acceptor_impl()
        {
            if(this->socketDesc != 0) {
                this->shutdown(SHUTDOWN_RDWR);
                this->close();
            };
        }

        int acceptor_impl::listen(std::string const& port)
        {
            struct addrinfo *result = NULL, hints;
            int iResult;

            memset(&hints, 0, sizeof(hints));

            hints.ai_family = AF_INET; // Internet address family is unspecified so that either an IPv6 or IPv4 address can be returned
            hints.ai_socktype = SOCK_STREAM; // Requests the socket type to be a stream socket for the TCP protocol
            hints.ai_protocol = IPPROTO_TCP;
            hints.ai_flags = AI_PASSIVE;

            // Resolve the local address and port to be used by the server
            iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
            if (iResult != 0) {
                log.error("getaddrinfo() failed! Error code: {}", iResult);
                return -1;
            }

            // Create a SOCKET for the server to listen for client connections
            socketDesc = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

            if (socketDesc < 0) {
                log.error("socket() failed! Error code: {}", iResult);
                freeaddrinfo(result);
                return -1;
            }

            int reuse = 1;
            iResult = setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));

            if (iResult < 0) {
                log.error("setsockopt() failed! Error code: {}", iResult);
                freeaddrinfo(result);
                ::close(socketDesc);
                return -1;
            }

            // Setup the TCP listening socket
            // bind the socket with the IP address and the port number.  In a way it is like the connect() function (the parameters are the same)
            iResult = bind(socketDesc, result->ai_addr, (int)result->ai_addrlen);

            if (iResult < 0) {
                log.error("bind() failed! Error code: {}", iResult);
                freeaddrinfo(result);
                ::close(socketDesc);
                return -1;
            }

            freeaddrinfo(result);

            // To listen on a socket
            // starts listening to allow clients to connect.
            if (::listen(socketDesc, SOMAXCONN) < 0) {
                log.error("listen() failed! Error code: {}", iResult);
                ::close(socketDesc);
                return -1;
            }

            return 0;
        }

        std::unique_ptr<socket_impl> acceptor_impl::accept()
        {

            native_socket_type clientSock = ::accept(this->socketDesc, NULL, NULL);
            if (clientSock < 0) {
                log.warn("accept() failed!");
                return nullptr;
            } else {
                return util::make_unique<socket_impl>(clientSock);
            }
        }

        int acceptor_impl::shutdown(enum SocketShutdownDir how)
        {
            if (::shutdown(this->socketDesc, how) < 0) {
                log.error("shutdown() failed!");
                return -1;
            }
            return 0;
        }

        int acceptor_impl::close()
        {
            if (::close(this->socketDesc) < 0) {
                log.error("close() failed!");
                return -1;
            }
            this->socketDesc = 0;
            return 0;
        }

        int acceptor_impl::getErrorCode()
        {
            return errno;
        }

    }

}
}
