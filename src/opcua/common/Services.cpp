/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/Services.h>

namespace basyx
{
    namespace opcua
    {
        template<>
        int32_t Services<Client>::getNameSpaceIndex(const std::string & t_namepsaceUri)
        {
            return ClientServices::getNameSpaceIndex(m_connector, t_namepsaceUri);
        }

        template<>
        int32_t Services<Server>::getNameSpaceIndex(const std::string & t_namepsaceUri)
        {
            return ServerServices::getNameSpaceIndex(m_connector, t_namepsaceUri);
        }

        template<>
        UA_StatusCode Services<Client>::addVariableNode(const NodeId& t_nodeId,
            const NodeId& t_parentNodeId,
            const NodeId& t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName& t_browseName,
            const VariableAttributes& t_vAttribute)
        {
            return ClientServices::addVariableNode(
                m_connector, t_nodeId, t_parentNodeId, t_referenceType, t_typeDefinition, t_browseName, t_vAttribute
            );
        }

        template<>
        UA_StatusCode Services<Server>::addVariableNode(const NodeId& t_nodeId,
            const NodeId& t_parentNodeId,
            const NodeId& t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName& t_browseName,
            const VariableAttributes& t_vAttribute)
        {
            return ServerServices::addVariableNode(
                m_connector, t_nodeId, t_parentNodeId, t_referenceType, t_typeDefinition, t_browseName, t_vAttribute
            );
        }

