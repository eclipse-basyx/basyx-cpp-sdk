/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_ABSTRACTION_IMPL_SOCKET_IMPL_H
#define BASYX_ABSTRACTION_IMPL_SOCKET_IMPL_H

#include <BaSyx/abstraction/impl/system_net_types.h>

#include <string>

#include <BaSyx/log/log.h>


namespace basyx {
namespace net {
namespace impl {

class socket_impl 
{
private:
    native_socket_type SocketDesc;
    basyx::log log;
public:
    socket_impl();
    
    explicit socket_impl(native_socket_type socket);
    
    ~socket_impl();

public:
    int connect(std::string const&, std::string const&);
    int read(void*, size_t);
    int recv(void*, size_t, int);
    int write(void*, size_t);

    int shutdown(enum SocketShutdownDir how);
    int close();

    int getErrorCode();
};

}
}
}
#endif /* BASYX_ABSTRACTION_IMPL_SOCKET_IMPL_H */
