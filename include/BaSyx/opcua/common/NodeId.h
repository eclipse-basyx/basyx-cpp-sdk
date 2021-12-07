/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef NODE_ID_H
#define NODE_ID_H

#include <string>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class NodeId
        {
        public:

            NodeId();

            NodeId(const UA_NodeId& t_node);

            NodeId(const NodeId& t_other);

            NodeId(NodeId&& t_other) noexcept;

            NodeId(UA_NodeIdType t_class, int32_t t_id) : NodeId(t_class, 0, t_id) {}

            NodeId(UA_NodeIdType t_class, uint16_t t_namespaceIndex, int32_t t_id);

            NodeId(UA_NodeIdType t_class, const std::string& t_id) : NodeId(t_class, 0, t_id) {}

            NodeId(UA_NodeIdType t_class, uint16_t t_namespaceIndex, const std::string& t_id);

            NodeId& operator=(NodeId&& t_other) noexcept;

            NodeId& operator=(const NodeId& t_other);

            bool operator ==(const NodeId& t_other);

            bool operator !=(const NodeId& t_other);

            virtual ~NodeId();

            bool isNull() const;

            inline void release();

            std::string toString() const;

            static NodeId nullNode();

            static NodeId numeric(uint16_t t_namespaceIdx, uint32_t t_id);

            static NodeId numeric(uint32_t t_id);

            static NodeId string(uint16_t t_namespaceIdx, const std::string& t_id);

            static NodeId string(const std::string& t_id);

            UA_NodeId& getUANode() const
            {
                return *m_node;
            }


        private:
            UA_NodeId* m_node = nullptr;
        };
    }
}
#endif