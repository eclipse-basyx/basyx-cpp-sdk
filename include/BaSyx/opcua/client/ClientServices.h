/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef CLIENT_SERVIES_H
#define CLIENT_SERVIES_H

#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/ExpandedNodeId.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/LocalizedText.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/common/VariableAttributes.h>
#include <BaSyx/opcua/common/MethodAttributes.h>
#include <BaSyx/opcua/common/ReferenceTypeAttributes.h>

namespace basyx
{
    namespace opcua
    {
        class ClientServices
        {
        public:
            static int32_t getNameSpaceIndex(Client& t_client, const std::string& t_namepsaceUri);

            template<class TYPE>
            static UA_StatusCode readValue(Client& t_client, const NodeId& t_nodeId, TYPE& t_value)
            {
                UA_Variant* variant;

                variant = UA_Variant_new();

                auto status = UA_Client_readValueAttribute(t_client.getUAClient(), t_nodeId.getUANode(), variant);

                if (status != UA_STATUSCODE_GOOD)
                {
                    return status;
                }

                if (UA_Variant_isEmpty(variant))
                {
                    UA_Variant_delete(variant);

                    return UA_STATUSCODE_BADDATAUNAVAILABLE;
                }

                t_value = *(static_cast<TYPE*>(variant->data));

                UA_Variant_delete(variant);

                return UA_STATUSCODE_GOOD;
            }

            template<class TYPE>
            static UA_StatusCode writeValue_(Client& t_client, const NodeId& t_node, const TYPE& t_value);

            template<class TYPE>
            static UA_StatusCode writeValue(Client& t_client, const NodeId& t_node, TYPE t_value)
            {

                UA_Variant* variant;

                UA_StatusCode status;

                if (!t_node.isNull())
                {
                    variant = UA_Variant_new();

                    status = UA_Variant_setScalarCopy(variant, &t_value, &UA_TYPES[opcua::shared::UATypeId(t_value)]);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        UA_Variant_delete(variant);

                        return status;
                    }

                    status = UA_Client_writeValueAttribute(t_client.getUAClient(), t_node.getUANode(), variant);

                    UA_Variant_delete(variant);

                    return status;
                }
                return UA_STATUSCODE_BADNODEIDINVALID;
            }

            template<uint32_t TYPE_ID>
            static bool isOfTypeNode(Client& t_client, const NodeId& t_node)
            {
                UA_Variant* variant;
                UA_StatusCode status;

                variant = UA_Variant_new();

                if (!t_node.isNull())
                {
                    status = UA_Client_readValueAttribute(t_client.getUAClient(), t_node.getUANode(), variant);
                }
                else
                {
                    UA_Variant_delete(variant);

                    return false;
                }

                if (status != UA_STATUSCODE_GOOD)
                {

                    UA_Variant_delete(variant);

                    return false;

                }

                auto typeNodeId = NodeId(variant->type->typeId);

                auto typeNodeIdExpected = NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 0, TYPE_ID);

                UA_Variant_delete(variant);

                return  typeNodeIdExpected == typeNodeId;
            }

            static UA_StatusCode addVariableNode(Client& t_client,
                const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const NodeId& t_typeDefinition,
                const QualifiedName& t_browseName,
                const VariableAttributes& t_vAttribute);

            static UA_StatusCode addVariableNode(Client& t_client,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const NodeId& t_typeDefinition,
                const QualifiedName& t_browseName,
                const VariableAttributes& t_vAttribute,
                NodeId& t_outNodeId);

            static UA_StatusCode addObjectNode(Client& t_client,
                const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_typeDefinition,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectAttributes& t_vAttribute);

            static UA_StatusCode addObjectNode(Client& t_client,
                const NodeId& t_parentNodeId,
                const NodeId& t_typeDefinition,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectAttributes& t_vAttribute,
                NodeId& t_outNodeId);

            static UA_StatusCode addObjectTypeNode(Client& t_client,
                const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectTypeAttributes& t_oTypeAttribute);

            static UA_StatusCode addObjectTypeNode(Client& t_client,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ObjectTypeAttributes& t_oTypeAttribute,
                NodeId& t_outNodeId);

