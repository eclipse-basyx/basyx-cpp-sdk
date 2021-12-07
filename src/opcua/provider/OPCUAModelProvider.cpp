/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/provider/OPCUAModelProvider.h>

namespace basyx
{
    namespace opcua
    {
        namespace provider
        {
            template<>
            OPCUAModelProvider<Client>::~OPCUAModelProvider()
            {
                m_connector->disconnect();
            }

            template<>
            OPCUAModelProvider<Server>::~OPCUAModelProvider()
            {
                m_connector->abort();
            }

            template<>
            OPCUAModelProvider<Client>::OPCUAModelProvider(
                const std::string & t_endpoint,
                const std::string & t_namespaceUri,
                const NodeId & t_rootNode,
                bool t_embedTypeMeta)
            {
                m_logger = util::make_unique<basyx::log>(loggerName);

                m_rootNode = t_rootNode;

                m_embedTypeMeta = t_embedTypeMeta;

                m_connector = util::make_unique<basyx::opcua::Client >(t_endpoint, t_namespaceUri);

                m_connector->connect();

                m_connector->setRootNode(t_rootNode);

                m_services = util::make_unique<Services<basyx::opcua::Client>>(*m_connector);

                m_opcaHandler = util::make_unique<OPCUA2VabHandlers<Client>>(*m_connector.get(), t_embedTypeMeta);

                m_vabHandler = util::make_unique<VAB2OPCUAHandlers<Client>>(*m_connector.get(), t_embedTypeMeta);

                TypesMap::define(m_connector->getNamespaceIndex(t_namespaceUri), *m_connector.get());
            }

            template<>
            OPCUAModelProvider<Server>::OPCUAModelProvider(
                const std::string & t_port,
                const std::string & t_namespaceUri,
                const NodeId & t_rootNode,
                bool t_embedTypeMeta)
            {
                m_logger = util::make_unique<basyx::log>(loggerName);

                m_rootNode = t_rootNode;

                m_embedTypeMeta = t_embedTypeMeta;

                m_connector = util::make_unique<basyx::opcua::Server>(std::stoi(t_port));

                m_connector->initialize();

                m_connector->setRootNode(t_rootNode);

                m_services = util::make_unique<Services<basyx::opcua::Server>>(*m_connector);

                m_opcaHandler = util::make_unique<OPCUA2VabHandlers<Server>>(*m_connector.get(), t_embedTypeMeta);

                m_vabHandler = util::make_unique<VAB2OPCUAHandlers<Server>>(*m_connector.get(), t_embedTypeMeta);

                TypesMap::define(m_connector->getNamespaceIndex(t_namespaceUri), *m_connector.get());
            }

            template<>
            OPCUAModelProvider<Client>::OPCUAModelProvider(std::unique_ptr<Client> t_connector)
            {
                m_logger = util::make_unique<basyx::log>(loggerName);

                m_connector = std::move(t_connector);

                m_embedTypeMeta = false;

                m_services = util::make_unique<Services<basyx::opcua::Client>>(*m_connector);

                m_rootNode = m_connector->getRootNode();

                m_opcaHandler = util::make_unique<OPCUA2VabHandlers<Client>>(*t_connector, false);

                m_vabHandler = util::make_unique<VAB2OPCUAHandlers<Client>>(*t_connector, false);

                TypesMap::define(m_connector->getNamespaceIndexDefault(), *t_connector.get());
            }

            template<>
            OPCUAModelProvider<Server>::OPCUAModelProvider(std::unique_ptr<Server> t_connector)
            {
                m_logger = util::make_unique<basyx::log>(loggerName);

                m_connector = std::move(t_connector);

                m_embedTypeMeta = false;

                m_services = util::make_unique<Services<basyx::opcua::Server>>(*m_connector);

                m_rootNode = m_connector->getRootNode();

                m_opcaHandler = util::make_unique<OPCUA2VabHandlers<Server>>(*t_connector, false);

                m_vabHandler = util::make_unique<VAB2OPCUAHandlers<Server>>(*t_connector, false);

                TypesMap::define(m_connector->getNamespaceIndexDefault(), *t_connector.get());
            }

            template<>
            OPCUAModelProvider<Client>::OPCUAModelProvider(std::unique_ptr<Client> t_connector,
                bool t_embedTypeMeta)
            {
                m_logger = util::make_unique<basyx::log>(loggerName);

                m_connector = std::move(t_connector);

                m_embedTypeMeta = t_embedTypeMeta;

                m_services = util::make_unique<Services<basyx::opcua::Client>>(*m_connector);

                m_rootNode = m_connector->getRootNode();

                m_opcaHandler = util::make_unique<OPCUA2VabHandlers<Client>>(*m_connector.get(), t_embedTypeMeta);

                m_vabHandler = util::make_unique<VAB2OPCUAHandlers<Client>>(*m_connector.get(), t_embedTypeMeta);

                TypesMap::define(m_connector->getNamespaceIndexDefault(), *t_connector.get());
            }

            template<>
            OPCUAModelProvider<Server>::OPCUAModelProvider(std::unique_ptr<Server> t_connector,
                bool t_embedTypeMeta)
            {
                m_logger = util::make_unique<basyx::log>(loggerName);

                m_connector = std::move(t_connector);

                m_embedTypeMeta = t_embedTypeMeta;

                m_services = util::make_unique<Services<basyx::opcua::Server>>(*m_connector);

                m_rootNode = m_connector->getRootNode();

                m_opcaHandler = util::make_unique<OPCUA2VabHandlers<Server>>(*m_connector.get(), t_embedTypeMeta);

                m_vabHandler = util::make_unique<VAB2OPCUAHandlers<Server>>(*m_connector.get(), t_embedTypeMeta);

                TypesMap::define(m_connector->getNamespaceIndexDefault(), *t_connector.get());
            }
        }
    }
}
