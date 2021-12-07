/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_MODEL_PROVIDER_H
#define OPCUA_MODEL_PROVIDER_H

#include <BaSyx/vab/core/IModelProvider.h>
#include <BaSyx/vab/core/util/VABPath.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/provider/VAB2OPCUAHandlers.h>
#include <BaSyx/opcua/provider/OPCUA2VabHandlers.h>
#include <BaSyx/opcua/provider/OPCUAModelProviderHelpers.h>
#include <BaSyx/opcua/typesmap/TypesMap.h>

namespace basyx
{
    namespace opcua
    {
        namespace provider
        {
            template<typename CONNECTOR_TYPE = basyx::opcua::Client>
            class OPCUAModelProvider : public vab::core::IModelProvider
            {
                static constexpr const char loggerName[] = "basyx::opcua::provider::OPCUAModelProvider";
            private:
                NodeId m_rootNode;
                std::unique_ptr<CONNECTOR_TYPE> m_connector;
                std::unique_ptr<OPCUA2VabHandlers<CONNECTOR_TYPE>> m_opcaHandler;
                std::unique_ptr<VAB2OPCUAHandlers<CONNECTOR_TYPE>> m_vabHandler;
                std::unique_ptr<Services<CONNECTOR_TYPE>> m_services;
                std::unique_ptr<basyx::log> m_logger;
                bool m_embedTypeMeta;

            public:
                OPCUAModelProvider() = default;

                ~OPCUAModelProvider();

                OPCUAModelProvider(const std::string& t_endpoint,
                    const std::string& t_namespaceUri,
                    const NodeId& t_rootNode,
                    bool t_embedTypeMeta);

                OPCUAModelProvider(std::unique_ptr<CONNECTOR_TYPE> t_connector);

                OPCUAModelProvider(std::unique_ptr<CONNECTOR_TYPE> t_connector,
                    bool t_embedTypeMeta);

            public:
                virtual basyx::object getModelPropertyValue(const std::string& t_path) override;
                virtual basyx::object::error setModelPropertyValue(const std::string& path, const basyx::object t_newValue) override;
                virtual basyx::object::error createValue(const std::string& t_path, const basyx::object t_newValue) override;
                virtual basyx::object::error deleteValue(const std::string& t_path, basyx::object t_deletedValue) override;
                virtual basyx::object::error deleteValue(const std::string& t_path) override;
                virtual basyx::object invokeOperation(const std::string& t_path, basyx::object t_parameters) override;
            private:
                BrowsePath getRootBrowsePath() const;
            };

            template<typename CONNECTOR_TYPE>
            constexpr char OPCUAModelProvider<CONNECTOR_TYPE>::loggerName[];

            template<>
            OPCUAModelProvider<Client>::~OPCUAModelProvider();

            template<>
            OPCUAModelProvider<Server>::~OPCUAModelProvider();

            template<>
            OPCUAModelProvider<Client>::OPCUAModelProvider(
                const std::string & t_endpoint,
                const std::string & t_namespaceUri,
                const NodeId & t_rootNode,
                bool t_embedTypeMeta);

            template<>
            OPCUAModelProvider<Server>::OPCUAModelProvider(
                const std::string & t_port,
                const std::string & t_namespaceUri,
                const NodeId & t_rootNode,
                bool t_embedTypeMeta);

            template<>
            OPCUAModelProvider<Client>::OPCUAModelProvider(std::unique_ptr<Client> t_connector);

            template<>
            OPCUAModelProvider<Server>::OPCUAModelProvider(std::unique_ptr<Server> t_connector);

            template<>
            OPCUAModelProvider<Client>::OPCUAModelProvider(std::unique_ptr<Client> t_connector,
                bool t_embedTypeMeta);

            template<>
            OPCUAModelProvider<Server>::OPCUAModelProvider(std::unique_ptr<Server> t_connector,
                bool t_embedTypeMeta);

            template<typename CONNECTOR_TYPE>
            basyx::object OPCUAModelProvider<CONNECTOR_TYPE>::getModelPropertyValue(const std::string & t_path)
            {
                m_logger->trace("GET - Path [" + t_path + "]");

                auto relativeBrowsePath = m_vabHandler->translateVABPathToBrowsePath(t_path, m_connector->getNamespaceIndexDefault());

                auto fullBrowsePath = BrowsePath({ m_services->getBrowseNameFromNodeId(m_rootNode) }) + relativeBrowsePath;

                auto nodeId = m_services->translateBrowsePathToNodeId(fullBrowsePath);

                if (nodeId.isNull())
                {
                    m_logger->error("BrowsePath : [" + t_path + "] OPCUA node cannot be resolved");
                    return basyx::object::make_null();
                }
                return m_opcaHandler->getBasyxObject(nodeId);
            }

