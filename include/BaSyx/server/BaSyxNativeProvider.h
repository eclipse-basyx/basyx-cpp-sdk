/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SERVER_BASYXNATIVEPROVIDER_H
#define BASYX_SERVER_BASYXNATIVEPROVIDER_H

#include <BaSyx/shared/types.h>

#include <BaSyx/util/tools/CoderTools.h>

#include <BaSyx/vab/backend/connector/native/frame/Frame.h>
#include <BaSyx/vab/provider/native/frame/BaSyxNativeFrameProcessor.h>

#include <BaSyx/log/log.h>

#include <BaSyx/abstraction/net/Buffer.h>

#include <asio.hpp>

/**
* Provies access based on the basyx native protocol
*/

namespace basyx {
namespace vab {
namespace provider {
namespace native {

class NativeProvider {
private:
    // Connection socket
    asio::ip::tcp::socket& clientSocket;

    // Frame processor
    frame::BaSyxNativeFrameProcessor* frameProcessor;

    // Buffers
    static constexpr std::size_t default_buffer_size = 8192;
    std::array<char, default_buffer_size> recv_buffer;
    std::array<char, default_buffer_size> send_buffer;

    bool closed;
    basyx::log log;

public:
    NativeProvider(asio::ip::tcp::socket& clientSocket,
        frame::BaSyxNativeFrameProcessor* frameProcessor)
        : clientSocket(clientSocket)
        , frameProcessor(frameProcessor)
        , closed(false)
        , log { "NativeProvider" }
    {
    }

    ~NativeProvider()
    {
        // Connection no longer needed, close it
        try {
            if (this->clientSocket.is_open())
                this->clientSocket.close();
        } catch (std::exception& e) {
            log.warn("Exception in closing socket: {}", e.what());
        };
    }

    // Has to be called repeatedly
    void update()
    {
        log.trace("Updating...");
        if (!closed) {
            asio::error_code ec;
            log.trace("Waiting for incoming message");
            auto input_frame = recvFrame(ec);

            if (ec) {
                log.info("Connection closed");
                closed = true;
            } else {
                log.trace("Received frame.");
                log.info("Received: {}", input_frame.getFirstValue());

                auto output_frame = frameProcessor->processInputFrame(input_frame);

                log.info("Sending reply.");

                auto bytes_sent = sendFrame(output_frame);
                if (bytes_sent < 0) {
                    log.error("Sending failed: {}", "ERROR");
                    closed = true;
                }
            }
        }
    }

    bool isClosed()
    {
        return closed;
    }

    std::size_t sendData(char* data, std::size_t size)
    {
        log.debug("Sending {} bytes.", size);
        std::size_t bytes_sent = this->clientSocket.send(asio::buffer(data, size));
        log.debug("Sent {} bytes.", bytes_sent);
        return bytes_sent;
    };

    std::size_t receiveData(char* data, asio::error_code& ec)
    {
        std::size_t bytes_read = this->clientSocket.receive(asio::buffer(recv_buffer.data(), recv_buffer.size()), 0, ec);
        log.debug("Received {} bytes.", bytes_read);
        return bytes_read;
    };

    std::size_t sendFrame(const connector::native::Frame& frame)
    {
		auto buffer_view = basyx::net::make_buffer(send_buffer.data() + BASYX_FRAMESIZE_SIZE, default_buffer_size - BASYX_FRAMESIZE_SIZE);
        connector::native::Frame::write_to_buffer(buffer_view, frame);

        auto size_field = reinterpret_cast<uint32_t*>(&send_buffer[0]);
        *size_field = static_cast<uint32_t>(frame.size());

        return sendData(send_buffer.data(), frame.size() + BASYX_FRAMESIZE_SIZE);
    };

    connector::native::Frame recvFrame(asio::error_code& ec)
    {
        this->receiveData(recv_buffer.data(), ec);
        auto size = *reinterpret_cast<uint32_t*>(recv_buffer.data());
        auto frame = connector::native::Frame::read_from_buffer(
            basyx::net::make_buffer(this->recv_buffer.data() + BASYX_FRAMESIZE_SIZE, size - BASYX_FRAMESIZE_SIZE));

        return frame;
    };
};

};
};
};
};

#endif /* BASYX_SERVER_BASYXNATIVEPROVIDER_H */
