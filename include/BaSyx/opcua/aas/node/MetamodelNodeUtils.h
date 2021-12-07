/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef METAMODEL_NODE_UTILS_HPP
#define METAMODEL_NODE_UTILS_HPP

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class MetamodelNodeUtils
            {
            public:
                MetamodelNodeUtils(CONNECTOR_TYPE& t_connector) : m_connector(t_connector){}
                
                NodeId filterNode(const std::string & t_idShort,
                    const NodeId& t_parentNode, const NodeId& t_metamodelType) const;
                    
                std::vector<std::tuple<NodeId, std::string>> filterNodes(const NodeId& t_parentNode,
                    const NodeId& t_metamodelType) const;

            private:
                CONNECTOR_TYPE& m_connector;
            };

            /* Filter nodes with the given IdShort and node type */
            template<typename CONNECTOR_TYPE>
            inline NodeId MetamodelNodeUtils<CONNECTOR_TYPE>::filterNode(const std::string & t_idShort, const NodeId& t_parentNode,
                const NodeId& t_metamodelType) const
            {
                Services<CONNECTOR_TYPE> services(m_connector);
                // Get the children
                std::vector<NodeId> propNodes = services.getChildReferences(
                    t_parentNode, NodeId::numeric(UA_NS0ID_HASCOMPONENT)
                );
                for (const NodeId& node : propNodes)
                {
                    if (services.getHasTypeDefinition(node) == t_metamodelType)
                    {
                        std::string identifier;
                        BrowseName smBrowseName = services.getBrowseNameFromNodeId(node);
                        if (smBrowseName.getText().empty())
                            return NodeId::nullNode();
                        if (shared::string::getInstanceName(smBrowseName.getText()) == t_idShort)
                            return node;
                    }
                }
                return NodeId::nullNode();
            }

            /* Filter nodes with the given node type */
            template<typename CONNECTOR_TYPE>
            inline std::vector<std::tuple<NodeId, std::string>> MetamodelNodeUtils<CONNECTOR_TYPE>::filterNodes(const NodeId& t_parentNode, 
                const NodeId & t_metamodelType) const
            {
                using namespace aas::metamodel;

                Services<CONNECTOR_TYPE> services(m_connector);

                std::vector<std::tuple<NodeId, std::string>> propNodeIdIdentTuple;

                std::vector<NodeId> childNodes = services.getChildReferences(
                    t_parentNode, NodeId::numeric(UA_NS0ID_HASCOMPONENT)
                );
                for (const NodeId& node : childNodes)
                {
                    if (services.getHasTypeDefinition(node) == t_metamodelType)
                    {
                        BrowseName propBrowseName = services.getBrowseNameFromNodeId(node);

                        propNodeIdIdentTuple.emplace_back(std::make_tuple(node, shared::string::getInstanceName(propBrowseName.getText())));
                    }
                }
                return propNodeIdIdentTuple;
            }
        }
    }
}
#endif