/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/client/ClientServices.h>

namespace basyx
{
    namespace opcua
    {
        template<>
        UA_StatusCode ClientServices::readValue<std::string>(Client& t_client, const NodeId& t_node, std::string& t_value)
        {
            UA_String value;
            UA_Variant* variant;

            variant = UA_Variant_new();

            if (!t_node.isNull())
            {
                UA_StatusCode status = UA_Client_readValueAttribute(t_client.getUAClient(), t_node.getUANode(), variant);

                if (status != UA_STATUSCODE_GOOD)
                {
                    UA_Variant_delete(variant);

                    return status;
                }

                value = *(UA_String*)variant->data;
                t_value = shared::string::UAStringToStdString(&value);
            }

            UA_Variant_delete(variant);

            return UA_STATUSCODE_GOOD;
        }

        template<>
        UA_StatusCode ClientServices::writeValue<std::string>(Client& t_client, const NodeId& t_node, std::string t_value)
        {

            UA_String uaStr = shared::string::UAStringFromStdString(t_value);

            return writeValue<UA_String>(t_client, t_node, uaStr);
        }

        template<>
        inline UA_StatusCode ClientServices::writeValue_<std::string>(Client & t_client, const NodeId & t_node, const std::string & t_value)
        {
            return writeValue<std::string>(t_client, t_node, t_value);
        }

        int32_t ClientServices::getNameSpaceIndex(Client& t_client, const std::string & t_namepsaceUri)
        {
            uint16_t ret = 0;
            UA_StatusCode status = UA_STATUSCODE_GOOD;

            UA_String ns_uri = shared::string::UAStringFromStdString(t_namepsaceUri);

            status = UA_Client_NamespaceGetIndex(t_client.getUAClient(), &ns_uri, &ret);

            if (status != UA_STATUSCODE_GOOD)
            {
                return Client::NAMESPACE_UNKOWN;
            }

            return static_cast<int>(ret);
        }

