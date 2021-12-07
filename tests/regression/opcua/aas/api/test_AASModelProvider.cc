/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include "gtest/gtest.h"
#include <BaSyx/shared/object.h>
#include <string>
#include <cstdint>
#include <thread>
#include <csignal>

#include <BaSyx/util/util.h>
#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/submodel/map_v2/aas/Asset.h>
#include <BaSyx/submodel/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/submodel/map_v2/SubModel.h>
#include <BaSyx/submodel/map_v2/submodelelement/property/Property.h>
#include <BaSyx/submodel/map_v2/submodelelement/operation/Operation.h>
#include <BaSyx/submodel/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/opcua/aas/provider/AASModelProvider.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodelAliases.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>



using namespace basyx::submodel::map;
using namespace basyx::opcua;
using namespace basyx::opcua::aas;
using namespace basyx::opcua::aas::metamodel;
using namespace basyx::submodel::map;

namespace basyx
{
	namespace tests
	{
		namespace opcua
		{
			std::shared_ptr<AssetAdministrationShell> buildTestAAS();
			//void addOperationNodes(UA_Server *server);
			//void addOperationsToSubModelManually(basyx::opcua::Client* t_client, UA_NodeId _subModelNode);
		}
	}
}

class AASModelProviderTest : public ::testing::Test
{
public:
	std::unique_ptr<Server> m_server;
	std::shared_ptr<AssetAdministrationShell> aas;
	std::shared_ptr<SubModel> sm;
	std::shared_ptr <AASModelProvider<basyx::opcua::Client>> provider;
public:

	virtual void SetUp() 
	{
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
	
	void TestAPIModelProvider()
	{
		auto server = m_server.get();
		/* Server thread */
		server->initialize();
		/* Add basyx namespace */
		server->addNameSpace(basyx::opcua::Server::DEFAULT_NS_URI);
		/* Add method nodes to Server which will be mapped to Operations */
		//basyx::tests::opcua::addOperationNodes(server->getUAServer());
		/* Detach the server thread and run in background */
		server->runInBackground();

		while (!server->isServerUp());

		provider = std::make_shared<AASModelProvider<>>(
			"opc.tcp://localhost:4840",
			utils::node::createNodeIdNumericDefault(UA_NS0ID_OBJECTSFOLDER)
		);

		TestCreate();
		TestGet();
		TestUpdate();
		TestDelete();

		/* Shutdown the server */
		server->abort();

	}

	void TestCreate()
	{
		auto aasMap = aas->getMap();

		basyx::object aas;

		provider->createValue("aasList", aasMap);

		/*Check whether the AAS is created successfully */
		auto aasObject = provider->getModelPropertyValue("aasList/shells/nutrunner/060884");

		/* Should not return a null object */
		ASSERT_NE(aasObject.getProperty("AssetAdministrationShell"), basyx::object::make_null());

		auto aasContentObject = provider->getModelPropertyValue("aasList/shells/nutrunner/060884/aas");

		/* Should not return a null object */
		ASSERT_FALSE(aasContentObject.IsNull());

		const std::string& idShort = aasContentObject.getProperty("idShort").Get<std::string&>();
		const std::string& id      = aasContentObject.getProperty("identifier").getProperty("id").Get<std::string&>();
		const std::string& idType  = aasContentObject.getProperty("identifier").getProperty("idType").Get<std::string&>();

		/* Check the identification */
		ASSERT_EQ("NexoNutrunner_AAS", idShort);
		ASSERT_EQ("shells/nutrunner/060884", id);
		ASSERT_EQ("URI", idType);

	}

	void TestGet()
	{
		/* GET test for a SubModel and a Property */
		auto smMap = basyx::object(sm->getMap());

		/* Add the Submodel to the existing AssetAdministrationShell via AAS API */
		auto errStat = provider->createValue("aasList/shells/nutrunner/060884/aas/submodels", smMap);

		auto smObject = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835"
		);

		const std::string& idShort = smObject.getProperty("idShort").Get<std::string&>();
		const std::string& id = smObject.getProperty("identifier").getProperty("id").Get<std::string&>();
		const std::string& idType = smObject.getProperty("identifier").getProperty("idType").Get<std::string&>();

		/* Check the identification */
		ASSERT_EQ("NexoNutrunner_Asset_1", idShort);
		ASSERT_EQ("19143e6f-9f36-4f84-a121-3a8d8fd8d835", id);
		ASSERT_EQ("Custom", idType);

		/* Get property values */
		auto objValToolWeight = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835/properties/toolWeight/value"
		);

		auto objValToolSize = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835/properties/toolSize/value"
		);

		auto objValtToolPortable = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835/properties/toolPort/value"
		);

		auto objValToolLife = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835/properties/toolLife/value"
		);

		ASSERT_DOUBLE_EQ(3.142, objValToolWeight.Get<double>());
		ASSERT_EQ("3/8 inch square units", objValToolSize.Get<std::string>());
		ASSERT_EQ(true, objValtToolPortable.Get<bool>());
		ASSERT_EQ(12, objValToolLife.Get<int>());

	}

	void TestUpdate()
	{

		/* Update the value */
		provider->setModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835/properties/toolLife/value",
			basyx::object(571)
		);
		
		/* Get the updated value*/
		auto objValToolLife = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835/properties/toolLife/value"
		);

		ASSERT_EQ(571, objValToolLife.Get<int>());
	}

	void TestDelete()
	{
		/* Delete the SubModel */
		provider->deleteValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835"
		);

		/* GET should return a null object */
		auto smObject = provider->getModelPropertyValue(
			"aasList/shells/nutrunner/060884/aas/submodels/19143e6f-9f36-4f84-a121-3a8d8fd8d835"
		);

		ASSERT_TRUE(smObject.IsNull());
	}

};


TEST_F(AASModelProviderTest, APIModelProvider)
{
	TestAPIModelProvider();
}