        template<>
        UA_StatusCode Services<Client>::addVariableNode(const NodeId& t_parentNodeId,
            const NodeId& t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName& t_browseName,
            const VariableAttributes& t_vAttribute,
            NodeId& t_outNodeId)
        {
            return ClientServices::addVariableNode(
                m_connector, t_parentNodeId, t_referenceType, t_typeDefinition, t_browseName, t_vAttribute, t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Server>::addVariableNode(const NodeId& t_parentNodeId,
            const NodeId& t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName& t_browseName,
            const VariableAttributes& t_vAttribute,
            NodeId& t_outNodeId)
        {
            return ServerServices::addVariableNode(
                m_connector, t_parentNodeId, t_referenceType, t_typeDefinition, t_browseName, t_vAttribute, t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Client>::addObjectNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute)
        {
            return ClientServices::addObjectNode(
                m_connector, t_nodeId, t_parentNodeId, t_typeDefinition, t_referenceType, t_browseName, t_vAttribute
            );
        }

        template<>
        UA_StatusCode Services<Server>::addObjectNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute)
        {
            return ServerServices::addObjectNode(
                m_connector, t_nodeId, t_parentNodeId, t_typeDefinition, t_referenceType, t_browseName, t_vAttribute
            );
        }

        template<>
        UA_StatusCode Services<Client>::addObjectNode(const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute,
            NodeId & t_outNodeId)
        {
            return ClientServices::addObjectNode(
                m_connector, t_parentNodeId, t_typeDefinition, t_referenceType, t_browseName, t_vAttribute, t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Server>::addObjectNode(const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute,
            NodeId & t_outNodeId)
        {
            return ServerServices::addObjectNode(
                m_connector, t_parentNodeId, t_typeDefinition, t_referenceType, t_browseName, t_vAttribute, t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Client>::addObjectTypeNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute)
        {
            return ClientServices::addObjectTypeNode(
                m_connector, t_nodeId, t_parentNodeId, t_referenceType, t_browseName, t_oTypeAttribute
            );
        }

        template<>
        UA_StatusCode Services<Server>::addObjectTypeNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute)
        {
            return ServerServices::addObjectTypeNode(
                m_connector, t_nodeId, t_parentNodeId, t_referenceType, t_browseName, t_oTypeAttribute
            );
        }

        template<>
        UA_StatusCode Services<Client>::addObjectTypeNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute,
            NodeId & t_outNodeId)
        {
            return ClientServices::addObjectTypeNode(
                m_connector, t_parentNodeId, t_referenceType, t_browseName, t_oTypeAttribute, t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Client>::addMethodNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes)
        {
            return ClientServices::addMethodNode(
                m_connector,
                t_nodeId,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_methodAttributes
            );
        }

        template<>
        UA_StatusCode Services<Server>::addMethodNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes)
        {
            return ServerServices::addMethodNode(
                m_connector,
                t_nodeId,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_methodAttributes
            );
        }

        template<>
        UA_StatusCode Services<Client>::addMethodNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes,
            NodeId & t_outNodeId)
        {
            return ClientServices::addMethodNode(
                m_connector,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_methodAttributes,
                t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Server>::addMethodNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes,
            NodeId & t_outNodeId)
        {
            return ServerServices::addMethodNode(
                m_connector,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_methodAttributes,
                t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Client>::addReferenceTypeNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ReferenceTypeAttributes & t_referenceTypeAttributes)
        {
            return ClientServices::addReferenceTypeNode(
                m_connector,
                t_nodeId,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_referenceTypeAttributes
            );
        }

        template<>
        UA_StatusCode Services<Server>::addReferenceTypeNode(const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ReferenceTypeAttributes & t_referenceTypeAttributes)
        {
            return ServerServices::addReferenceTypeNode(
                m_connector,
                t_nodeId,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_referenceTypeAttributes
            );
        }

        template<>
        UA_StatusCode Services<Client>::addReferenceTypeNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ReferenceTypeAttributes & t_referenceTypeAttributes,
            NodeId & t_outNodeId)
        {
            return ClientServices::addReferenceTypeNode(
                m_connector,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_referenceTypeAttributes,
                t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Server>::addReferenceTypeNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ReferenceTypeAttributes & t_referenceTypeAttributes,
            NodeId & t_outNodeId)
        {
            return ServerServices::addReferenceTypeNode(
                m_connector,
                t_parentNodeId,
                t_referenceType,
                t_browseName,
                t_referenceTypeAttributes,
                t_outNodeId
            );
        }

        template<>
        UA_StatusCode Services<Client>::addForwardReference(const NodeId & t_sourceNodeId,
            const NodeId & t_referenceType,
            const ExpandedNodeId & t_targetNodeID,
            const UA_NodeClass & t_targetNodeClass)
        {
            return ClientServices::addForwardReference(m_connector,
                t_sourceNodeId,
                t_referenceType,
                t_targetNodeID,
                t_targetNodeClass
            );
        }

        template<>
        UA_StatusCode Services<Client>::addForwardReferenceModellingRuleMandatory(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass)
        {
            return ClientServices::addForwardReferenceModellingRuleMandatory(m_connector, t_sourceNodeId, t_targetNodeClass);
        }

        template<>
        UA_StatusCode Services<Server>::addForwardReferenceModellingRuleMandatory(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass)
        {
            return ServerServices::addForwardReferenceModellingRuleMandatory(m_connector, t_sourceNodeId, t_targetNodeClass);
        }

        template<>
        UA_StatusCode Services<Client>::addForwardReferenceModellingRuleOptional(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass)
        {
            return UA_StatusCode();
        }

        template<>
        UA_StatusCode Services<Server>::addForwardReferenceModellingRuleOptional(const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass)
        {
            return UA_StatusCode();
        }

        template<>
        UA_StatusCode Services<Server>::addForwardReference(const NodeId & t_sourceNodeId,
            const NodeId & t_referenceType,
            const ExpandedNodeId & t_targetNodeID,
            const UA_NodeClass & t_targetNodeClass)
        {
            return ServerServices::addForwardReference(m_connector,
                t_sourceNodeId,
                t_referenceType,
                t_targetNodeID,
                t_targetNodeClass
            );
        }

        template<>
        UA_StatusCode Services<Client>::deleteNode(const NodeId & t_nodeId)
        {
            return ClientServices::deleteNode(m_connector, t_nodeId);
        }

        template<>
        UA_StatusCode Services<Server>::deleteNode(const NodeId & t_nodeId)
        {
            return ServerServices::deleteNode(m_connector, t_nodeId);
        }

        template<>
        UA_StatusCode Services<Server>::addObjectTypeNode(const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute,
            NodeId & t_outNodeId)
        {
            return ServerServices::addObjectTypeNode(
                m_connector, t_parentNodeId, t_referenceType, t_browseName, t_oTypeAttribute, t_outNodeId
            );
        }

        template<>
        std::vector<NodeId> Services<Client>::getAllChildReferences(const NodeId & t_node)
        {
            return ClientServices::getAllChildReferences(m_connector, t_node);
        }

        template<>
        std::vector<NodeId> Services<Server>::getAllChildReferences(const NodeId & t_node)
        {
            return ServerServices::getAllChildReferences(m_connector, t_node);
        }

        template<>
        std::vector<NodeId> Services<Client>::getChildReferences(const NodeId & t_node, const NodeId & t_referenceType)
        {
            return ClientServices::getChildReferences(m_connector, t_node, t_referenceType);
        }

        template<>
        std::vector<NodeId> Services<Server>::getChildReferences(const NodeId & t_node, const NodeId & t_referenceType)
        {
            return ServerServices::getChildReferences(m_connector, t_node, t_referenceType);
        }

        template<>
        NodeId Services<Client>::getHasTypeDefinition(const NodeId & t_browseNode)
        {
            return ClientServices::getHasTypeDefinition(m_connector, t_browseNode);
        }

        template<>
        NodeId Services<Server>::getHasTypeDefinition(const NodeId & t_browseNode)
        {
            return ServerServices::getHasTypeDefinition(m_connector, t_browseNode);
        }

        template<>
        NodeId Services<Client>::getDataType(const NodeId & t_variableNodeId)
        {
            return ClientServices::getDataType(m_connector, t_variableNodeId);
        }

        template<>
        NodeId Services<Server>::getDataType(const NodeId & t_variableNodeId)
        {
            return ServerServices::getDataType(m_connector, t_variableNodeId);
        }

        template<>
        BrowseName Services<Client>::getBrowseNameFromNodeId(const NodeId & t_node)
        {
            return ClientServices::getBrowseNameFromNodeId(m_connector, t_node);
        }

        template<>
        BrowseName Services<Server>::getBrowseNameFromNodeId(const NodeId & t_node)
        {
            return ServerServices::getBrowseNameFromNodeId(m_connector, t_node);
        }

        template<>
        UA_NodeClass Services<Client>::getNodeClass(const NodeId & t_node)
        {
            return ClientServices::getNodeClass(m_connector, t_node);
        }

        template<>
        UA_NodeClass Services<Server>::getNodeClass(const NodeId & t_node)
        {
            return ServerServices::getNodeClass(m_connector, t_node);
        }

        template<>
        bool Services<Client>::isNodeObject(const NodeId & t_node)
        {
            return ClientServices::isNodeObject(m_connector, t_node);
        }

        template<>
        bool Services<Server>::isNodeObject(const NodeId & t_node)
        {
            return ServerServices::isNodeObject(m_connector, t_node);
        }

        template<>
        bool Services<Client>::isNodeObjectType(const NodeId & t_node)
        {
            return ClientServices::isNodeObjectType(m_connector, t_node);
        }

        template<>
        bool Services<Server>::isNodeObjectType(const NodeId & t_node)
        {
            return ServerServices::isNodeObjectType(m_connector, t_node);
        }

        template<>
        bool Services<Client>::isNodeReferenceType(const NodeId & t_node)
        {
            return ClientServices::isNodeReferenceType(m_connector, t_node);
        }

        template<>
        bool Services<Server>::isNodeReferenceType(const NodeId & t_node)
        {
            return ServerServices::isNodeReferenceType(m_connector, t_node);
        }

        template<>
        bool Services<Client>::isNodeVariable(const NodeId & t_node)
        {
            return ClientServices::isNodeVariable(m_connector, t_node);
        }

        template<>
        bool Services<Server>::isNodeVariable(const NodeId & t_node)
        {
            return ServerServices::isNodeVariable(m_connector, t_node);
        }

        template<>
        NodeId Services<Client>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath)
        {
            return ClientServices::translateBrowsePathToNodeId(m_connector, t_browsePath);
        }

        template<>
        NodeId Services<Server>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath)
        {
            return ServerServices::translateBrowsePathToNodeId(m_connector, t_browsePath);
        }

        template<>
        NodeId Services<Client>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath, const NodeId & t_startNode)
        {
            return ClientServices::translateBrowsePathToNodeId(m_connector, t_browsePath, t_startNode);
        }

        template<>
        NodeId Services<Server>::translateBrowsePathToNodeId(const BrowsePath & t_browsePath, const NodeId & t_startNode)
        {
            return ServerServices::translateBrowsePathToNodeId(m_connector, t_browsePath, t_startNode);
        }

        template<>
        NodeId Services<Client>::translateBrowsePathToNodeId(const std::string & t_browsePathStr)
        {
            return ClientServices::translateBrowsePathToNodeId(m_connector, t_browsePathStr);
        }

        template<>
        NodeId Services<Server>::translateBrowsePathToNodeId(const std::string & t_browsePathStr)
        {
            return ServerServices::translateBrowsePathToNodeId(m_connector, t_browsePathStr);
        }

        template<>
        UA_StatusCode Services<Client>::translateBrowsePathToNodeIdService(BrowsePath t_browsePath,
            const NodeId & t_startNode,
            NodeId & targetNode)
        {
            return ClientServices::translateBrowsePathToNodeIdService(m_connector, t_browsePath, t_startNode, targetNode);
        }

        template<>
        bool Services<Client>::doesNodeExists(const NodeId & t_node, const NodeId & t_parent)
        {
            return ClientServices::doesNodeExists(m_connector, t_node, t_parent);;
        }

        template<>
        bool Services<Server>::doesNodeExists(const NodeId & t_node, const NodeId & t_parent)
        {
            return ServerServices::doesNodeExists(m_connector, t_node, t_parent);;
        }

        template<>
        UA_StatusCode Services<Server>::translateBrowsePathToNodeIdService(BrowsePath t_browsePath,
            const NodeId & t_startNode,
            NodeId & targetNode)
        {
            return ServerServices::translateBrowsePathToNodeIdService(m_connector, t_browsePath, t_startNode, targetNode);
        }

        template<>
        std::vector<NodeId> Services<Client>::getChildReferencesWithType(const NodeId & t_node,
            const NodeId & t_typeNode,
            const NodeId & t_referenceType)
        {
            return ClientServices::getChildReferencesWithType(m_connector, t_node, t_typeNode, t_referenceType);
        }

        template<>
        std::vector<NodeId> Services<Server>::getChildReferencesWithType(const NodeId & t_node,
            const NodeId & t_typeNode,
            const NodeId & t_referenceType)
        {
            return ServerServices::getChildReferencesWithType(m_connector, t_node, t_typeNode, t_referenceType);
        }

        template<>
        NodeId Services<Client>::getChildReferencesWithBrowseName(const NodeId & t_node,
            const BrowseName & t_browseName,
            const NodeId & t_referenceType)
        {
            return ClientServices::getChildReferencesWithBrowseName(m_connector, t_node, t_browseName, t_referenceType);
        }

        template<>
        UA_StatusCode Services<Client>::getNodeDescription(const NodeId & t_node, LocalizedText & t_description)
        {
            return ClientServices::getNodeDescription(m_connector, t_node, t_description);
        }

        template<>
        UA_StatusCode Services<Server>::getNodeDescription(const NodeId & t_node, LocalizedText & t_description)
        {
            return ServerServices::getNodeDescription(m_connector, t_node, t_description);
        }


        template<>
        UA_StatusCode Services<Client>::setNodeDescription(const NodeId & t_node, const LocalizedText & t_description)
        {
            return ClientServices::setNodeDescription(m_connector, t_node, t_description);
        }

        template<>
        UA_StatusCode Services<Server>::setNodeDescription(const NodeId & t_node, const LocalizedText & t_description)
        {
            return ServerServices::setNodeDescription(m_connector, t_node, t_description);
        }

        template<>
        NodeId Services<Server>::getChildReferencesWithBrowseName(const NodeId & t_node,
            const BrowseName & t_browseName,
            const NodeId & t_referenceType)
        {
            return ServerServices::getChildReferencesWithBrowseName(m_connector, t_node, t_browseName, t_referenceType);
        }
    }
}