            template<typename CONNECTOR_TYPE>
            basyx::object::error OPCUAModelProvider<CONNECTOR_TYPE>::setModelPropertyValue(const std::string & t_path, const basyx::object t_newValue)
            {
                m_logger->trace("SET - Path [" + t_path + "]");

                auto relativeBrowsePath = m_vabHandler->translateVABPathToBrowsePath(t_path, m_connector->getNamespaceIndexDefault());

                auto fullBrowsePath = BrowsePath({ m_services->getBrowseNameFromNodeId(m_rootNode) }) +
                    //BrowsePath(BrowsePath::build({ m_contextName }) + 
                    relativeBrowsePath;

                auto nodeId = m_services->translateBrowsePathToNodeId(fullBrowsePath);

                if (nodeId.isNull())
                {
                    m_logger->error("BrowsePath : [" + t_path + "] OPCUA node cannot be resolved");

                    return basyx::object::error::PropertyNotFound;
                }

                if (m_vabHandler->isNodePrimitive(nodeId) ||
                    (m_embedTypeMeta && TypesTransformer::isTypeEncapsulated(basyx::object(t_newValue))))
                {
                    auto status = m_opcaHandler->writePrimitive(nodeId, t_newValue);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        m_logger->error("BrowsePath : [" + t_path + "] write failed - Reason : " + shared::diag::getErrorString(status));

                        return basyx::object::error::MalformedRequest;
                    }
                    return  basyx::object::error::None;
                }

                auto ret = deleteValue(t_path);

                if (ret != basyx::object::error::None)
                {
                    return ret;
                }

                return createValue(t_path, t_newValue);
            }

            template<typename CONNECTOR_TYPE>
            basyx::object::error OPCUAModelProvider<CONNECTOR_TYPE>::createValue(const std::string & t_path, const basyx::object t_newValue)
            {
                m_logger->trace("CREATE - Path [" + t_path + "]");

                auto relativeBrowsePath = m_vabHandler->translateVABPathToBrowsePath(t_path, m_connector->getNamespaceIndexDefault());

                auto fullBrowsePath = BrowsePath({ m_services->getBrowseNameFromNodeId(m_rootNode) }) + relativeBrowsePath;

                auto nodeId = m_services->translateBrowsePathToNodeId(fullBrowsePath);

                if (!nodeId.isNull())
                {
                    m_logger->error("BrowsePath [" + fullBrowsePath.toString() + "] element already exists in OPCUA server");

                    return basyx::object::error::ObjectAlreadyExists;
                }

                auto parentPath = fullBrowsePath.getParentPath();

                auto parentNodeId = m_services->translateBrowsePathToNodeId(parentPath);

                auto status = m_vabHandler->createObject(parentNodeId, relativeBrowsePath, t_newValue);

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger->error("Node creation failed - BrowsePath [" + fullBrowsePath.toString() + "] : Reason - " +
                        shared::diag::getErrorString(status));

                    basyx::object::error::MalformedRequest;
                }

                m_logger->trace("Node [" + fullBrowsePath.toString() + "] - created");

                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            basyx::object::error OPCUAModelProvider<CONNECTOR_TYPE>::deleteValue(const std::string & path, basyx::object deletedValue)
            {
                return basyx::object::error::MalformedRequest;
            }

            template<typename CONNECTOR_TYPE>
            basyx::object::error OPCUAModelProvider<CONNECTOR_TYPE>::deleteValue(const std::string & t_path)
            {
                UA_StatusCode status = UA_STATUSCODE_GOOD;

                m_logger->trace("DELETE - Path [" + t_path + "]");

                auto relativeBrowsePath = m_vabHandler->translateVABPathToBrowsePath(t_path, m_connector->getNamespaceIndexDefault());

                auto fullBrowsePath = BrowsePath({ m_services->getBrowseNameFromNodeId(m_rootNode) }) + relativeBrowsePath;

                auto nodeId = m_services->translateBrowsePathToNodeId(fullBrowsePath);

                if (nodeId.isNull())
                {
                    m_logger->error("BrowsePath [" + fullBrowsePath.toString() + "] element does not exists in OPCUA server");

                    return basyx::object::error::PropertyNotFound;
                }

                status = m_services->deleteNode(nodeId);

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger->error("OPCUA Node : " + fullBrowsePath.toString() + " deletion failed - Reason : " +
                        shared::diag::getErrorString(status));

                    return basyx::object::error::MalformedRequest;
                }

                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            basyx::object OPCUAModelProvider<CONNECTOR_TYPE>::invokeOperation(const std::string & path, basyx::object parameters)
            {
                return basyx::object::make_null();
            }

            template<typename CONNECTOR_TYPE>
            BrowsePath OPCUAModelProvider<CONNECTOR_TYPE>::getRootBrowsePath() const
            {
                return BrowsePath({ m_services->getBrowseNameFromNodeId(m_rootNode) });
            }
        }
    }
}

#endif