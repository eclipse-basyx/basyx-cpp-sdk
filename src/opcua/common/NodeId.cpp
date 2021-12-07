/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/NodeId.h>

namespace basyx
{
    namespace opcua
    {
        NodeId::~NodeId()
        {
            release();
        }

        void NodeId::release()
        {
            if (m_node != nullptr)
            {
                UA_NodeId_delete(m_node);
            }
            m_node = nullptr;
        }

        std::string NodeId::toString() const
        {
            if (m_node->identifierType == UA_NODEIDTYPE_NUMERIC)
            {
                return std::string(
                    "ns:" +
                    std::to_string(m_node->namespaceIndex) + ";i=" +
                    std::to_string(m_node->identifier.numeric)
                );
            }
            else if (m_node->identifierType == UA_NODEIDTYPE_STRING)
            {
                return  std::string(
                    "ns:" +
                    std::to_string(m_node->namespaceIndex) + ";s=" +
                    std::string(
                        reinterpret_cast<char*>(m_node->identifier.string.data),
                        m_node->identifier.string.length)
                );
            }
            else if (m_node->identifierType == UA_NODEIDTYPE_GUID)
            {
                return std::string();
            }
            else if (m_node->identifierType == UA_NODEIDTYPE_BYTESTRING)
            {
                return std::string();
            }
            return std::string();
        }

        NodeId NodeId::nullNode()
        {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 0, 0));
        }

        NodeId NodeId::numeric(uint16_t t_namespaceIndex, uint32_t t_id)
        {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, t_namespaceIndex, t_id));
        }

        NodeId NodeId::numeric(uint32_t t_id)
        {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 0, t_id));;
        }

        NodeId NodeId::string(uint16_t t_namespaceIndex, const std::string & t_id)
        {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_namespaceIndex, t_id));
        }

        NodeId NodeId::string(const std::string & t_id)
        {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_STRING, 0, t_id));
        }

        bool NodeId::isNull() const
        {
            auto node = UA_NODEID_NULL;

            return UA_NodeId_equal(m_node, &node);
        }

        NodeId::NodeId()
        {
            m_node = UA_NodeId_new();

            *m_node = UA_NODEID_NULL;
        }

        NodeId::NodeId(NodeId&& t_other) noexcept
        {
            release();

            m_node = UA_NodeId_new();

            UA_NodeId_copy(&t_other.getUANode(), m_node);

            t_other.release();
        }

        NodeId::NodeId(const UA_NodeId & t_node)
        {
            release();

            m_node = UA_NodeId_new();

            UA_NodeId_copy(&t_node, m_node);
        }

        NodeId::NodeId(const NodeId & t_other)
        {
            release();

            m_node = UA_NodeId_new();

            UA_NodeId_copy(&t_other.getUANode(), m_node);
        }


        NodeId::NodeId(UA_NodeIdType t_class, uint16_t t_namespaceIndex, int32_t t_id)
        {
            m_node = UA_NodeId_new();

            *m_node = UA_NODEID_NUMERIC(t_namespaceIndex, t_id);
        }

        NodeId::NodeId(UA_NodeIdType t_class, uint16_t t_namespaceIndex, const std::string & t_id)
        {
            m_node = UA_NodeId_new();

            *m_node = UA_NODEID_STRING_ALLOC(t_namespaceIndex, const_cast<char*>(t_id.c_str()));
        }

        NodeId & NodeId::operator=(NodeId && t_other) noexcept
        {
            release();

            m_node = UA_NodeId_new();

            UA_NodeId_copy(&t_other.getUANode(), m_node);

            return *this;
        }

        NodeId & NodeId::operator=(const NodeId& t_other)
        {
            release();

            m_node = UA_NodeId_new();

            UA_NodeId_copy(&t_other.getUANode(), m_node);

            return *this;
        }

        bool NodeId::operator==(const NodeId & t_other)
        {
            return UA_NodeId_equal(m_node, &t_other.getUANode());
        }

        bool NodeId::operator!=(const NodeId & t_other)
        {
            return !(*this == t_other);
        }
    }
}
