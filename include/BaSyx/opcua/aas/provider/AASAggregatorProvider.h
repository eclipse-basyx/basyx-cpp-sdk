/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_AGGREGATOR_PROVIDER_H
#define AAS_AGGREGATOR_PROVIDER_H

#include <BaSyx/log/log.h>
#include <BaSyx/shared/types.h>
#include <BaSyx/shared/object.h>
#include <BaSyx/vab/core/IModelProvider.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/provider/AASModelProviderCommon.h>
#include <BaSyx/opcua/aas/provider/AASAggregatorHelpers.h>
#include <BaSyx/opcua/aas/provider/AASSubmodelProvider.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE = basyx::opcua::Client>
            class AASAggregatorProvider : public vab::core::IModelProvider
            {
                static constexpr const char loggerName[] = "AASAggregatorProvider";
            public:

                AASAggregatorProvider(const std::string & t_endpoint, const NodeId & t_rootNode);

                AASAggregatorProvider(const std::string & t_endpoint,
                    std::unique_ptr<IModelProvider> t_submodelProvider,
                    const NodeId & t_rootNode);

                ~AASAggregatorProvider();

                /* REST GET */
                virtual basyx::object getModelPropertyValue(const std::string& t_path) override
                {
                    if (t_path.empty())
                    {
                        m_logger.error("Path cannot be empty");
                        return basyx::object::make_error(basyx::object::error::MalformedRequest, "Path cannot be empty");
                    }             
                    return parseGet(t_path);
                }

                /* REST PUT */
                virtual basyx::object::error setModelPropertyValue(const std::string& t_path, const basyx::object t_newValue) override
                {
                    if (t_path.empty())
                    {
                        m_logger.error("Path cannot be empty");
                        return basyx::object::error::MalformedRequest;
                    }
                    return parsePut(t_path, t_newValue);
                }

                /* REST POST */
                virtual basyx::object::error createValue(const std::string& t_path, const basyx::object t_newValue) override
                {
                    if (t_path.empty())
                    {
                        m_logger.error("Path cannot be empty");
                        return basyx::object::error::MalformedRequest;
                    }
                    return basyx::object::error::None;
                }

                /* IGNORED */
                virtual basyx::object::error deleteValue(const std::string& t_path, basyx::object t_deletedValue) override
                {
                    return basyx::object::error::ProviderException;
                }

                /* REST DELETE */
                virtual basyx::object::error deleteValue(const std::string& t_path) override
                {
                    if (t_path.empty())
                    {
                        m_logger.error("Path cannot be empty");
                        return basyx::object::error::MalformedRequest;
                    }
                    return parseDelete(t_path);
                }

                /* REST POST */
                virtual basyx::object invokeOperation(const std::string& t_path, basyx::object t_parameters) override
                {
                    if (t_path.empty())
                    {
                        m_logger.error("Path cannot be empty");
                        return basyx::object::make_error(basyx::object::error::MalformedRequest, "Path cannot be empty");
                    }
                    return m_submodelProvider->invokeOperation(t_path, t_parameters);
                }

            private:
                basyx::object parseGet(const std::string& t_path);
                basyx::object::error parsePut(const std::string& t_path, basyx::object t_value);
                basyx::object::error parseDelete(const std::string& t_path);
                NodeId getAASNode(const std::string& t_identifier);
            private:
                std::unique_ptr<CONNECTOR_TYPE> m_connector;
                std::unique_ptr<IModelProvider> m_submodelProvider;
                basyx::log m_logger;
                NodeId m_rootNode;
            };

            template<typename CONNECTOR_TYPE>
            constexpr char AASAggregatorProvider<CONNECTOR_TYPE>::loggerName[];

            template<>
            inline AASAggregatorProvider<Client>::AASAggregatorProvider(const std::string & t_endpoint, const NodeId & t_rootNode) :
                m_rootNode(t_rootNode), m_logger(basyx::log(loggerName))
            {
                m_connector = util::make_unique<Client>(t_endpoint, shared::Namespaces::BASYX_NS_URI);

                m_connector->setRootNode(t_rootNode);

                m_connector->connect();

                metamodel::AASMetamodel::define<Client>(m_connector->getNamespaceIndexDefault(), *m_connector.get());
            }

            template<>
            inline AASAggregatorProvider<Server>::AASAggregatorProvider(const std::string & t_port, const NodeId & t_rootNode) :
                m_rootNode(t_rootNode), m_logger(basyx::log(loggerName))
            {
                m_connector = util::make_unique<Server>(std::stoi(t_port), shared::Namespaces::BASYX_NS_URI);

                m_connector->setRootNode(t_rootNode);

                m_connector->initialize();

                m_submodelProvider = util::make_unique<AASSubmodelProvider<Server>>(*m_connector.get(), t_rootNode);

                metamodel::AASMetamodel::define<Server>(m_connector->getNamespaceIndexDefault(), *m_connector.get());
            }

            template<>
            inline AASAggregatorProvider<Client>::AASAggregatorProvider(const std::string & t_endpoint,
                std::unique_ptr<IModelProvider> t_submodelProvider,
                const NodeId & t_rootNode) :
                m_rootNode(t_rootNode), m_logger(basyx::log(loggerName))
            {
                m_connector = util::make_unique<Client>(t_endpoint, shared::Namespaces::BASYX_NS_URI);

                m_connector->setRootNode(t_rootNode);

                m_connector->connect();

                m_submodelProvider = std::move(t_submodelProvider);

                metamodel::AASMetamodel::define<Client>(m_connector->getNamespaceIndexDefault(), *m_connector.get());
            }

            template<>
            inline AASAggregatorProvider<Server>::AASAggregatorProvider(const std::string & t_port,
                std::unique_ptr<IModelProvider> t_submodelProvider,
                const NodeId & t_rootNode) :
                m_rootNode(t_rootNode), m_logger(basyx::log(loggerName))
            {
                m_connector = util::make_unique<Server>(std::stoi(t_port), shared::Namespaces::BASYX_NS_URI);

                m_connector->setRootNode(t_rootNode);

                m_connector->initialize();

                m_submodelProvider = std::move(t_submodelProvider);

                metamodel::AASMetamodel::define<Server>(m_connector->getNamespaceIndexDefault(), *m_connector.get());
            }

            template<>
            inline AASAggregatorProvider<Client>::~AASAggregatorProvider()
            {
                m_connector->disconnect();
            }

            template<>
            inline AASAggregatorProvider<Server>::~AASAggregatorProvider()
            {
                m_connector->abort();
            }


            template<typename CONNECTOR_TYPE>
            inline basyx::object AASAggregatorProvider<CONNECTOR_TYPE>::parseGet(const std::string & t_path)
            {
                auto idTuple{ AASProviderApiParseHelpers::parseIdentifiers(vab::core::VABPath(t_path)) };

                AASAggregatorHelpers<CONNECTOR_TYPE> aggregator(*m_connector, m_rootNode);
                if (t_path == Element::shells)
                    return aggregator.getShells();
                else if (AASProviderApiParseHelpers::isApiShellsAASId(t_path))
                {
                    return aggregator.getShellsAasId(std::get<AAS_ID>(idTuple));
                }
                else if (AASProviderApiParseHelpers::isApiShellsAASIdAAS(t_path))
                {
                    return aggregator.getShellsAasId(std::get<AAS_ID>(idTuple));
                }
                else if (AASProviderApiParseHelpers::isAPISubmodels(t_path))
                {
                    return aggregator.getShellsAasidAasSubmodels(std::get<AAS_ID>(idTuple));
                }
                else
                {
                    NodeId  aasNode = getAASNode(std::get<AAS_ID>(idTuple));

                    if (aasNode.isNull())
                        return basyx::object::make_error(basyx::object::error::ProviderException);

                    m_submodelProvider = util::make_unique<AASSubmodelProvider<CONNECTOR_TYPE>>(*m_connector.get(), aasNode);
                    return m_submodelProvider->getModelPropertyValue(t_path);
                }
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASAggregatorProvider<CONNECTOR_TYPE>::parsePut(const std::string & t_path,
                basyx::object t_value)
            {
                auto idTuple{ AASProviderApiParseHelpers::parseIdentifiers(vab::core::VABPath(t_path)) };

                AASAggregatorHelpers<CONNECTOR_TYPE> aggregator(*m_connector, m_rootNode);
                if (AASProviderApiParseHelpers::isApiShellsAASId(t_path))
                {
                    return aggregator.putShellsAasId(std::get<AAS_ID>(idTuple), t_value);
                }
                else
                {
                    NodeId  aasNode = getAASNode(std::get<AAS_ID>(idTuple));

                    if (aasNode.isNull())
                        return basyx::object::error::ProviderException;

                    m_submodelProvider = util::make_unique<AASSubmodelProvider<CONNECTOR_TYPE>>(*m_connector.get(), aasNode);
                    return m_submodelProvider->setModelPropertyValue(t_path, t_value);
                }               
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASAggregatorProvider<CONNECTOR_TYPE>::parseDelete(const std::string & t_path)
            {
                auto idTuple{ AASProviderApiParseHelpers::parseIdentifiers(vab::core::VABPath(t_path)) };

                AASAggregatorHelpers<CONNECTOR_TYPE> aggregator(*m_connector, m_rootNode);
                if (AASProviderApiParseHelpers::isApiShellsAASId(t_path))
                {
                    return aggregator.deleteShellsAasId(std::get<AAS_ID>(idTuple));
                }
                else
                {
                    NodeId  aasNode = getAASNode(std::get<AAS_ID>(idTuple));

                    if (aasNode.isNull())
                        return basyx::object::error::ProviderException;

                    m_submodelProvider = util::make_unique<AASSubmodelProvider<CONNECTOR_TYPE>>(*m_connector.get(), aasNode);
                    return m_submodelProvider->deleteValue(t_path);
                }
            }
            template<typename CONNECTOR_TYPE>
            inline NodeId AASAggregatorProvider<CONNECTOR_TYPE>::getAASNode(const std::string& t_identifier)
            {
                NodeId aasNode;

                AssetAdministrationShellNodeManager<CONNECTOR_TYPE> aasNodeMgr(*m_connector.get(), m_rootNode);
                UA_StatusCode status = aasNodeMgr.retrieve(t_identifier, aasNode);

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger.error("Node for AssetAdministrationShell ["+ t_identifier + "] could not be retrieved - " +
                        shared::diag::getErrorString(status));
                    return NodeId::nullNode();
                }
                return aasNode;
            }
        }
    }
}

#endif