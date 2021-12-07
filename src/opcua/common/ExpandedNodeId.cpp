/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/ExpandedNodeId.h>

namespace basyx
{
    namespace opcua
    {
        ExpandedNodeId::~ExpandedNodeId()
        {
            release();
        }

        void ExpandedNodeId::release()
        {
            if (m_node != nullptr)
            {
                UA_ExpandedNodeId_delete(m_node);
            }
            m_node = nullptr;
        }

        std::string ExpandedNodeId::toString()
        {
            if (m_node->nodeId.identifierType == UA_NODEIDTYPE_NUMERIC)
            {
                return std::string(
                    "ns:" +
                    std::to_string(m_node->nodeId.namespaceIndex) + ";i=" +
                    std::to_string(m_node->nodeId.identifier.numeric)
                );
            }
            else if (m_node->nodeId.identifierType == UA_NODEIDTYPE_STRING)
            {
                return  std::string(
                    "ns:" +
                    std::to_string(m_node->nodeId.namespaceIndex) + ";s=" +
                    std::string(
                        reinterpret_cast<char*>(m_node->nodeId.identifier.string.data),
                        m_node->nodeId.identifier.string.length)
                );
            }
            else if (m_node->nodeId.identifierType == UA_NODEIDTYPE_GUID)
            {
                return std::string();
            }
            else if (m_node->nodeId.identifierType == UA_NODEIDTYPE_BYTESTRING)
            {
                return std::string();
            }
        }

        bool ExpandedNodeId::isNull()
        {
            auto node = UA_EXPANDEDNODEID_NULL;

            return UA_ExpandedNodeId_equal(&node, m_node);
        }

        ExpandedNodeId::ExpandedNodeId()
        {
            m_node = UA_ExpandedNodeId_new();

            *m_node = UA_EXPANDEDNODEID_NULL;
        }

        ExpandedNodeId::ExpandedNodeId(ExpandedNodeId&& t_other) noexcept
        {
            release();

            m_node = UA_ExpandedNodeId_new();

            UA_ExpandedNodeId_copy(&t_other.getUANode(), m_node);

            t_other.release();
        }

        ExpandedNodeId::ExpandedNodeId(const UA_ExpandedNodeId & t_node)
        {
            if (m_node != nullptr)
            {
                UA_ExpandedNodeId_delete(m_node);
            }

            m_node = UA_ExpandedNodeId_new();

            UA_ExpandedNodeId_copy(&t_node, m_node);
        }

        ExpandedNodeId::ExpandedNodeId(UA_NodeIdType t_class, uint16_t t_namespaceIndex, int32_t t_id)
        {
            m_node = UA_ExpandedNodeId_new();

            *m_node = UA_EXPANDEDNODEID_NUMERIC(t_namespaceIndex, t_id);
        }

        ExpandedNodeId::ExpandedNodeId(UA_NodeIdType t_class, uint16_t t_namespaceIndex, const std::string & t_id)
        {
            m_node = UA_ExpandedNodeId_new();

            *m_node = UA_EXPANDEDNODEID_STRING_ALLOC(t_namespaceIndex, const_cast<char*>(t_id.c_str()));
        }

        ExpandedNodeId & ExpandedNodeId::operator=(ExpandedNodeId && t_other) noexcept
        {
            if (m_node != nullptr)
            {
                UA_ExpandedNodeId_delete(m_node);
            }

            m_node = UA_ExpandedNodeId_new();

            UA_ExpandedNodeId_copy(&t_other.getUANode(), m_node);

            return *this;
        }

        ExpandedNodeId & ExpandedNodeId::operator=(const ExpandedNodeId& t_other)
        {
            if (m_node != nullptr)
            {
                UA_ExpandedNodeId_delete(m_node);
            }

            m_node = UA_ExpandedNodeId_new();

            UA_ExpandedNodeId_copy(&t_other.getUANode(), m_node);

            return *this;
        }

        bool ExpandedNodeId::operator==(ExpandedNodeId & t_other)
        {
            return UA_ExpandedNodeId_equal(m_node, &t_other.getUANode());
        }

        bool ExpandedNodeId::operator!=(ExpandedNodeId & t_other)
        {
            return !(*this == t_other);
        }

        ExpandedNodeId ExpandedNodeId::nullNode()
        {
            return std::move(ExpandedNodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 0, 0));
        }

        ExpandedNodeId ExpandedNodeId::numeric(uint16_t t_namepsaceIdx, uint32_t t_id)
        {
            return std::move(ExpandedNodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, t_namepsaceIdx, t_id));
        }

        ExpandedNodeId ExpandedNodeId::numeric(uint32_t t_id)
        {
            return std::move(ExpandedNodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 0, t_id));;
        }

        ExpandedNodeId ExpandedNodeId::string(uint16_t t_namepsaceIdx, const std::string & t_id)
        {
            return std::move(ExpandedNodeId(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_namepsaceIdx, t_id));
        }

        ExpandedNodeId ExpandedNodeId::string(const std::string & t_id)
        {
            return std::move(ExpandedNodeId(UA_NodeIdType::UA_NODEIDTYPE_STRING, 0, t_id));
        }
    }
}