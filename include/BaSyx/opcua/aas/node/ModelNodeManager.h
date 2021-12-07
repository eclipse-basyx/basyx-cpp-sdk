/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef IMODEL_NODE_MANAGER_H
#define IMODEL_NODE_MANAGER_H

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/node/MetamodelTypes.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            class ModelNodeManager
            {
            public:
                ModelNodeManager(const NodeId& t_metamodel_node, const NodeId& t_parent_node):
                    m_metamodel_node(t_metamodel_node), m_parent_node(m_parent_node){}

                ModelNodeManager() = default;

                virtual ~ModelNodeManager() = default;

                virtual UA_StatusCode create(const std::string& t_identifier, NodeId& t_outNode,
                    const LocalizedText& t_description) const = 0;

                virtual UA_StatusCode retrieve(const std::string& t_identifier, NodeId& t_outNode) const = 0;
            
                virtual std::vector<std::tuple<NodeId, std::string>> retrieveAll() const = 0;

                virtual UA_StatusCode remove(const std::string& t_identifier) const = 0;

                const NodeId& getParentNode() const
                {
                    return m_parent_node;
                }

                const NodeId& getMetamodelNode() const
                {
                    return m_parent_node;
                }

            protected:
                NodeId m_metamodel_node;
                NodeId m_parent_node;
            };
        }
    }
}

#endif