        UA_StatusCode ClientServices::addVariableNode(Client& t_client,
            const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName & t_browseName,
            const VariableAttributes & t_vAttribute)
        {
            UA_StatusCode status;

            status = UA_Client_addVariableNode(t_client.getUAClient(),
                t_nodeId.getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_typeDefinition.getUANode(),
                t_vAttribute.getUA_VariableAttributes(),
                NULL
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                return status;
            }
            /* This is a workaroud for string variable nodes. Reading an uninitialied string nodes
               results a segmenation fault, thus until such behaviour is fixed in the opcua stack
               this nodes should be explicitly written to indicate that the node is uninitialized */
            if (NodeId(UA_TYPES[UA_TYPES_STRING].typeId) == NodeId(t_vAttribute.getUA_VariableAttributes().dataType))
            {
                writeValue<std::string>(t_client, t_nodeId, "NULL");
            }

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode ClientServices::addVariableNode(Client& t_client,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const NodeId& t_typeDefinition,
            const QualifiedName & t_browseName,
            const VariableAttributes & t_vAttribute,
            NodeId & t_outNodeId)
        {
            UA_StatusCode status;
            UA_NodeId outNode;

            status = UA_Client_addVariableNode(t_client.getUAClient(),
                NodeId::nullNode().getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_typeDefinition.getUANode(),
                t_vAttribute.getUA_VariableAttributes(),
                &outNode
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                return status;
            }

            if (NodeId(UA_TYPES[UA_TYPES_STRING].typeId) == NodeId(t_vAttribute.getUA_VariableAttributes().dataType))
            {
                writeValue<std::string>(t_client, outNode, "NULL");
            }

            t_outNodeId = std::move(NodeId(outNode));

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode ClientServices::addObjectNode(Client& t_client,
            const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId& t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute)
        {
            return UA_Client_addObjectNode(t_client.getUAClient(),
                t_nodeId.getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_typeDefinition.getUANode(),
                t_vAttribute.getUA_ObjectAttributes(),
                NULL
            );
        }

        UA_StatusCode ClientServices::addObjectNode(Client& t_client,
            const NodeId & t_parentNodeId,
            const NodeId & t_typeDefinition,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectAttributes & t_vAttribute,
            NodeId & t_outNodeId)
        {
            UA_NodeId outNode;
            auto status = UA_Client_addObjectNode(t_client.getUAClient(),
                NodeId::nullNode().getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_typeDefinition.getUANode(),
                t_vAttribute.getUA_ObjectAttributes(),
                &outNode
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                return status;
            }

            t_outNodeId = std::move(NodeId(outNode));

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode ClientServices::addObjectTypeNode(Client& t_client,
            const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute)
        {
            return UA_Client_addObjectTypeNode(t_client.getUAClient(),
                t_nodeId.getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_oTypeAttribute.getUA_ObjectTypeAttributes(),
                NULL
            );
        }

        UA_StatusCode ClientServices::addObjectTypeNode(Client& t_client,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ObjectTypeAttributes & t_oTypeAttribute,
            NodeId & t_outNodeId)
        {
            UA_NodeId outNode;
            auto status = UA_Client_addObjectTypeNode(t_client.getUAClient(),
                NodeId::nullNode().getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_oTypeAttribute.getUA_ObjectTypeAttributes(),
                &outNode
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                return status;
            }

            t_outNodeId = std::move(NodeId(outNode));

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode ClientServices::addMethodNode(Client & t_client,
            const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes)
        {

            return UA_Client_addMethodNode(
                t_client.getUAClient(),
                t_nodeId.getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_methodAttributes.getUA_MethodAttributes(),
                NULL
            );
        }

        UA_StatusCode ClientServices::addMethodNode(Client & t_client,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const MethodAttributes & t_methodAttributes,
            NodeId & t_outNodeId)
        {
            UA_NodeId outNode;

            auto status = UA_Client_addMethodNode(
                t_client.getUAClient(),
                NodeId::nullNode().getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_methodAttributes.getUA_MethodAttributes(),
                &outNode
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                return status;
            }

            t_outNodeId = std::move(NodeId(outNode));

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode ClientServices::addReferenceTypeNode(Client & t_client,
            const NodeId & t_nodeId,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ReferenceTypeAttributes & t_referenceTypeAttributes)
        {
            return UA_Client_addReferenceTypeNode(
                t_client.getUAClient(),
                t_nodeId.getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_referenceTypeAttributes.getUA_ReferenceTypeAttributes(),
                NULL
            );
        }

        UA_StatusCode ClientServices::addReferenceTypeNode(Client & t_client,
            const NodeId & t_parentNodeId,
            const NodeId & t_referenceType,
            const QualifiedName & t_browseName,
            const ReferenceTypeAttributes & t_referenceTypeAttributes,
            NodeId & t_outNodeId)
        {
            UA_NodeId outNode = UA_NODEID_NULL;

            auto status = UA_Client_addReferenceTypeNode(
                t_client.getUAClient(),
                NodeId::nullNode().getUANode(),
                t_parentNodeId.getUANode(),
                t_referenceType.getUANode(),
                t_browseName.getUA_QualifiedName(),
                t_referenceTypeAttributes.getUA_ReferenceTypeAttributes(),
                &outNode
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                return status;
            }

            t_outNodeId = std::move(NodeId(outNode));

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode ClientServices::addForwardReference(Client& t_client,
            const NodeId & t_sourceNodeId,
            const NodeId & t_referenceType,
            const ExpandedNodeId & t_targetNodeID,
            const UA_NodeClass & t_targetNodeClass)
        {
            return UA_Client_addReference(t_client.getUAClient(),
                t_sourceNodeId.getUANode(),
                t_referenceType.getUANode(),
                true,
                UA_STRING_NULL,
                t_targetNodeID.getUANode(),
                t_targetNodeClass
            );
        }

        UA_StatusCode ClientServices::addForwardReferenceModellingRuleMandatory(Client& t_client,
            const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass)
        {
            return addForwardReference(
                t_client, t_sourceNodeId,
                NodeId::numeric(UA_NS0ID_HASMODELLINGRULE),
                ExpandedNodeId::numeric(UA_NS0ID_MODELLINGRULE_MANDATORY),
                t_targetNodeClass
            );
        }

        UA_StatusCode ClientServices::addForwardReferenceModellingRuleOptional(Client& t_client,
            const NodeId & t_sourceNodeId,
            const UA_NodeClass & t_targetNodeClass)
        {
            return addForwardReference(
                t_client, t_sourceNodeId,
                NodeId::numeric(UA_NS0ID_HASMODELLINGRULE),
                ExpandedNodeId::numeric(UA_NS0ID_MODELLINGRULE_OPTIONAL),
                t_targetNodeClass
            );
        }

        UA_StatusCode ClientServices::deleteNode(Client & t_client, const NodeId & t_nodeId)
        {
            return UA_Client_deleteNode(t_client.getUAClient(), t_nodeId.getUANode(), UA_TRUE);
        }

        std::vector<NodeId> ClientServices::getAllChildReferences(Client& t_client, const NodeId & t_browseNode)
        {
            std::vector<NodeId> ret;
            UA_BrowseRequest* browseRequest;
            UA_BrowseResponse* browseResponse;

            browseRequest = UA_BrowseRequest_new();
            browseResponse = UA_BrowseResponse_new();

            browseRequest->requestedMaxReferencesPerNode = 0;
            browseRequest->nodesToBrowse = UA_BrowseDescription_new();
            browseRequest->nodesToBrowseSize = 1;
            browseRequest->nodesToBrowse[0].nodeId = t_browseNode.getUANode();
            browseRequest->nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL;

            *browseResponse = UA_Client_Service_browse(t_client.getUAClient(), *browseRequest);

            auto i(0), j(0);
            while (i < browseResponse->resultsSize)
            {
                while (j < browseResponse->results[i].referencesSize)
                {
                    UA_ReferenceDescription *desc_ref = &(browseResponse->results[i].references[j]);

                    ret.push_back(desc_ref->nodeId.nodeId);

                    j++;
                }
                i++;
            }

            UA_BrowseRequest_delete(browseRequest);
            UA_BrowseResponse_delete(browseResponse);

            return ret;
        }

        std::vector<NodeId> ClientServices::getChildReferences(Client& t_client, const NodeId & t_browseNode, const NodeId & t_referenceType)
        {
            std::vector<NodeId> ret;
            UA_BrowseRequest* browseRequest;
            UA_BrowseResponse* browseResponse;

            browseRequest = UA_BrowseRequest_new();
            browseResponse = UA_BrowseResponse_new();

            browseRequest->requestedMaxReferencesPerNode = 0;
            browseRequest->nodesToBrowse = UA_BrowseDescription_new();
            browseRequest->nodesToBrowseSize = 1;
            browseRequest->nodesToBrowse[0].nodeId = t_browseNode.getUANode();
            browseRequest->nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL;

            *browseResponse = UA_Client_Service_browse(t_client.getUAClient(), *browseRequest);

            auto i(0), j(0);
            while (i < browseResponse->resultsSize)
            {
                while (j < browseResponse->results[i].referencesSize)
                {
                    UA_ReferenceDescription *desc_ref = &(browseResponse->results[i].references[j]);

                    NodeId refNode(desc_ref->referenceTypeId);

                    if (refNode == t_referenceType)
                    {
                        ret.push_back(desc_ref->nodeId.nodeId);
                    }
                    j++;
                }
                i++;
            }

            UA_BrowseRequest_delete(browseRequest);
            UA_BrowseResponse_delete(browseResponse);

            return ret;
        }

        NodeId ClientServices::getHasTypeDefinition(Client& t_client, const NodeId & t_browseNode)
        {
            auto refs = getChildReferences(t_client, t_browseNode, NodeId::numeric(UA_NS0ID_HASTYPEDEFINITION));

            if (refs.empty() || refs.size() > 1)
            {
                return (NodeId::nullNode().getUANode());
            }

            return (NodeId(refs[0]));
        }

        std::vector<NodeId> ClientServices::getChildReferencesWithType(Client & t_client,
            const NodeId & t_node,
            const NodeId & t_typeNode,
            const NodeId & t_referenceType)
        {
            std::vector<NodeId> ret;

            for (NodeId& node : getChildReferences(t_client, t_node, t_referenceType))
            {
                auto typeDefinition = getHasTypeDefinition(t_client, node);

                if (typeDefinition == t_typeNode)
                {
                    ret.push_back(node);
                }
            }
            return ret;
        }

        NodeId ClientServices::getChildReferencesWithBrowseName(Client & t_client,
            const NodeId & t_node,
            const BrowseName & t_browseName,
            const NodeId & t_referenceType)
        {
            for (NodeId& node : getChildReferences(t_client, t_node, t_referenceType))
            {
                auto browseName = getBrowseNameFromNodeId(t_client, node);

                if (browseName == t_browseName)
                {
                    return node;
                }
            }
            return NodeId::nullNode();
        }

        NodeId ClientServices::getDataType(Client& t_client, const NodeId& t_variableNodeId)
        {
            UA_NodeId outDataType;

            auto status = UA_Client_readDataTypeAttribute(t_client.getUAClient(), t_variableNodeId.getUANode(), &outDataType);

            if (status != UA_STATUSCODE_GOOD)
            {
                return NodeId::nullNode();
            }
            return outDataType;
        }

        BrowseName ClientServices::getBrowseNameFromNodeId(Client& t_client, const NodeId & t_node)
        {
            BrowseName bName;

            UA_QualifiedName* qName;

            qName = UA_QualifiedName_new();

            UA_StatusCode status = UA_Client_readBrowseNameAttribute(t_client.getUAClient(), t_node.getUANode(), qName);

            if (UA_STATUSCODE_GOOD != status)
            {
                UA_QualifiedName_delete(qName);
                return bName;
            }

            auto ns = qName->namespaceIndex;
            auto str = shared::string::UAStringToStdString(&qName->name);

            UA_QualifiedName_delete(qName);

            return BrowseName(ns, str);
        }

        bool ClientServices::isNodeObject(Client& t_client, const NodeId & t_node)
        {
            return (UA_NodeClass::UA_NODECLASS_OBJECT == getNodeClass(t_client, t_node));
        }

        bool ClientServices::isNodeObjectType(Client& t_client, const NodeId & t_node)
        {
            return (UA_NodeClass::UA_NODECLASS_OBJECTTYPE == getNodeClass(t_client, t_node));
        }

        bool ClientServices::isNodeReferenceType(Client& t_client, const NodeId & t_node)
        {
            return (UA_NodeClass::UA_NODECLASS_REFERENCETYPE == getNodeClass(t_client, t_node));
        }

        bool ClientServices::isNodeVariable(Client& t_client, const NodeId & t_node)
        {
            return (UA_NodeClass::UA_NODECLASS_VARIABLE == getNodeClass(t_client, t_node));
        }

        UA_NodeClass ClientServices::getNodeClass(Client& t_client, const NodeId & t_node)
        {
            UA_NodeClass nodeClass;

            auto status = UA_Client_readNodeClassAttribute(
                t_client.getUAClient(), t_node.getUANode(), &nodeClass
            );

            if (status = UA_STATUSCODE_GOOD)
            {
                return nodeClass;
            }
            return UA_NODECLASS_UNSPECIFIED;
        }

        NodeId ClientServices::translateBrowsePathToNodeId(Client& t_client, const BrowsePath & t_browsePath)
        {
            NodeId rootNode(t_client.getRootNode().getUANode());

            auto rootNodeBrowseName = getBrowseNameFromNodeId(t_client, rootNode);

            if ((t_browsePath.size() == 1) && (rootNodeBrowseName == t_browsePath.front()))
            {
                return rootNode.getUANode();
            }
            /* The BrowsePath should start with the Root Node*/
            else if (rootNodeBrowseName == t_browsePath.front())
            {
                return translateBrowsePathToNodeId(t_client, t_browsePath, t_client.getRootNode());
            }
            else
            {
                return NodeId::nullNode().getUANode();
            }
        }

        NodeId ClientServices::translateBrowsePathToNodeId(Client& t_client,
            const BrowsePath & t_browsePath,
            const NodeId & t_startNode)
        {
            NodeId retNode;

            if (t_browsePath.size() < 1)
            {
                return std::move(NodeId::nullNode());
            }

            auto path = t_browsePath;

            path.erase(path.begin());

            auto status = translateBrowsePathToNodeIdService(t_client, path, t_startNode, retNode);

            if (UA_STATUSCODE_GOOD != status)
            {
                return NodeId::nullNode();
            }

            return retNode.getUANode();
        }

        NodeId ClientServices::translateBrowsePathToNodeId(Client & t_client, const std::string & t_browsePathStr)
        {
            return translateBrowsePathToNodeId(t_client, BrowsePath::fromString(t_browsePathStr), t_client.getRootNode());
        }

        UA_StatusCode ClientServices::translateBrowsePathToNodeIdService(Client& t_client,
            const BrowsePath& t_browsePath,
            const NodeId & t_startNode,
            NodeId & t_targetNode)
        {
            UA_StatusCode retCode;

            UA_NodeId targetNode = UA_NODEID_NULL;

            UA_BrowsePath browsePath;
            UA_BrowsePath_init(&browsePath);

            browsePath.startingNode = t_startNode.getUANode();

            browsePath.relativePath.elements = (UA_RelativePathElement*)UA_Array_new(
                t_browsePath.size(), &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]
            );

            browsePath.relativePath.elementsSize = t_browsePath.size();

            int i(0);
            for (auto &path : t_browsePath)
            {
                UA_RelativePathElement *elem = &browsePath.relativePath.elements[i];
                elem->referenceTypeId = UA_NODEID_NULL;

                auto ns = path.getNamespaceIdx();
                const char* name = path.getText().c_str();

                elem->targetName = UA_QUALIFIEDNAME_ALLOC(ns, name);

                i++;
            }

            UA_TranslateBrowsePathsToNodeIdsRequest request;
            UA_TranslateBrowsePathsToNodeIdsRequest_init(&request);
            request.browsePaths = &browsePath;
            request.browsePathsSize = 1;


            UA_TranslateBrowsePathsToNodeIdsResponse response = UA_Client_Service_translateBrowsePathsToNodeIds(
                t_client.getUAClient(), request
            );

            retCode = response.responseHeader.serviceResult;

            if (response.results != NULL)
            {
                if (response.results[0].targets != NULL)
                {
                    targetNode = response.results[0].targets[0].targetId.nodeId;
                }

                UA_BrowsePath_deleteMembers(&browsePath);
                UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);

                t_targetNode = targetNode;
            }

            return retCode;
        }

        bool ClientServices::doesNodeExists(Client& t_client, const NodeId & t_node, const NodeId & t_parent)
        {
            auto nodes = getAllChildReferences(t_client, t_parent);

            for (auto &node : nodes)
            {
                if (node == t_node)
                {
                    return true;
                }
            }
            return false;
        }

       UA_StatusCode ClientServices::getNodeDescription(Client & t_client, const NodeId & t_node, LocalizedText & t_description)
       {
           UA_LocalizedText description;

           UA_StatusCode status = UA_Client_readDescriptionAttribute(t_client.getUAClient(), t_node.getUANode(), &description);

           t_description = LocalizedText (description);

           return status;
       }

       UA_StatusCode ClientServices::setNodeDescription(Client & t_client, const NodeId & t_node, const LocalizedText& t_description)
       {
           std::string locale = t_description.getLocale();
           std::string text = t_description.getText();

           UA_LocalizedText desc = UA_LOCALIZEDTEXT(const_cast<char*>(locale.c_str()), const_cast<char*>(text.c_str()));

           return UA_Client_writeDescriptionAttribute(t_client.getUAClient(), t_node.getUANode(), &desc);
       }
    }
}

