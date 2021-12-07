/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef SERVIES_H
#define SERVIES_H

#include <BaSyx/opcua/client/ClientServices.h>
#include <BaSyx/opcua/server/ServerServices.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/ExpandedNodeId.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/common/VariableAttributes.h>

namespace basyx
{
    namespace opcua
    {
        template<typename CONNECTOR_TYPE = Client>
        class Services
        {
        public:
            Services(CONNECTOR_TYPE& t_connector) : m_connector(t_connector) {}

            int32_t getNameSpaceIndex(const std::string& t_namepsaceUri);

            template<typename TYPE>
            UA_StatusCode readValue(const NodeId& t_nodeId, TYPE& t_value);

            template<typename TYPE>
            UA_StatusCode writeValue(const NodeId& t_node, TYPE t_value);

            template<uint32_t TYPE_ID>
            bool isOfTypeNode(const NodeId& t_node);

            UA_StatusCode addVariableNode(const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const NodeId& t_typeDefinition,
                const QualifiedName& t_browseName,
                const VariableAttributes& t_vAttribute);

            UA_StatusCode addVariableNode(const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const NodeId& t_typeDefinition,
                const QualifiedName& t_browseName,
                const VariableAttributes& t_vAttribute,
                NodeId& t_outNodeId);

            UA_StatusCode addObjectNode(const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_typeDefinition,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectAttributes& t_vAttribute);

            UA_StatusCode addObjectNode(const NodeId& t_parentNodeId,
                const NodeId& t_typeDefinition,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectAttributes& t_vAttribute,
                NodeId& t_outNodeId);

            UA_StatusCode addObjectTypeNode(const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectTypeAttributes& t_oTypeAttribute);

            UA_StatusCode addObjectTypeNode(const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectTypeAttributes& t_oTypeAttribute,
                NodeId& t_outNodeId);

            UA_StatusCode addMethodNode(const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const MethodAttributes& t_methodAttributes
            );

            UA_StatusCode addMethodNode(const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const MethodAttributes& t_methodAttributes,
                NodeId& t_outNodeId);

            UA_StatusCode addReferenceTypeNode(const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ReferenceTypeAttributes& t_referenceTypeAttributes);

            UA_StatusCode addReferenceTypeNode(const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ReferenceTypeAttributes& t_referenceTypeAttributes,
                NodeId& t_outNodeId);

            UA_StatusCode addForwardReference(const NodeId& t_sourceNodeId,
                const NodeId& t_referenceType,
                const ExpandedNodeId& t_targetNodeID,
                const UA_NodeClass& t_targetNodeClass);

            UA_StatusCode addForwardReferenceModellingRuleMandatory(const NodeId& t_sourceNodeId,
                const UA_NodeClass& t_targetNodeClass);

            UA_StatusCode addForwardReferenceModellingRuleOptional(const NodeId & t_sourceNodeId,
                const UA_NodeClass & t_targetNodeClass);

            UA_StatusCode deleteNode(const NodeId& t_nodeId);

            NodeId getHasTypeDefinition(const NodeId & t_browseNode);

            NodeId getDataType(const NodeId& t_variableNodeId);

            BrowseName getBrowseNameFromNodeId(const NodeId& t_node);

            bool isNodeObject(const NodeId& t_node);

            bool isNodeObjectType(const NodeId& t_node);

            bool isNodeReferenceType(const NodeId& t_node);

            bool isNodeVariable(const NodeId& t_node);

            UA_NodeClass getNodeClass(const NodeId& t_node);

            NodeId translateBrowsePathToNodeId(const BrowsePath& t_browsePath);

            NodeId translateBrowsePathToNodeId(const BrowsePath& t_browsePath, const NodeId& t_startNode);

            NodeId translateBrowsePathToNodeId(const std::string& t_browsePathStr);

            UA_StatusCode translateBrowsePathToNodeIdService(BrowsePath t_browsePath,
                const NodeId& t_startNode,
                NodeId& targetNode);

            CONNECTOR_TYPE& getConnector()
            {
                return m_connector;
            }

            bool doesNodeExists(const NodeId& t_node, const NodeId& t_parent);

            std::vector<NodeId> getAllChildReferences(const NodeId& t_Node);

            std::vector<NodeId> getChildReferences(const NodeId& t_Node, const NodeId& t_referenceType);

