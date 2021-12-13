/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef PROPERTY_NODE_MANAGER_H
#define PROPERTY_NODE_MANAGER_H

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/aas/metamodel/AASPropertyType.h>
#include <BaSyx/opcua/aas/node/ModelNodeManager.h>
#include <BaSyx/opcua/aas/node/MetamodelNodeUtils.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename T> using Property = basyx::aas::map::Property<T>;

            template<typename CONNECTOR_TYPE>
            class PropertyNodeManager final: public ModelNodeManager
            {
            public:
                PropertyNodeManager() = delete;

                PropertyNodeManager(CONNECTOR_TYPE& t_connector, const NodeId& t_parent):
                    m_services(Services<CONNECTOR_TYPE>(t_connector))
                {
                    using namespace metamodel;

                    int ns = m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

                    this->m_metamodel_node = AASPropertyType::getNodeId(ns);

                    this->m_parent_node = t_parent;
                }

                virtual UA_StatusCode create(const std::string& t_idShort, NodeId& t_outNode, const LocalizedText& t_description) const override;

                virtual UA_StatusCode retrieve(const std::string& t_idShort, NodeId& t_outNode) const override;

                virtual UA_StatusCode remove(const std::string& t_idShort) const override;

                virtual std::vector<std::tuple<NodeId, std::string>> retrieveAll() const override;
            private:
                mutable opcua::Services<CONNECTOR_TYPE> m_services;
            };


            /* Adds a Property node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode PropertyNodeManager<CONNECTOR_TYPE>::create(const std::string & t_idShort,
                NodeId & t_outNode,
                const LocalizedText& t_description) const
            {
                // IdShort should not be empty
                if (t_idShort.empty())
                    return UA_STATUSCODE_BADINVALIDARGUMENT;

                // Prepare the attributes of the Node
                auto nsIdx = m_services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                auto propMetaName = basyx::aas::ModelTypes_::to_string(basyx::aas::ModelTypes::Property);

                auto propDisplayName = std::string(propMetaName) + ":" + t_idShort;

                QualifiedName propBrowseName(nsIdx, propDisplayName);

                // TODO : Adapt the Langstring set to multiple languages
                ObjectAttributes propOAttr(propDisplayName, t_description.getText(), t_description.getLocale());

                // Instantiate the Property object node
                return m_services.addObjectNode(
                    this->m_parent_node, this->m_metamodel_node, NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                    propBrowseName, propOAttr, t_outNode
                );
            }

            /*  Retrieves Property node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode PropertyNodeManager<CONNECTOR_TYPE>::retrieve(const std::string & t_idShort, NodeId & t_outNode) const
            {
                MetamodelNodeUtils<CONNECTOR_TYPE> nodeUtils(m_services.getConnector());

                t_outNode = nodeUtils.filterNode(t_idShort, this->m_parent_node, this->m_metamodel_node);
                if (t_outNode.isNull())
                    return UA_STATUSCODE_BADNOTFOUND;
                return UA_STATUSCODE_GOOD;
            }

            /* Deletes the Property node with the given idShort */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode PropertyNodeManager<CONNECTOR_TYPE>::remove(const std::string & t_idShort) const
            {
                NodeId propNode;
                
                UA_StatusCode status = retrieve(t_idShort, propNode);
                if (propNode.isNull())
                    return UA_STATUSCODE_BADNOTFOUND;
                if (status != UA_STATUSCODE_GOOD)
                    return status;
                return m_services.deleteNode(propNode);
            }


    	    /* Retrieve all the Property <node, idShort> tuple */
            template<typename CONNECTOR_TYPE>
            inline std::vector<std::tuple<NodeId, std::string>> PropertyNodeManager<CONNECTOR_TYPE>::retrieveAll() const
            {
                MetamodelNodeUtils<CONNECTOR_TYPE> nodeUtils(m_services.getConnector());

                return nodeUtils.filterNodes(this->m_parent_node, this->m_metamodel_node);
            }
        }
    }
}
#endif