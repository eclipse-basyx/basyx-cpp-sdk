/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_ABSTRACTION_NET_ACCEPTOR_H
#define BASYX_ABSTRACTION_NET_ACCEPTOR_H

#include <BaSyx/log/log.h>
#include <memory>

#include <BaSyx/abstraction/net/Socket.h>

namespace basyx {
namespace net {

// Forward declarations
namespace impl {
    class acceptor_impl;
}

namespace tcp {

    class Acceptor {
    private:
        std::unique_ptr<basyx::net::impl::acceptor_impl> acceptor;
        basyx::log log;
        Acceptor& _move_acceptor(Acceptor&& other);

    public:
        explicit Acceptor(int port);
        explicit Acceptor(const std::string& port);

        // Delete copy-assignment and constructor, there should only ever be one Acceptor object representing a single acceptor
        Acceptor(const Acceptor& other) = delete;
        Acceptor& operator=(const Acceptor& other) = delete;

        // Allow move-operations
        Acceptor& operator=(Acceptor&& other);
        Acceptor(Acceptor&& other);

        ~Acceptor();

    public:
        void close();

        // Blockingly wait for connection
        Socket accept();
    };
}

}
}

#endif /* BASYX_ABSTRACTION_NET_ACCEPTOR_H */