            std::vector<NodeId> getChildReferencesWithType(const NodeId& t_node,
                const NodeId& t_typeNode,
                const NodeId& t_referenceType);

            NodeId getChildReferencesWithBrowseName(const NodeId& t_node,
                const BrowseName& t_browseName,
                const NodeId& t_referenceType);

            UA_StatusCode getNodeDescription(const NodeId & t_node, LocalizedText& t_description);

            UA_StatusCode setNodeDescription(const NodeId & t_node, const LocalizedText& t_description);

        private:
            CONNECTOR_TYPE& m_connector;
        };

        template<>
        int32_t Services<Client>::getNameSpaceIndex(const std::string & t_namepsaceUri);

        template<>
        int32_t Services<Server>::getNameSpaceIndex(const std::string & t_namepsaceUri);

        template<>template<typename TYPE>
        UA_StatusCode Services<Client>::readValue(const NodeId & t_nodeId, TYPE & t_value)
        {
            return ClientServices::readValue<TYPE>(m_connector, t_nodeId, t_value);
        }

        template<>template<typename TYPE>
        UA_StatusCode Services<Server>::readValue(const NodeId & t_nodeId, TYPE & t_value)
        {
            return ServerServices::readValue<TYPE>(m_connector, t_nodeId, t_value);
        }

        template<>template<typename TYPE>
        UA_StatusCode Services<Client>::writeValue(const NodeId & t_node, TYPE t_value)
        {
            return ClientServices::writeValue<TYPE>(m_connector, t_node, t_value);
        }

        template<>template<typename TYPE>
        UA_StatusCode Services<Server>::writeValue(const NodeId & t_node, TYPE t_value)
        {
            return ServerServices::writeValue<TYPE>(m_connector, t_node, t_value);
        }

        template<>template<uint32_t TYPE_ID>
        bool Services<Client>::isOfTypeNode(const NodeId & t_node)
        {
            return ClientServices::isOfTypeNode<TYPE_ID>(m_connector, t_node);
        }

        template<>template<uint32_t TYPE_ID>
        bool Services<Server>::isOfTypeNode(const NodeId & t_node)
        {
            return ServerServices::isOfTypeNode<TYPE_ID>(m_connector, t_node);
        }

        template<>
        UA_StatusCode Services<Client>::addVariableNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const NodeId & t_typeDefinition,
            const QualifiedName & t_browseName,
            const VariableAttributes & t_vAttribute);

