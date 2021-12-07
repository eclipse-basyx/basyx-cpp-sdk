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

#include <BaSyx/abstraction/impl/socket_impl.h>

#include <iostream>

namespace basyx {
	namespace net {
		namespace impl {

			socket_impl::socket_impl()
				: SocketDesc{ 0 }
				, log{ "SocketImpl" }
			{
			}

			socket_impl::socket_impl(native_socket_type socket)
				: SocketDesc{ socket }
				, log{ "SocketImpl" }
			{
			}

			socket_impl::~socket_impl()
			{
				this->close();
			};

			int socket_impl::connect(std::string const& address, std::string const& port) {
				WSADATA wsaData;

				// Initialize Winsock
				int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
				if (iResult != 0) {
					log.error("WSAStartup() failed: {}", iResult);
					return -1;
				}

				struct addrinfo *result = NULL, *ptr = NULL, hints;

				ZeroMemory(&hints, sizeof(hints));

				hints.ai_family = AF_UNSPEC; //the address family specification. We usually use AF_INET which is for IPv4 format. For IPv6 format you have to use AF_INET6.
				hints.ai_socktype = SOCK_STREAM; //  SOCK_STREAM opens a connection between two distant computers and allows them to communicate: this protocol is called TCP . SOCK_DGRAM, which doesn't open any connection between the computers, but send immediately the message to the ip and port number specified: this protocol is called UDP
				hints.ai_protocol = IPPROTO_TCP; // The protocol to be used. The possible options for the protocol parameter are specific to the address family and socket type specified.

				// Resolve the server address and port
				iResult = getaddrinfo(address.c_str(), port.c_str(), &hints, &result);
				if (iResult != 0) {
					log.error("getaddrinfo() failed: {}", iResult);
					WSACleanup();
					return -1;
				}

				ptr = result;

				// Create a SOCKET for connecting to server
				SocketDesc = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

				if (SocketDesc == INVALID_SOCKET) {
					log.error("socket() failed: {}", WSAGetLastError());
					freeaddrinfo(result);
					WSACleanup();
					return -1;
				}

				// Connect to server
				// 1. server socket, 2. socket address information, 3. size of socket address information ( of the second parameter)
				iResult = ::connect(SocketDesc, ptr->ai_addr, (int)ptr->ai_addrlen);

				if (iResult == SOCKET_ERROR) {
					log.error("connect() failed.");
					closesocket(SocketDesc);
					SocketDesc = INVALID_SOCKET;
					return -1;
				}

				freeaddrinfo(result);

				if (SocketDesc == INVALID_SOCKET) {
					log.error("Unable to connect to server!");
					WSACleanup();
					return -1;
				}

				return 0;

			}



			int socket_impl::read(void* buf, size_t count) {
				return ::recv(this->SocketDesc, reinterpret_cast<char*>(buf), count, 0);
			}

			int socket_impl::recv(void* buf, size_t len, int flags) {
				return ::recv(this->SocketDesc, reinterpret_cast<char*>(buf), len, 0);
			}

			int socket_impl::write(void* buf, size_t count) {
				return ::send(this->SocketDesc, reinterpret_cast<char*>(buf), count, 0);
			}

			int socket_impl::shutdown(enum SocketShutdownDir how) {
				return ::shutdown(this->SocketDesc, how);
			}

			int socket_impl::close() {
				int iResult = this->shutdown(SHUTDOWN_WR);

				if (iResult == SOCKET_ERROR)
				{
					log.warn("socket_impl# shutdown failed: {}", WSAGetLastError());
				}

				closesocket(SocketDesc);
				WSACleanup();

				return 0;
			}

			int socket_impl::getErrorCode() {
				return WSAGetLastError();
			}
		}
	}
}
