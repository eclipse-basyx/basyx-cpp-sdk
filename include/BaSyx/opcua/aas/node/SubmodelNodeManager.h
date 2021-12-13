/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef SUBMODEL_NODE_MANAGER_H
#define SUBMODEL_NODE_MANAGER_H

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelType.h>
#include <BaSyx/opcua/aas/node/ModelNodeManager.h>
#include <BaSyx/opcua/aas/node/MetamodelNodeUtils.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            using Submodel = basyx::aas::map::Submodel;

            template<typename CONNECTOR_TYPE>
            class SubmodelNodeManager final: public ModelNodeManager
            {
            public:

                SubmodelNodeManager() = delete;

                SubmodelNodeManager(CONNECTOR_TYPE& t_connector, const NodeId& t_parent):
                    m_services(Services<CONNECTOR_TYPE>(t_connector))
                {
                    using namespace metamodel;

                    int ns = m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

                    this->m_metamodel_node  = AASSubmodelType::getNodeId(ns);

                    this->m_parent_node = t_parent;
                }

                virtual UA_StatusCode create(const std::string& t_idShort , NodeId& t_outNode,
                    const LocalizedText& t_description) const override;

                virtual UA_StatusCode retrieve(const std::string& t_idShort, NodeId& t_outNode) const override;

                virtual UA_StatusCode remove(const std::string& t_idShort) const override;

                virtual std::vector<std::tuple<NodeId, std::string>> retrieveAll() const override;
            private:
                mutable opcua::Services<CONNECTOR_TYPE> m_services;
            };

            /* Adds a SM node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode SubmodelNodeManager<CONNECTOR_TYPE>::create(const std::string & t_identifier,
                NodeId & t_outNode,
                const LocalizedText& t_description) const
            {
                // IdShort should not be empty
                if (t_identifier.empty())
                    return UA_STATUSCODE_BADINVALIDARGUMENT;

                // Prepare the attributes of the Node
                auto nsIdx = m_services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                auto smMetaName = basyx::aas::ModelTypes_::to_string(basyx::aas::ModelTypes::Submodel);

                auto smDisplayName = std::string(smMetaName) + ":" + t_identifier;

                QualifiedName smBrowseName(nsIdx, smDisplayName);

                // TODO : Adapt the Langstring set to multiple languages
                ObjectAttributes smOAttr(smDisplayName, t_description.getText(), t_description.getLocale());

                // Instantiate the AssetAdministrationShell object node
                return m_services.addObjectNode(
                    this->m_parent_node, this->m_metamodel_node, NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                    smBrowseName, smOAttr, t_outNode
                );
            }

            /* Retrieves the SM node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode SubmodelNodeManager<CONNECTOR_TYPE>::retrieve(const std::string & t_idShort, NodeId & t_outNode) const
            {
                MetamodelNodeUtils<CONNECTOR_TYPE> nodeUtils(m_services.getConnector());

                t_outNode = nodeUtils.filterNode(t_idShort, this->m_parent_node, this->m_metamodel_node);
                if (t_outNode.isNull())
                    return UA_STATUSCODE_BADNOTFOUND;
                return UA_STATUSCODE_GOOD;
            }

            /* Removes the SM node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode SubmodelNodeManager<CONNECTOR_TYPE>::remove(const std::string & t_idShort) const
            {
                NodeId smNode;  
                          
                UA_StatusCode status = retrieve(t_idShort, smNode);
                if (smNode.isNull())
                    return UA_STATUSCODE_BADNOTFOUND;      
                if (status != UA_STATUSCODE_GOOD)
                    return status;
                return m_services.deleteNode(smNode);
            }

            /* Retrieves all the SM <node, idShort> tuple */
            template<typename CONNECTOR_TYPE>
            inline std::vector<std::tuple<NodeId, std::string>> SubmodelNodeManager<CONNECTOR_TYPE>::retrieveAll() const
            {
                MetamodelNodeUtils<CONNECTOR_TYPE> nodeUtils(m_services.getConnector());

                return nodeUtils.filterNodes(this->m_parent_node, this->m_metamodel_node);
            }


}
    }
}
#endif