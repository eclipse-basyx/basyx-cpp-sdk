/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_ABSTRACTION_NET_SOCKET_H
#define BASYX_ABSTRACTION_NET_SOCKET_H

#include <BaSyx/abstraction/impl/socket_impl.h>

#include <BaSyx/util/util.h>

#include <BaSyx/log/log.h>

#include <string>

namespace basyx {
namespace net {
namespace tcp {

template <typename socket_impl>
class basic_socket {
private:
    basyx::log log;
    std::unique_ptr<socket_impl> socket;

    basic_socket<socket_impl>& _move_socket(basic_socket<socket_impl>&& other)
    {
        // close current socket and assign new one
        if (this->socket != nullptr)
            this->socket->close();

        this->socket = std::move(other.socket);
        // other no longer represents a socket connection
        other.socket.reset(nullptr);
        return *this;
    }

public:
    basic_socket()
        : socket { nullptr }
        , log { "Socket" } {};

    basic_socket(std::unique_ptr<socket_impl> socket)
        : socket { std::forward<std::unique_ptr<socket_impl>>(socket) }
        , log { "Socket" } {};

    ~basic_socket() {};

    // Delete copy-assignment and constructor, there should only ever be one Socket object representing a single connection
    basic_socket<socket_impl>& operator=(basic_socket<socket_impl>& other) = delete;
    basic_socket(basic_socket<socket_impl>& other) = delete;

    // Allow move-operations
    basic_socket<socket_impl>& operator=(basic_socket<socket_impl>&& other) { return _move_socket(std::forward<basic_socket<socket_impl>>(other)); };
    basic_socket(basic_socket<socket_impl>&& other) { _move_socket(std::forward<basic_socket<socket_impl>>(other)); };

    template <typename Buffer>
    std::size_t Send(Buffer&& buffer)
    {
        if (socket == nullptr)
            return 0;

        return socket->write(buffer.data(), buffer.size());
    }

    template <typename MutableBuffer>
    std::size_t Receive(MutableBuffer&& buffer)
    {
        if (socket == nullptr)
            return 0;

        return socket->recv(buffer.data(), buffer.size(), 0);
    }

    static basic_socket<socket_impl> Connect(const std::string& address, int port)
    {
		std::cout << "[Socket] Entering ctor";
        return basic_socket<socket_impl>::Connect(address, std::to_string(port));
    }

    static basic_socket<socket_impl> Connect(const std::string& address, const std::string& port)
    {
		std::cout << "[Connector] Entering connect";
		auto sock_impl = util::make_unique<socket_impl>();
		std::cout << "[Connector] sock_impl created";
		auto result = sock_impl->connect(address, port);
		std::cout << "[Connector] sock_impl connected";

        if (result != 0)
            return basic_socket<socket_impl> {};

        return basic_socket<socket_impl> { std::forward<std::unique_ptr<socket_impl>>(sock_impl) };
    }

    int GetErrorCode()
    {
        if (this->socket == nullptr)
            return -1;

        return this->socket->getErrorCode();
    }

    void Close()
    {
        if (this->socket != nullptr) {
            log.trace("Closing socket...");

            //this->socket->shutdown(SHUTDOWN_RDWR);
            this->socket->close();
            this->socket.reset();
        }
    }

    bool Healthy()
    {
        if (this->socket == nullptr)
            return false;

        return true;
    }
};

using Socket = basic_socket<basyx::net::impl::socket_impl>;
};
}
}

#endif /* BASYX_ABSTRACTION_NET_SOCKET_H */
