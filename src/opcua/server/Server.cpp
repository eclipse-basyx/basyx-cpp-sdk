/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/server/Server.h>

namespace basyx
{
    namespace opcua
    {
        void Server::initialize()
        {
            UA_StatusCode status;

            m_server = UA_Server_new();
            status = UA_ServerConfig_setMinimal(UA_Server_getConfig(m_server), m_port, nullptr);

            if (UA_STATUSCODE_GOOD != status)
            {
                m_logger.error("Configuraion faulty - Reason" + std::string(UA_StatusCode_name(status)));
                return;
            }

            if (!m_namespace.empty())
            {
                addNameSpace(m_namespace.c_str());
            }

            UA_Server_getConfig(m_server)->verifyRequestTimestamp = UA_RULEHANDLING_ACCEPT;
            m_logger.info("Intitialized");
        }

        void Server::run()
        {
            std::thread serverThread{ [this] {
                UA_StatusCode status = UA_Server_run(m_server, &running);
                }
            };
            serverThread.join();
        }

        Server::~Server()
        {
            if (m_server)
            {
                m_logger.info("Shutting down ...");
                UA_Server_delete(m_server);
                m_logger.debug("Destroyed");
            }
        }

        void Server::abort()
        {
            std::lock_guard<std::mutex> abort(abortMutex);
            running = false;
            m_logger.info("Aborted");
        }

        uint16_t Server::addNameSpace(const char* t_namespaceUri)
        {
            uint16_t nsIdx = UA_Server_addNamespace(m_server, t_namespaceUri);
            m_logger.info("Namespace added : " + std::string(t_namespaceUri) + " -> " + std::to_string(nsIdx));
            return nsIdx;
        }

        UA_Server * Server::getUAServer()
        {
            return m_server;
        }

        int32_t Server::getNamespaceIndexDefault() const
        {
            return getNamespaceIndex(shared::Namespaces::BASYX_NS_URI);
        }

        int32_t Server::getNamespaceIndex(const std::string & t_namespaceIdentifier) const
        {
            size_t ns;

            auto uri = shared::string::UAStringFromStdString(t_namespaceIdentifier);
            auto status = UA_Server_getNamespaceByName(m_server, uri, &ns);
            if (status != UA_STATUSCODE_GOOD)
            {
                return -1;
            }
            return ns;
        }

        void Server::setRootNode(const NodeId & t_nodeId)
        {
            m_rootNode = t_nodeId;
        }

        const NodeId& Server::getRootNode() const
        {
            return m_rootNode;
        }
    }
}