            static UA_StatusCode addMethodNode(Client& t_client,
                const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const MethodAttributes& t_methodAttributes
            );

            static UA_StatusCode addMethodNode(Client& t_client,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const MethodAttributes& t_methodAttributes,
                NodeId& t_outNodeId);

            static UA_StatusCode addReferenceTypeNode(Client& t_client,
                const NodeId& t_nodeId,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ReferenceTypeAttributes& t_referenceTypeAttributes);

            static UA_StatusCode addReferenceTypeNode(Client& t_client,
                const NodeId& t_parentNodeId,
                const NodeId& t_referenceType,
                const QualifiedName& t_browseName,
                const ReferenceTypeAttributes& t_referenceTypeAttributes,
                NodeId& t_outNodeId);

            static UA_StatusCode addForwardReference(Client& t_client,
                const NodeId& t_sourceNodeId,
                const NodeId& t_referenceType,
                const ExpandedNodeId& t_targetNodeID,
                const UA_NodeClass& t_targetNodeClass);

            static UA_StatusCode addForwardReferenceModellingRuleMandatory(Client& t_client,
                const NodeId& t_sourceNodeId,
                const UA_NodeClass& t_targetNodeClass);

            static UA_StatusCode addForwardReferenceModellingRuleOptional(Client& t_client,
                const NodeId & t_sourceNodeId,
                const UA_NodeClass & t_targetNodeClass);

            static UA_StatusCode deleteNode(Client& t_client, const NodeId& t_nodeId);

            static std::vector<NodeId> getAllChildReferences(Client& t_client, const NodeId& t_Node);

            static std::vector<NodeId> getChildReferences(Client& t_client,
                const NodeId& t_node,
                const NodeId& t_referenceType);

            static NodeId getHasTypeDefinition(Client& t_client, const NodeId & t_browseNode);

            static std::vector<NodeId> getChildReferencesWithType(Client& t_client,
                const NodeId& t_node,
                const NodeId& t_typeNode,
                const NodeId& t_referenceType);

            static NodeId getChildReferencesWithBrowseName(Client& t_client,
                const NodeId& t_node,
                const BrowseName& t_browseName,
                const NodeId& t_referenceType);

            static NodeId getDataType(Client& t_client, const NodeId& t_variableNodeId);

            static BrowseName getBrowseNameFromNodeId(Client& t_client, const NodeId& t_node);

            static bool isNodeObject(Client& t_client, const NodeId& t_node);

            static bool isNodeObjectType(Client& t_client, const NodeId& t_node);

            static bool isNodeReferenceType(Client& t_client, const NodeId& t_node);

            static bool isNodeVariable(Client& t_client, const NodeId& t_node);

            static UA_NodeClass getNodeClass(Client& t_client, const NodeId& t_node);

            static NodeId translateBrowsePathToNodeId(Client& t_client, const BrowsePath& t_browsePath);

            static NodeId translateBrowsePathToNodeId(Client& t_client,
                const BrowsePath& t_browsePath,
                const NodeId& t_startNode);

            static NodeId translateBrowsePathToNodeId(Client& t_client, const std::string& t_browsePathStr);

            static UA_StatusCode translateBrowsePathToNodeIdService(Client& t_client,
                const BrowsePath& t_browsePath,
                const NodeId & t_startNode,
                NodeId & t_targetNode);

            static bool doesNodeExists(Client& t_client, const NodeId& t_node, const NodeId& t_parent);

            static UA_StatusCode getNodeDescription(Client& t_client, const NodeId& t_node, LocalizedText& t_description);

            static UA_StatusCode setNodeDescription(Client& t_client, const NodeId& t_node, const LocalizedText& t_description);
        };

        template<>
        UA_StatusCode ClientServices::readValue<std::string>(Client& t_client, const NodeId& t_node, std::string& t_value);

        template<>
        UA_StatusCode ClientServices::writeValue<std::string>(Client& t_client, const NodeId& t_node, std::string t_value);

        template<>
        UA_StatusCode ClientServices::writeValue_<std::string>(Client & t_client, const NodeId & t_node, const std::string & t_value);
}
}

#endif