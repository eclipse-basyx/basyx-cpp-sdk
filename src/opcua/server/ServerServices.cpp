/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/server/ServerServices.h>

namespace basyx
{
	namespace opcua
	{
		int32_t ServerServices::getNameSpaceIndex(Server& t_server, const std::string & t_namepsaceUri)
		{
			size_t index;
			
			auto namepSpaceUri = shared::string::UAStringFromStdString(t_namepsaceUri);

			auto status = UA_Server_getNamespaceByName(t_server.getUAServer(), namepSpaceUri, &index);

			if (status != UA_STATUSCODE_GOOD)
			{
				return -1;
			}
			return static_cast<int32_t>(index);
		}

		template<>
		UA_StatusCode ServerServices::readValue<std::string>(Server& t_server, const NodeId& t_node, std::string& t_value)
		{
			UA_String value;
			UA_Variant* variant;

			variant = UA_Variant_new();

			if (!t_node.isNull())
			{
				UA_StatusCode status = UA_Server_readValue(t_server.getUAServer(), t_node.getUANode(), variant);

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
		UA_StatusCode ServerServices::writeValue<std::string>(Server& t_server, const NodeId& t_node, std::string t_value)
		{

			UA_String uaStr = shared::string::UAStringFromStdString(t_value);

			return writeValue<UA_String>(t_server, t_node, uaStr);
		}

		UA_StatusCode ServerServices::addVariableNode(Server& t_server,
			const NodeId & t_nodeId,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const NodeId & t_typeDefinition,
			const QualifiedName & t_browseName,
			const VariableAttributes & t_vAttribute)
		{
			UA_StatusCode status;

			status = UA_Server_addVariableNode(t_server.getUAServer(),
				t_nodeId.getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_typeDefinition.getUANode(),
				t_vAttribute.getUA_VariableAttributes(),
				NULL,
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
				writeValue<std::string>(t_server, t_nodeId, "NULL");
			}

			return UA_STATUSCODE_GOOD;
		}

		UA_StatusCode ServerServices::addVariableNode(Server& t_server,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const NodeId& t_typeDefinition,
			const QualifiedName & t_browseName,
			const VariableAttributes & t_vAttribute,
			NodeId & t_outNodeId)
		{
			UA_StatusCode status;
			UA_NodeId outNode;

			status = UA_Server_addVariableNode(t_server.getUAServer(),
				NodeId::nullNode().getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_typeDefinition.getUANode(),
				t_vAttribute.getUA_VariableAttributes(),
				NULL,
				&outNode
			);

			if (status != UA_STATUSCODE_GOOD)
			{
				return status;
			}

			if (NodeId(UA_TYPES[UA_TYPES_STRING].typeId) == NodeId(t_vAttribute.getUA_VariableAttributes().dataType))
			{
				writeValue<std::string>(t_server, NodeId(outNode), "NULL");
			}

			t_outNodeId = std::move(NodeId(outNode));

			return UA_STATUSCODE_GOOD;
		}

		UA_StatusCode ServerServices::addObjectNode(Server & t_server,
			const NodeId & t_nodeId,
			const NodeId & t_parentNodeId,
			const NodeId & t_typeDefinition,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const ObjectAttributes & t_oAttribute)
		{
			return UA_Server_addObjectNode(t_server.getUAServer(),
				t_nodeId.getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_typeDefinition.getUANode(),
				t_oAttribute.getUA_ObjectAttributes(),
				NULL,
				NULL
			);
		}

		UA_StatusCode ServerServices::addObjectNode(Server & t_server,
			const NodeId & t_parentNodeId,
			const NodeId & t_typeDefinition,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const ObjectAttributes & t_oAttribute,
			NodeId & t_outNodeId)
		{
			UA_StatusCode status;
			UA_NodeId outNode;

			status = UA_Server_addObjectNode(t_server.getUAServer(),
				NodeId::nullNode().getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_typeDefinition.getUANode(),
				t_oAttribute.getUA_ObjectAttributes(),
				NULL,
				&outNode
			);

			if (status != UA_STATUSCODE_GOOD)
			{
				return status;
			}

			t_outNodeId = std::move(NodeId(outNode));

			return UA_STATUSCODE_GOOD;
		}

		UA_StatusCode ServerServices::addObjectTypeNode(Server & t_server,
			const NodeId & t_nodeId,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const ObjectTypeAttributes & t_oTypeAttribute)
		{
			return UA_Server_addObjectTypeNode(t_server.getUAServer(),
				t_nodeId.getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_oTypeAttribute.getUA_ObjectTypeAttributes(),
				NULL,
				NULL
			);
		}

		UA_StatusCode ServerServices::addObjectTypeNode(Server & t_server,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const ObjectTypeAttributes & t_oTypeAttribute,
			NodeId & t_outNodeId)
		{
			UA_StatusCode status;
			UA_NodeId outNode;

			status = UA_Server_addObjectTypeNode(t_server.getUAServer(),
				NodeId::nullNode().getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_oTypeAttribute.getUA_ObjectTypeAttributes(),
				NULL,
				&outNode
			);

			if (status != UA_STATUSCODE_GOOD)
			{
				return status;
			}

			t_outNodeId = std::move(NodeId(outNode));

			return UA_STATUSCODE_GOOD;
		}

		UA_StatusCode ServerServices::addForwardReference(Server & t_server,
			const NodeId & t_sourceNodeId,
			const NodeId & t_referenceType,
			const ExpandedNodeId & t_targetNodeID,
			const UA_NodeClass & t_targetNodeClass)
		{
			return UA_Server_addReference(t_server.getUAServer(),
				t_sourceNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_targetNodeID.getUANode(),
				true
			);
		}

		UA_StatusCode ServerServices::addForwardReferenceModellingRuleMandatory(Server & t_server,
			const NodeId & t_sourceNodeId,
			const UA_NodeClass & t_targetNodeClass)
		{
			return addForwardReference(t_server,
				t_sourceNodeId,
				NodeId::numeric(UA_NS0ID_HASMODELLINGRULE),
				ExpandedNodeId::numeric(UA_NS0ID_MODELLINGRULE_MANDATORY),
				t_targetNodeClass
			);
		}

		UA_StatusCode ServerServices::addForwardReferenceModellingRuleOptional(Server & t_server,
			const NodeId & t_sourceNodeId,
			const UA_NodeClass & t_targetNodeClass)
		{
			return addForwardReference(t_server,
				t_sourceNodeId,
				NodeId::numeric(UA_NS0ID_HASMODELLINGRULE),
				ExpandedNodeId::numeric(UA_NS0ID_MODELLINGRULE_OPTIONAL),
				t_targetNodeClass
			);
		}

		UA_StatusCode ServerServices::addMethodNode(Server & t_server,
			const NodeId & t_nodeId,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const MethodAttributes & t_methodAttributes)
		{
			return UA_Server_addMethodNode(
				t_server.getUAServer(),
				t_nodeId.getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_methodAttributes.getUA_MethodAttributes(),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL
			);
		}

		UA_StatusCode ServerServices::addMethodNode(Server & t_server,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const MethodAttributes & t_methodAttributes,
			NodeId & t_outNodeId)
		{
			UA_NodeId outNode = UA_NODEID_NULL;

			auto status = UA_Server_addMethodNode(
				t_server.getUAServer(),
				NodeId::nullNode().getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_methodAttributes.getUA_MethodAttributes(),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				&outNode
			);

			if (status != UA_STATUSCODE_GOOD)
			{
				return status;
			}

			t_outNodeId = std::move(NodeId(outNode));

			return UA_STATUSCODE_GOOD;
		}

		UA_StatusCode ServerServices::addReferenceTypeNode(Server & t_server,
			const NodeId & t_nodeId,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const ReferenceTypeAttributes & t_referenceTypeAttributes)
		{
			return UA_Server_addReferenceTypeNode(
				t_server.getUAServer(),
				t_nodeId.getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_referenceTypeAttributes.getUA_ReferenceTypeAttributes(),
				NULL,
				NULL
			);
		}

		UA_StatusCode ServerServices::addReferenceTypeNode(Server & t_server,
			const NodeId & t_parentNodeId,
			const NodeId & t_referenceType,
			const QualifiedName & t_browseName,
			const ReferenceTypeAttributes & t_referenceTypeAttributes,
			NodeId & t_outNodeId)
		{
			UA_NodeId outNode = UA_NODEID_NULL;

			auto status = UA_Server_addReferenceTypeNode(
				t_server.getUAServer(),
				NodeId::nullNode().getUANode(),
				t_parentNodeId.getUANode(),
				t_referenceType.getUANode(),
				t_browseName.getUA_QualifiedName(),
				t_referenceTypeAttributes.getUA_ReferenceTypeAttributes(),
				NULL,
				&outNode
			);

			if (status != UA_STATUSCODE_GOOD)
			{
				return status;
			}

			t_outNodeId = std::move(NodeId(outNode));

			return UA_STATUSCODE_GOOD;
		}

		UA_StatusCode ServerServices::deleteNode(Server & t_server, const NodeId & t_nodeId)
		{
			return UA_Server_deleteNode(t_server.getUAServer(), t_nodeId.getUANode(), UA_TRUE);
		}

		std::vector<NodeId> ServerServices::getAllChildReferences(Server & t_server, const NodeId & t_node)
		{
			return getChildReferences(t_server, t_node, NodeId::nullNode());
		}

		std::vector<NodeId> ServerServices::getChildReferences(Server & t_server,
			const NodeId & t_node,
			const NodeId & t_referenceType)
		{
			std::vector<NodeId> ret;
			UA_BrowseDescription* bdesc;
			UA_BrowseResult* bres;

			bdesc = UA_BrowseDescription_new();
			bres = UA_BrowseResult_new();

			bdesc->nodeId = t_node.getUANode();
			bdesc->resultMask = UA_BROWSERESULTMASK_ALL;
			bdesc->browseDirection = UA_BROWSEDIRECTION_FORWARD;

			if (!t_referenceType.isNull())
			{
				bdesc->referenceTypeId = t_referenceType.getUANode();
			}

			*bres = UA_Server_browse(t_server.getUAServer(), 0, bdesc);

			if (bres->statusCode != UA_STATUSCODE_GOOD)
			{
				UA_BrowseDescription_delete(bdesc);
				UA_BrowseResult_delete(bres);

				return ret;
			}

			for (size_t i = 0; i < bres->referencesSize; ++i)
			{
				ret.push_back(NodeId(bres->references[i].nodeId.nodeId));
			}

			UA_BrowseDescription_delete(bdesc);
			UA_BrowseResult_delete(bres);
			return ret;
		}

		NodeId ServerServices::getHasTypeDefinition(Server & t_server, const NodeId & t_browseNode)
		{
			auto refs = getChildReferences(t_server, t_browseNode, NodeId::numeric(UA_NS0ID_HASTYPEDEFINITION));

			if (refs.empty() || refs.size() > 1)
			{
				return(NodeId::nullNode());
			}

			return (NodeId(refs[0]));
		}

		NodeId ServerServices::getDataType(Server & t_server, const NodeId & t_variableNodeId)
		{
			UA_NodeId outDataType;

			auto status = UA_Server_readDataType(t_server.getUAServer(), t_variableNodeId.getUANode(), &outDataType);

			if (status != UA_STATUSCODE_GOOD)
			{
				return (NodeId::nullNode());
			}
			return (NodeId(outDataType));
		}

		BrowseName ServerServices::getBrowseNameFromNodeId(Server & t_server, const NodeId & t_node)
		{
			BrowseName bName;

			UA_QualifiedName* qName;

			qName = UA_QualifiedName_new();

			UA_StatusCode status = UA_Server_readBrowseName(t_server.getUAServer(), t_node.getUANode(), qName);

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

		bool ServerServices::isNodeObject(Server & t_server, const NodeId & t_node)
		{
			return (UA_NodeClass::UA_NODECLASS_OBJECT == getNodeClass(t_server, t_node));
		}

		bool ServerServices::isNodeObjectType(Server & t_server, const NodeId & t_node)
		{
			return (UA_NodeClass::UA_NODECLASS_OBJECTTYPE == getNodeClass(t_server, t_node));
		}

		bool ServerServices::isNodeReferenceType(Server & t_server, const NodeId & t_node)
		{
			return (UA_NodeClass::UA_NODECLASS_REFERENCETYPE == getNodeClass(t_server, t_node));
		}

		bool ServerServices::isNodeVariable(Server & t_server, const NodeId & t_node)
		{
			return (UA_NodeClass::UA_NODECLASS_VARIABLE == getNodeClass(t_server, t_node));
		}

		UA_NodeClass ServerServices::getNodeClass(Server & t_server, const NodeId & t_node)
		{
			UA_NodeClass nodeClass;

			auto status = UA_Server_readNodeClass(
				t_server.getUAServer(), t_node.getUANode(), &nodeClass
			);

			if (status = UA_STATUSCODE_GOOD)
			{
				return nodeClass;
			}
			return UA_NODECLASS_UNSPECIFIED;
		}

		NodeId ServerServices::translateBrowsePathToNodeId(Server & t_server, const BrowsePath & t_browsePath)
		{
			NodeId rootNode(t_server.getRootNode().getUANode())
				;
			auto rootNodeBrowseName = getBrowseNameFromNodeId(t_server, rootNode);

			if ((t_browsePath.size() == 1) && (rootNodeBrowseName == t_browsePath.front()))
			{
				return rootNode;
			}
			/* The BrowsePath should start with the Root Node*/
			else if (rootNodeBrowseName == t_browsePath.front())
			{
				return translateBrowsePathToNodeId(t_server,t_browsePath, t_server.getRootNode());
			}
			else
			{
				return NodeId::nullNode();
			}
		}

		NodeId ServerServices::translateBrowsePathToNodeId(Server & t_server, const BrowsePath & t_browsePath, const NodeId & t_startNode)
		{
			NodeId retNode;

			if (t_browsePath.size() < 1)
			{
				return NodeId::nullNode().getUANode();
			}

			auto path = t_browsePath;

			path.erase(path.begin());

			auto status = translateBrowsePathToNodeIdService(t_server, path, t_startNode, retNode);

			if (UA_STATUSCODE_GOOD != status)
			{
				return NodeId::nullNode();;
			}

			return retNode;
		}

		NodeId ServerServices::translateBrowsePathToNodeId(Server & t_server, const std::string & t_browsePath)
		{
			return translateBrowsePathToNodeId(t_server, BrowsePath::fromString(t_browsePath), t_server.getRootNode());
		}

		UA_StatusCode ServerServices::translateBrowsePathToNodeIdService(Server & t_server,
			const BrowsePath & t_browsePath,
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

			UA_BrowsePathResult result = UA_Server_translateBrowsePathToNodeIds(
				t_server.getUAServer(), &browsePath
			);

			retCode = result.statusCode;

			if (result.targetsSize > 0)
			{
				targetNode = result.targets[0].targetId.nodeId;
			}

			UA_BrowsePath_deleteMembers(&browsePath);

			t_targetNode = targetNode;

			return retCode;
		}

		bool ServerServices::doesNodeExists(Server & t_server, const NodeId & t_node, const NodeId & t_parent)
		{
			auto nodes = getAllChildReferences(t_server, t_parent);

			for (auto &node : nodes)
			{
				if (node == t_node)
				{
					return true;
				}
			}
			return false;
		}

		std::vector<NodeId> ServerServices::getChildReferencesWithType(Server & t_server,
			const NodeId & t_node,
			const NodeId & t_typeNode,
			const NodeId & t_referenceType)
		{
			std::vector<NodeId> ret;

			for (NodeId& node : getChildReferences(t_server, t_node, t_referenceType))
			{
				auto typeDefinition = getHasTypeDefinition(t_server, node);

				if (typeDefinition == t_typeNode)
				{
					ret.emplace_back(node.getUANode());
				}
			}
			return ret;
		}

		NodeId ServerServices::getChildReferencesWithBrowseName(Server & t_server,
			const NodeId & t_node,
			const BrowseName & t_browseName,
			const NodeId & t_referenceType)
		{
			for (NodeId& node : getChildReferences(t_server, t_node, t_referenceType))
			{
				auto browseName = getBrowseNameFromNodeId(t_server, node);

				if (browseName == t_browseName)
				{
					return  node.getUANode();
				}
			}
			return NodeId::nullNode().getUANode();
		}

        UA_StatusCode ServerServices::getNodeDescription(Server & t_server, const NodeId & t_node, LocalizedText& t_description)
        {
            UA_LocalizedText description;

            UA_StatusCode status = UA_Server_readDescription(t_server.getUAServer(), t_node.getUANode(), &description);

            t_description = LocalizedText(description);

            return status;
        }

        UA_StatusCode ServerServices::setNodeDescription(Server & t_server, const NodeId & t_node, const LocalizedText & t_description)
        {
            std::string locale = t_description.getLocale();
            std::string text = t_description.getText();

            UA_LocalizedText desc = UA_LOCALIZEDTEXT(const_cast<char*>(locale.c_str()), const_cast<char*>(text.c_str()));

            return UA_Server_writeDescription(t_server.getUAServer(), t_node.getUANode(), desc);
        }

	}
}
