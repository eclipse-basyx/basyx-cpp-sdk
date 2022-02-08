/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_SERVER_H
#define OPCUA_SERVER_H

#include <thread>
#include <mutex>
#include <BaSyx/util/util.h>
#include <BaSyx/log/log.h>
#include <BaSyx/opcua/server/open62541Server.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
    namespace opcua
    {
        class Server
        {
            static constexpr const char* loggerName = "OPCUAServer";
        public:
            Server() = delete;
            Server(uint16_t t_port) :
                m_port(t_port), m_logger(loggerName), m_namespace(shared::Namespaces::OPCUA_NS_URI) {}
            Server(uint16_t t_port, const std::string& t_namespaceUri) :
                m_port(t_port), m_logger(loggerName), m_namespace(t_namespaceUri) {}

            virtual ~Server();

            void initialize();

            void run();

            void abort();

            void setRootNode(const NodeId& t_nodeId);

            const NodeId& getRootNode() const;

            UA_Server* getUAServer();

            uint16_t addNameSpace(const char* t_namespaceUri);

            int32_t getNamespaceIndexDefault() const;

            int32_t getNamespaceIndex(const std::string & t_namespaceIdentifier) const;

        private:
            std::mutex abortMutex;
            volatile UA_Boolean running = true;

            UA_Server* m_server = nullptr;
            uint16_t m_port;

            NodeId m_rootNode = NodeId::numeric(UA_NS0ID_OBJECTSFOLDER);
            std::string m_namespace;
            basyx::log m_logger;
        };

    }
}

#endif