        template<>
        UA_StatusCode Services<Server>::addVariableNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const NodeId & t_typeDefinition,
            const QualifiedName & t_browseName,
            const VariableAttributes & t_vAttribute);

        template<>
        UA_StatusCode Services<Client>::addVariableNode(const NodeId& t_parentNodeId,
            const NodeId& t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName& t_browseName,
            const VariableAttributes& t_vAttribute,
            NodeId& t_outNodeId);

        template<>
        UA_StatusCode Services<Server>::addVariableNode(const NodeId& t_parentNodeId,
            const NodeId& t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName& t_browseName,
            const VariableAttributes& t_vAttribute,
            NodeId& t_outNodeId);

        template<>
        UA_StatusCode Services<Client>::addObjectNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute);

        template<>
        UA_StatusCode Services<Server>::addObjectNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute);

        template<>
        UA_StatusCode Services<Client>::addObjectNode(const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute,
            NodeId & t_outNodeId);

        template<>
        UA_StatusCode Services<Server>::addObjectNode(const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute,
            NodeId & t_outNodeId);

        template<>
        UA_StatusCode Services<Client>::addObjectTypeNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute);

        template<>
        UA_StatusCode Services<Server>::addObjectTypeNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute);

        template<>
        UA_StatusCode Services<Client>::addMethodNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes);

        template<>
        UA_StatusCode Services<Server>::addMethodNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes);

        template<>
        UA_StatusCode Services<Client>::addMethodNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes,
            NodeId & t_outNodeId);

        template<>
        UA_StatusCode Services<Server>::addMethodNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes,
            NodeId & t_outNodeId);

        template<>
        std::vector<NodeId> Services<Client>::getAllChildReferences(const NodeId & t_node);

        template<>
        std::vector<NodeId> Services<Server>::getAllChildReferences(const NodeId & t_node);

        template<>
        std::vector<NodeId> Services<Client>::getChildReferences(const NodeId & t_node, const NodeId & t_referenceType);

        template<>
        std::vector<NodeId> Services<Server>::getChildReferences(const NodeId & t_node, const NodeId & t_referenceType);

        template<>
        NodeId Services<Client>::getHasTypeDefinition(const NodeId & t_browseNode);

        template<>
        NodeId Services<Server>::getHasTypeDefinition(const NodeId & t_browseNode);

        template<>
        BrowseName Services<Client>::getBrowseNameFromNodeId(const NodeId & t_node);

        template<>
        BrowseName Services<Server>::getBrowseNameFromNodeId(const NodeId & t_node);

        template<>
        UA_NodeClass Services<Client>::getNodeClass(const NodeId & t_node);

        template<>
        UA_NodeClass Services<Server>::getNodeClass(const NodeId & t_node);

        template<>
        NodeId Services<Client>::getDataType(const NodeId & t_variableNodeId);

        template<>
        NodeId Services<Server>::getDataType(const NodeId & t_variableNodeId);

        template<>
        bool Services<Client>::isNodeObject(const NodeId & t_node);

        template<>
        bool Services<Server>::isNodeObject(const NodeId & t_node);

        template<>
        bool Services<Client>::isNodeObjectType(const NodeId & t_node);

        template<>
        bool Services<Server>::isNodeObjectType(const NodeId & t_node);

        template<>
        bool Services<Client>::isNodeReferenceType(const NodeId & t_node);

        template<>
        bool Services<Server>::isNodeReferenceType(const NodeId & t_node);

        template<>
        NodeId Services<Client>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath);

        template<>
        NodeId Services<Server>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath);

        template<>
        NodeId Services<Client>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath, const NodeId & t_startNode);

        template<>
        NodeId Services<Server>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath, const NodeId & t_startNode);


        template<>
        NodeId Services<Client>::translateBrowsePathToNodeId(const std::string & t_browsePathStr);

        template<>
        NodeId Services<Server>::translateBrowsePathToNodeId(const std::string & t_browsePathStr);

        template<>
        UA_StatusCode Services<Client>::translateBrowsePathToNodeIdService(BrowsePath t_browsePath,
            const NodeId & t_startNode,
            NodeId & targetNode);

        template<>
        UA_StatusCode Services<Server>::translateBrowsePathToNodeIdService(BrowsePath t_browsePath,
            const NodeId & t_startNode,
            NodeId & targetNode);

        template<>
        UA_StatusCode Services<Client>::addForwardReferenceModellingRuleMandatory(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass);

        template<>
        UA_StatusCode Services<Server>::addForwardReferenceModellingRuleMandatory(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass);

        template<>
        UA_StatusCode Services<Client>::addForwardReferenceModellingRuleOptional(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass);

        template<>
        UA_StatusCode Services<Server>::addForwardReferenceModellingRuleOptional(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass);

        template<>
        bool Services<Client>::doesNodeExists(const NodeId & t_node, const NodeId & t_parent);

        template<>
        bool Services<Server>::doesNodeExists(const NodeId & t_node, const NodeId & t_parent);

        template<>
        std::vector<NodeId> Services<Client>::getChildReferencesWithType(const NodeId & t_node,
            const NodeId & t_typeNode,
            const NodeId & t_referenceType);

        template<>
        std::vector<NodeId> Services<Server>::getChildReferencesWithType(const NodeId & t_node,
            const NodeId & t_typeNode,
            const NodeId & t_referenceType);

        template<>
        NodeId Services<Client>::getChildReferencesWithBrowseName(const NodeId & t_node,
            const BrowseName & t_browseName,
            const NodeId & t_referenceType);

        template<>
        NodeId Services<Server>::getChildReferencesWithBrowseName(const NodeId & t_node,
            const BrowseName & t_browseName,
            const NodeId & t_referenceType);
        template<>
        UA_StatusCode Services<Client>::getNodeDescription(const NodeId & t_node, LocalizedText & t_description);

        template<>
        UA_StatusCode Services<Server>::getNodeDescription(const NodeId & t_node, LocalizedText & t_description);

        template<>
        UA_StatusCode Services<Client>::setNodeDescription(const NodeId & t_node, const LocalizedText & t_description);

        template<>
        UA_StatusCode Services<Server>::setNodeDescription(const NodeId & t_node, const LocalizedText & t_description);
    }
}
#endif