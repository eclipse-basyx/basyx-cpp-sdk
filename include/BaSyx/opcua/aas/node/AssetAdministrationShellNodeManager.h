/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef ASSET_ADMINISTRATION_SHELL_NODE_MANAGER_H
#define ASSET_ADMINISTRATION_SHELL_NODE_MANAGER_H

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/aas/node/ModelNodeManager.h>
#include <BaSyx/opcua/aas/metamodel/AASIdentifierType.h>
#include <BaSyx/opcua/aas/metamodel/IAASIdentifiableType.h>
#include <BaSyx/opcua/aas/metamodel/AASAssetAdministrationShellType.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class AssetAdministrationShellNodeManager final: public ModelNodeManager
            {            
            public:

                AssetAdministrationShellNodeManager() = delete;

                AssetAdministrationShellNodeManager(CONNECTOR_TYPE& t_connector, const NodeId& t_parent):
                    m_services(Services<CONNECTOR_TYPE>(t_connector))
                    {
                        using namespace metamodel;

                        int ns = m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

                        this->m_metamodel_node = AASAssetAdministrationShellType::getNodeId(ns);

                        this->m_parent_node = t_parent;
                    }

                virtual UA_StatusCode create(const std::string& t_idShort, NodeId& t_outNode, const LocalizedText& t_description) const override;

                virtual UA_StatusCode retrieve(const std::string& t_identifier, NodeId& t_outNode) const override;

                virtual UA_StatusCode remove(const std::string& t_identifier) const override;

                virtual std::vector<std::tuple<NodeId, std::string>> retrieveAll() const override;

            private:
                mutable opcua::Services<CONNECTOR_TYPE> m_services;
            };
            
            /* Retrieves the AAS node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode AssetAdministrationShellNodeManager<CONNECTOR_TYPE>::create(const std::string & t_idShort,
                NodeId & t_outNode,
                const LocalizedText& t_description) const
            {
                // IdShort should not be empty
                if (t_idShort.empty())
                    return UA_STATUSCODE_BADINVALIDARGUMENT;

                // Prepare the attributes of the Node
                auto nsIdx = m_services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                auto aasMetaName = aas::ModelTypes_::to_string(aas::ModelTypes::AssetAdministrationShell);

                auto aasDisplayName = std::string(aasMetaName) + ":" + t_idShort;

                QualifiedName aasBrowseName(nsIdx, aasDisplayName);

                // TODO : Adapt the Langstring set to multiple languages
                ObjectAttributes aasOAttr(aasDisplayName, t_description.getText(), t_description.getLocale());

                // Instantiate the AssetAdministrationShell object node
                return m_services.addObjectNode(
                    this->m_parent_node, this->m_metamodel_node, NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                    aasBrowseName, aasOAttr, t_outNode
                );
            }

            /* Retrieves the AAS node with given identifier */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode AssetAdministrationShellNodeManager<CONNECTOR_TYPE>::retrieve(const std::string & t_identifier,
                NodeId & t_outNode) const
            {
                using namespace aas::metamodel;

                auto nsIdx = m_services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                // Get the children
                std::vector<NodeId> aasNodes = m_services.getChildReferences(
                    this->m_parent_node, NodeId::numeric(UA_NS0ID_HASCOMPONENT)
                );

                // Filter the node
                for (const NodeId& node : aasNodes)
                {
                    if (m_services.getHasTypeDefinition(node) == this->m_metamodel_node)
                    {
                        std::string identifier;
                        NodeId identifierNode;

                        BrowsePath path(
                            BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Identification),
                            BrowseName(nsIdx, AASIdentifierType::AttrNames::BrowseText_ID)
                        );

                        UA_StatusCode status = m_services.translateBrowsePathToNodeIdService(path, node, identifierNode);

                        CHECK_STATUS_AND_RETURN(status);

                        CHECK_NODE_AND_RETURN(identifierNode);

                        status = m_services.readValue(identifierNode, identifier);
                        
                        CHECK_STATUS_AND_RETURN(status);

                        if (t_identifier == identifier)
                        {
                            t_outNode = node;

                            return UA_STATUSCODE_GOOD;
                        }
                    }
                }

                t_outNode = NodeId::nullNode();

                return UA_STATUSCODE_BADNOTFOUND;
            }

            /* Deletes the AAS node with given identifier */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode AssetAdministrationShellNodeManager<CONNECTOR_TYPE>::remove(const std::string & t_identifier) const
            {
                NodeId aasNode;
                
                UA_StatusCode status = retrieve(t_identifier, aasNode);

                CHECK_NODE_AND_RETURN(aasNode);

                CHECK_STATUS_AND_RETURN(status);

                return m_services.deleteNode(aasNode);
            }

            /* Retrieves the AAS <node, identifier> tuple of all AASs */
            template<typename CONNECTOR_TYPE>
            inline std::vector<std::tuple<NodeId, std::string>> AssetAdministrationShellNodeManager<CONNECTOR_TYPE>::retrieveAll() const
            {
                using namespace aas::metamodel;

                std::vector<std::tuple<NodeId, std::string>> aasNodeIdIdentTuple;

                auto nsIdx = m_services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                // Get the children
                std::vector<NodeId> childNodes = m_services.getChildReferences(
                    this->m_parent_node, NodeId::numeric(UA_NS0ID_HASCOMPONENT)
                );

                // Filter the AAS node from the children
                for (const NodeId& node : childNodes)
                {
                    if (m_services.getHasTypeDefinition(node) == this->m_metamodel_node)
                    {
                        std::string identifier;
                        NodeId identifierNode;

                        BrowsePath path(
                            BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Identification),
                            BrowseName(nsIdx, AASIdentifierType::AttrNames::BrowseText_ID)
                        );

                        UA_StatusCode status = m_services.translateBrowsePathToNodeIdService(path, node, identifierNode);

                        if ((UA_STATUSCODE_GOOD != status) || (identifierNode.isNull()))
                            return aasNodeIdIdentTuple;

                        status = m_services.readValue(identifierNode, identifier);

                        if (UA_STATUSCODE_GOOD != status)
                            return aasNodeIdIdentTuple;

                        aasNodeIdIdentTuple.emplace_back(std::make_tuple(node, identifier));
                    }
                }
                return aasNodeIdIdentTuple;
            }
        }
    }
}

#endif