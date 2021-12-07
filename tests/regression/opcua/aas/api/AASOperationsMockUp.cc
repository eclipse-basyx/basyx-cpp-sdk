/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/



#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/opcua/aas/model/AASOperation.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/submodel/map_v2/aas/Asset.h>
#include <BaSyx/submodel/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/submodel/map_v2/SubModel.h>
#include <BaSyx/submodel/map_v2/submodelelement/property/Property.h>
#include <BaSyx/submodel/map_v2/submodelelement/operation/Operation.h>
#include <BaSyx/submodel/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/util/util.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodelAliases.h>


namespace basyx
{
	namespace tests
	{
		namespace opcua
		{
			using namespace basyx::opcua;
			using namespace basyx::opcua::aas;
			using namespace basyx::opcua::aas::metamodel;
			using namespace basyx::submodel::map;
#if 0
			void addOperationNodes(UA_Server *server);
			void addOperationsToSubModelManually(basyx::opcua::Client* t_client, UA_NodeId _subModelNode);

			static UA_StatusCode copy__callback(UA_Server *server,
				const UA_NodeId *sessionId, void *sessionContext,
				const UA_NodeId *methodId, void *methodContext,
				const UA_NodeId *objectId, void *objectContext,
				size_t inputSize, const UA_Variant *input,
				size_t outputSize, UA_Variant *output);
			static UA_StatusCode average3__callback(UA_Server *server,
				const UA_NodeId *sessionId, void *sessionContext,
				const UA_NodeId *methodId, void *methodContext,
				const UA_NodeId *objectId, void *objectContext,
				size_t inputSize, const UA_Variant *input,
				size_t outputSize, UA_Variant *output);


