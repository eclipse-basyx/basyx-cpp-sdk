/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/abstraction/impl/acceptor_impl.h>
#include <BaSyx/abstraction/impl/socket_impl.h>

#include <BaSyx/util/util.h>
#include <BaSyx/log/log.h>

#include <iostream>

namespace basyx {
namespace net {
namespace impl {

    acceptor_impl::~acceptor_impl()
    {
        this->shutdown(SHUTDOWN_RDWR);
        this->close();
    }

    int acceptor_impl::listen(std::string const& port)
    {
        WSADATA wsaData;

        // Initialize Winsock
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            log.trace("WSAStartup failed: {}", iResult);
        }

        struct addrinfo *result = NULL, hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET; // Internet address family is unspecified so that either an IPv6 or IPv4 address can be returned
        hints.ai_socktype = SOCK_STREAM; // Requests the socket type to be a stream socket for the TCP protocol
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the local address and port to be used by the server
        iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
        if (iResult != 0) {
            log.trace("getaddrinfo failed: {}", iResult);
            WSACleanup();
            return -1;
        }

        socketDesc = INVALID_SOCKET;

        // Create a SOCKET for the server to listen for client connections
        socketDesc = socket(result->ai_family, result->ai_socktype,
            result->ai_protocol);

        if (socketDesc == INVALID_SOCKET) {
            log.trace("Error at socket(): {}", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return -1;
        }

        // Setup the TCP listening socket
        //bind the socket with the IP address and the port number.  In a way it is like the connect() function (the parameters are the same)
        iResult = bind(socketDesc, result->ai_addr, (int)result->ai_addrlen);

        if (iResult == SOCKET_ERROR) {
            log.trace("bind() failed: {}", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(socketDesc);
            WSACleanup();
            return -1;
        }

        freeaddrinfo(result);

        // To listen on a socket
        // starts listening to allow clients to connect.
        if (::listen(socketDesc, SOMAXCONN) == SOCKET_ERROR) {
            log.trace("listen() failed: {}", WSAGetLastError());
            closesocket(socketDesc);
            WSACleanup();
            return -1;
        }

        log.info("Listening on port {}", port);

        return 0;
    }

    std::unique_ptr<socket_impl> acceptor_impl::accept()
    {
        native_socket_type clientSock = ::accept(this->socketDesc, NULL, NULL);

        if (clientSock == INVALID_SOCKET) {
            log.trace("accept() failed: {}", WSAGetLastError());
            return nullptr;
        } else {
            return util::make_unique<socket_impl>(clientSock);
        }
    }

    int acceptor_impl::shutdown(enum SocketShutdownDir how)
    {
        return ::shutdown(socketDesc, how);
    }

    int acceptor_impl::close()
    {
        this->shutdown(SHUTDOWN_RDWR);

        if (::closesocket(this->socketDesc) != 0) {
            log.warn("close() failed!");
            return -1;
        }
        this->socketDesc = 0;
        return 0;
    }

    int acceptor_impl::getErrorCode()
    {
        return WSAGetLastError();
    }

}
}
}