			void addOperationsToSubModelManually(basyx::opcua::Client* t_client, UA_NodeId _subModelNode) {
				/* Operation Test Case*/
				auto operation1 = std::make_shared<AASOperation<Client>>(*t_client, _subModelNode, "Copy");
				auto operation2 = std::make_shared<AASOperation<Client>>(*t_client, _subModelNode, "Average3");
				/* Operation NoedId */
				auto op1NodeId = UA_NODEID_STRING(operation1->getConnector().getNamespaceIndexDefault(), "operation1");
				auto op2NodeId = UA_NODEID_STRING(operation2->getConnector().getNamespaceIndexDefault(), "operation2");
				/* Create two AASOperationType  Instance */
				auto oattr1 = t_client->createObjectAttributes("Operation::Copy", "Operation::Copy");
				auto oattr2 = t_client->createObjectAttributes("Operation::Average3", "Operation::Average3");

				t_client->addObjectNodeHasComponent(op1NodeId,
					operation1->getParentNodeId().getUANode(),
					"Operation::Copy",
					AASOperationType::getNodeId(t_client->getNamespaceIndexDefault()).getUANode(),
					oattr1);

				t_client->addObjectNodeHasComponent(op2NodeId,
					operation2->getParentNodeId().getUANode(),
					"Operation::Average3",
					AASOperationType::getNodeId(t_client->getNamespaceIndexDefault()).getUANode(),
					oattr2);

				/* Remove the default Operation Node */
				auto defaultMethodNode1 = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op1NodeId), {t_client->getNamespaceIndexDefault(),"Operation"} },
					op1NodeId
				);
				auto defaultMethodNode2 = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op2NodeId), {t_client->getNamespaceIndexDefault(),"Operation"} },
					op2NodeId
				);

				/* Delete the default method Nodes*/
				t_client->deleteNodeWithReferences(defaultMethodNode1);
				t_client->deleteNodeWithReferences(defaultMethodNode2);

				/* Create a referece to Operation "Copy" method node already in the server*/
				/* Get Copy NodeId*/
				auto copyMethod1NodeId = t_client->translateBrowsePathToNodeId(
					{ {t_client->getNamespaceIndexDefault(),"OperationFolder"},
					 {t_client->getNamespaceIndexDefault(),"Copy"},
					 {t_client->getNamespaceIndexDefault(),"Operation"} },
					UA_NODEID_STRING(t_client->getNamespaceIndexDefault(), "OperationFolder")
				);
				auto average2NodeId = t_client->translateBrowsePathToNodeId(
					{ {t_client->getNamespaceIndexDefault(),"OperationFolder"},
					 {t_client->getNamespaceIndexDefault(),"Average3"},
					 {t_client->getNamespaceIndexDefault(),"Operation"} },
					UA_NODEID_STRING(t_client->getNamespaceIndexDefault(), "OperationFolder")
				);

				//t_client->deleteNodeWithReferences()
				auto copyModethodNodeNameStr = copyMethod1NodeId.identifier.string;
				t_client->addForwardReference(
					op1NodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
					UA_EXPANDEDNODEID_STRING(
						t_client->getNamespaceIndexDefault(),
						const_cast<char*>(utils::conversion::UAStringToStdString(&copyModethodNodeNameStr).c_str())),
					UA_NODECLASS_METHOD
				);

				auto average3ModethodNodeNameStr = average2NodeId.identifier.string;
				t_client->addForwardReference(
					op2NodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
					UA_EXPANDEDNODEID_STRING(
						t_client->getNamespaceIndexDefault(),
						const_cast<char*>(utils::conversion::UAStringToStdString(&average3ModethodNodeNameStr).c_str())),
					UA_NODECLASS_METHOD
				);
				/* Set IdShort, Category and Kind of OperationNode */
				/* We have to do this manually because the t_client doesnot
				   have methods to update IdShort */
				auto operation1IdShortNodeId = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op1NodeId),
					{t_client->getNamespaceIndexDefault(), IAASReferableType::AttrNames::BrowseText_IdShort} },
					op1NodeId
				);
				auto operation2IdShortNodeId = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op1NodeId),
					{t_client->getNamespaceIndexDefault(), IAASReferableType::AttrNames::BrowseText_IdShort} },
					op2NodeId
				);

				auto operation1CategoryNodeId = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op1NodeId),
					{t_client->getNamespaceIndexDefault(), IAASReferableType::AttrNames::BrowseText_Category} },
					op1NodeId
				);
				auto operation2CategoryNodeId = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op2NodeId),
					{t_client->getNamespaceIndexDefault(), IAASReferableType::AttrNames::BrowseText_Category} },
					op2NodeId
				);

				auto operation1KindNodeId = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op1NodeId),
					{t_client->getNamespaceIndexDefault(), AASSubModelElementType::AttrNames::BrowseText_Kind} },
					op1NodeId
				);
				auto operation2KindNodeId = t_client->translateBrowsePathToNodeId(
					{ t_client->getBrowseNameFromNodeId(op2NodeId),
					{t_client->getNamespaceIndexDefault(), AASSubModelElementType::AttrNames::BrowseText_Kind} },
					op2NodeId
				);

				t_client->writeValue(operation1IdShortNodeId, UA_STRING("Copy"));
				t_client->writeValue(operation1CategoryNodeId, UA_STRING("Copy Value Category"));
				t_client->writeValue(operation1KindNodeId, UA_STRING("Instance"));

				t_client->writeValue(operation2IdShortNodeId, UA_STRING("Average3"));
				t_client->writeValue(operation2CategoryNodeId, UA_STRING("Average3 Value Category"));
				t_client->writeValue(operation2KindNodeId, UA_STRING("Instance"));
			}

			/* Copies the input argumets to the output arguments */
			static UA_StatusCode copy__callback(UA_Server *server,
				const UA_NodeId *sessionId, void *sessionContext,
				const UA_NodeId *methodId, void *methodContext,
				const UA_NodeId *objectId, void *objectContext,
				size_t inputSize, const UA_Variant *input,
				size_t outputSize, UA_Variant *output) {

				auto boolValPtr = (UA_Boolean*)input[0].data;
				UA_Variant_setScalarCopy(output, boolValPtr, &UA_TYPES[UA_TYPES_BOOLEAN]);
				output++;

				auto intValPtr = (UA_Int32*)input[1].data;
				UA_Variant_setScalarCopy(output, intValPtr, &UA_TYPES[UA_TYPES_INT32]);
				output++;

				auto floatValPtr = (UA_Float*)input[2].data;
				UA_Variant_setScalarCopy(output, floatValPtr, &UA_TYPES[UA_TYPES_FLOAT]);
				output++;

				auto doubleValPtr = (UA_Double*)input[3].data;
				UA_Variant_setScalarCopy(output, doubleValPtr, &UA_TYPES[UA_TYPES_DOUBLE]);
				output++;

				auto strPtr = (UA_String*)input[4].data;
				auto value = utils::conversion::UAStringToStdString(strPtr);
				UA_String newString = UA_STRING((char*)value.c_str());
				UA_Variant_setScalarCopy(output, &newString, &UA_TYPES[UA_TYPES_STRING]);

				UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "operation__callback() invoked");

				return UA_STATUSCODE_GOOD;
			}

			/* Writes the Average of three double input arguments to output arguments */
			static UA_StatusCode average3__callback(UA_Server *server,
				const UA_NodeId *sessionId, void *sessionContext,
				const UA_NodeId *methodId, void *methodContext,
				const UA_NodeId *objectId, void *objectContext,
				size_t inputSize, const UA_Variant *input,
				size_t outputSize, UA_Variant *output) {

				auto n1 = *(UA_Double*)input[0].data;
				auto n2 = *(UA_Double*)input[1].data;
				auto n3 = *(UA_Double*)input[2].data;

				auto result = (n1 + n2 + n3) / 3.0;

				UA_Variant_setScalarCopy(output, &result, &UA_TYPES[UA_TYPES_DOUBLE]);
				UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "average3__callback() invoked");

				return UA_STATUSCODE_GOOD;
			}

			void addOperationNodes(UA_Server *server) {

				size_t ns;
				UA_Server_getNamespaceByName(server, UA_STRING((char*)Server::BASYX_NS_URI), &ns);

				/* Copy method Arguments */
				/* Five input arguments */
				UA_Argument copyInputArguments[5];

				UA_Argument_init(&copyInputArguments[0]);
				copyInputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "Bool input argument");
				copyInputArguments[0].name = UA_STRING("bool_input_arg");
				copyInputArguments[0].dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
				copyInputArguments[0].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyInputArguments[1]);
				copyInputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "Int input argument");
				copyInputArguments[1].name = UA_STRING("int_input_arg");
				copyInputArguments[1].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
				copyInputArguments[1].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyInputArguments[2]);
				copyInputArguments[2].description = UA_LOCALIZEDTEXT("en-US", "Float input argument");
				copyInputArguments[2].name = UA_STRING("float_input_arg");
				copyInputArguments[2].dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
				copyInputArguments[2].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyInputArguments[3]);
				copyInputArguments[3].description = UA_LOCALIZEDTEXT("en-US", "Double input argument");
				copyInputArguments[3].name = UA_STRING("double_input_arg");
				copyInputArguments[3].dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
				copyInputArguments[3].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyInputArguments[4]);
				copyInputArguments[4].description = UA_LOCALIZEDTEXT("en-US", "String input argument");
				copyInputArguments[4].name = UA_STRING("string_input_arg");
				copyInputArguments[4].dataType = UA_TYPES[UA_TYPES_STRING].typeId;
				copyInputArguments[4].valueRank = UA_VALUERANK_SCALAR;

				/* Five output argument */
				UA_Argument copyOutputArguments[5];
				UA_Argument_init(&copyOutputArguments[0]);
				copyOutputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "Bool output argument");
				copyOutputArguments[0].name = UA_STRING("bool_output_arg");
				copyOutputArguments[0].dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
				copyOutputArguments[0].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyOutputArguments[1]);
				copyOutputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "Int output argument");
				copyOutputArguments[1].name = UA_STRING("int_output_arg");
				copyOutputArguments[1].dataType = UA_TYPES[UA_TYPES_INT32].typeId;
				copyOutputArguments[1].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyOutputArguments[2]);
				copyOutputArguments[2].description = UA_LOCALIZEDTEXT("en-US", "Float output argument");
				copyOutputArguments[2].name = UA_STRING("float_output_arg");
				copyOutputArguments[2].dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
				copyOutputArguments[2].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyOutputArguments[3]);
				copyOutputArguments[3].description = UA_LOCALIZEDTEXT("en-US", "Double output argument");
				copyOutputArguments[3].name = UA_STRING("double_output_arg");
				copyOutputArguments[3].dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
				copyOutputArguments[3].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&copyOutputArguments[4]);
				copyOutputArguments[4].description = UA_LOCALIZEDTEXT("en-US", "String output argument");
				copyOutputArguments[4].name = UA_STRING("string_output_arg");
				copyOutputArguments[4].dataType = UA_TYPES[UA_TYPES_STRING].typeId;
				copyOutputArguments[4].valueRank = UA_VALUERANK_SCALAR;

				/* Average3 method Arguments */
				/* Three input arguments     */
				UA_Argument averageInputArguments[3];

				UA_Argument_init(&averageInputArguments[0]);
				averageInputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "Double input argument 1");
				averageInputArguments[0].name = UA_STRING("double_input_arg_1");
				averageInputArguments[0].dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
				averageInputArguments[0].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&averageInputArguments[1]);
				averageInputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "Double input argument 2");
				averageInputArguments[1].name = UA_STRING("double_input_arg_2");
				averageInputArguments[1].dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
				averageInputArguments[1].valueRank = UA_VALUERANK_SCALAR;

				UA_Argument_init(&averageInputArguments[2]);
				averageInputArguments[2].description = UA_LOCALIZEDTEXT("en-US", "Double input argument 3");
				averageInputArguments[2].name = UA_STRING("double_input_arg_3");
				averageInputArguments[2].dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
				averageInputArguments[2].valueRank = UA_VALUERANK_SCALAR;

				/* One output argument */
				UA_Argument averageOutputArguments[1];
				UA_Argument_init(averageOutputArguments);
				averageOutputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "Double average output argument");
				averageOutputArguments[0].name = UA_STRING("return_average_output_arg");
				averageOutputArguments[0].dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
				averageOutputArguments[0].valueRank = UA_VALUERANK_SCALAR;

				/* Add the method node */
				UA_MethodAttributes incAttr = UA_MethodAttributes_default;
				incAttr.description = UA_LOCALIZEDTEXT("en-US", "Operation");
				incAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Operation");
				incAttr.executable = true;
				incAttr.userExecutable = true;

				UA_NodeId operationFolderNodeId = UA_NODEID_STRING(ns, "OperationFolder");
				UA_NodeId copyNodeId, avg3NodeId;
				UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
				oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "OperationFolder");
				UA_StatusCode status = UA_Server_addObjectNode(server, operationFolderNodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
					UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
					UA_QUALIFIEDNAME(ns, "OperationFolder"), UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
					oAttr, NULL, NULL);

				UA_ObjectAttributes oCopyAttr = UA_ObjectAttributes_default;
				oCopyAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Copy");
				UA_ObjectAttributes oAvg3Attr = UA_ObjectAttributes_default;
				oAvg3Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Average3");

				status = UA_Server_addObjectNode(server, UA_NODEID_NULL,
					operationFolderNodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
					UA_QUALIFIEDNAME(ns, "Copy"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
					oCopyAttr, NULL, &copyNodeId);

				status = UA_Server_addObjectNode(server, UA_NODEID_NULL,
					operationFolderNodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
					UA_QUALIFIEDNAME(ns, "Average3"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
					oAvg3Attr, NULL, &avg3NodeId);

				status = UA_Server_addMethodNode(server, UA_NODEID_STRING(ns, "Operation1"),
					copyNodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
					UA_QUALIFIEDNAME(ns, "Operation"),
					incAttr, &copy__callback,
					5, copyInputArguments, 5, copyOutputArguments,
					NULL, NULL);

				status = UA_Server_addMethodNode(server, UA_NODEID_STRING(ns, "Operation2"),
					avg3NodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
					UA_QUALIFIEDNAME(ns, "Operation"),
					incAttr, &average3__callback,
					3, averageInputArguments, 1, averageOutputArguments,
					NULL, NULL);
			}
#endif 
			std::shared_ptr<AssetAdministrationShell> buildTestAAS() {
				/*Create a dummy asset for metamodel compatibility sake*/
				Asset asset{ "", Identifier::Custom("") };//Dummy Asset
				/* Create an AssetAdministrationShell */
				auto aas{
					std::make_shared<AssetAdministrationShell>(
						"NexoNutrunner_AAS", /*IdShort*/
						Identifier::URI("https://boschrexroth.com/shells/nutrunner/0608842010/1234567890222"),/*Identification*/
						asset
					)
				};
				/* Set Administration attributes */
				aas->getAdministrativeInformation().setRevision("1");
				aas->getAdministrativeInformation().setVersion("2");
				/* Set Description */
				aas->getDescription().add("en-US", "Nexo wireless cordless screwdriver");
				/* Create SubModel */
				auto tighteningControl_1 = util::make_unique<SubModel>(
					"NexoNutrunner_Asset_1", /*IdShort*/
					Identifier::Custom("19143e6f-9f36-4f84-a121-3a8d8fd8d835") /*Identification*/
					);
				/* Set Administration attributes */
				tighteningControl_1->getAdministrativeInformation().setRevision("1");
				tighteningControl_1->getAdministrativeInformation().setVersion("2");
				/* Create SubModel */
				auto tighteningControl_2 = util::make_unique<SubModel>(
					"NexoNutrunner_Asset_2",
					Identifier::Custom("19143e6f-9f36-4f84-a121-3a8d8fd8d836")
					);

				tighteningControl_2->getAdministrativeInformation().setRevision("1");
				tighteningControl_2->getAdministrativeInformation().setVersion("2");
				//.addElement(std::move(extractedSM))

				/*Create Property and add to SubModel*/
				auto toolSize = tighteningControl_1->submodelElements().createElement<Property<std::string>>("toolSize");
				toolSize->setValue("3/8 inch square units");
				/* DISABLED since "void setValueId(const api::IReference & valueId)" not implemented */
				Key miscRef(KeyElements::Property,
					false,
					KeyType::Custom,
					"19143e6f-9f36-4f84-a121");
				Reference toolReferences({ miscRef });
				toolSize->setValueId(toolReferences);
				toolSize->setValueType("string");

				/* Create the second property */
				auto toolRadius = tighteningControl_1->submodelElements().createElement<Property<float>>("toolRadius");
				toolRadius->setValue(20.99234);
				toolRadius->setValueType("float");
				/* Create the second property */
				auto toolWeight = tighteningControl_1->submodelElements().createElement<Property<double>>("toolWeight");
				toolWeight->setValue(3.142);
				toolWeight->setValueType("double");
				/* Create the third property */
				auto toolPortable = tighteningControl_1->submodelElements().createElement<Property<bool>>("toolPort");
				toolPortable->setValue(true);
				toolPortable->setValueType("boolean");
				/* Create the fourth property */
				auto toolLife = tighteningControl_1->submodelElements().createElement<Property<int32_t>>("toolLife");
				toolLife->setValue(12);
				toolLife->setValueType("int");

				aas->getSubmodels().addElement(std::move(tighteningControl_1));
				aas->getSubmodels().addElement(std::move(tighteningControl_2));

				return std::move(aas);
			}
		}
	}
}