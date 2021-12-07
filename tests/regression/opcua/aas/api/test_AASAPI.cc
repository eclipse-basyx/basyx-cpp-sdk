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

#include <BaSyx/submodel/map_v2/aas/Asset.h>
#include <BaSyx/submodel/map_v2/aas/AssetAdministrationShell.h>
#include <BaSyx/submodel/map_v2/SubModel.h>
#include <BaSyx/submodel/map_v2/submodelelement/property/Property.h>
#include <BaSyx/submodel/map_v2/submodelelement/operation/Operation.h>
#include <BaSyx/submodel/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/util/util.h>
//#include <BaSyx/opcua/aas/api/AASApi.h>
#include <BaSyx/opcua/aas/api/AASApiAssetAdminstrationShell.h>
#include <BaSyx/opcua/aas/api/AASApiSubModel.h>
#include <BaSyx/opcua/aas/api/AASApiSubModelElement.h>
#include <BaSyx/opcua/aas/provider/AASModelProviderHelpers.h>
#include <BaSyx/opcua/aas/provider/AASModelProvider.h>
#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodelAliases.h>

using namespace basyx::submodel::map;
using namespace basyx::opcua;
using namespace basyx::opcua::aas;
using namespace basyx::opcua::aas::metamodel;

namespace basyx
{
	namespace tests
	{
		namespace opcua
		{
			//void addOperationsToSubModelManually(basyx::opcua::Client* t_client, UA_NodeId _subModelNode);
			//void addOperationNodes(UA_Server *server);
			std::shared_ptr<AssetAdministrationShell> buildTestAAS();
		}
	}
}

class AASAPITest : public ::testing::Test
{	
public:
	std::unique_ptr<Client> m_client;
    std::unique_ptr<Server> m_server;
	std::shared_ptr<AssetAdministrationShell> aas;
public:

	virtual void SetUp() 
	{
        m_server = util::make_unique<Server>(4844);

		m_client = util::make_unique<Client>("opc.tcp://localhost:4844", Namespaces::BASYX_NS_URI);

		aas = basyx::tests::opcua::buildTestAAS();
	}

	virtual void TearDown()
	{
		/* Shutdown the server */
		m_server->abort();
	}

    /* SubModel Element Property */
    void TestAASSubModelElements(){

		auto server = m_server.get();
		auto client = m_client.get();
        
        server->initialize();
		server->addNameSpace(basyx::opcua::Server::DEFAULT_NS_URI);
        /* Add method nodes to Server which will be mapped to Operations */
		//basyx::tests::opcua::addOperationNodes(server->getUAServer());
		server->runInBackground();

        /* Wait until the server is Up*/
        while(!server->isServerUp());
        /* Initialize the client */
		client->connect();

        TestProperties();
        //TestOperationsSignature();
        //TestOperationsInvoke();

    }
    void TestProperties()
	{
		using namespace basyx::opcua::aas;

		auto server = m_server.get();
		auto client = m_client.get();

        /* Define OPCUA AAS metamodel */
        AASMetamodel::define<Client>(2, *client);

		auto api = util::make_unique<AASApiAssetAdminstrationShell<Client>>(
			*client, basyx::opcua::utils::node::createNodeIdNumericDefault(UA_NS0ID_OBJECTSFOLDER)
		);

        /* Translate aas to OPCUA */
		api->createAssetAdministrationShell(aas);

        /* Get the AssetAdministrationShell from OPCUA server*/
        auto aasFromOPCUA = api->getAssetAdministrationShell(
		"https://boschrexroth.com/shells/nutrunner/0608842010/1234567890222"
        );


        /* Assertions*/
        /* AssetAdministrationShell attributes */
        ASSERT_EQ("1", *aasFromOPCUA->getAdministrativeInformation().getVersion());
        ASSERT_EQ("2", *aasFromOPCUA->getAdministrativeInformation().getRevision());
        ASSERT_EQ("NexoNutrunner_AAS", aasFromOPCUA->getIdShort());
        /* Get SubModels */
        /* DISABLED for map_v2 fix now */
        for(std::size_t i = 0; i < aasFromOPCUA->getSubmodels().size(); ++i) {
		    const auto& subModelFromOPCUA = aasFromOPCUA->getSubmodels().getElement(i);

            if((subModelFromOPCUA->getIdentification().getId() == "19143e6f-9f36-4f84-a121-3a8d8fd8d835")){

                ASSERT_EQ("1", *subModelFromOPCUA->getAdministrativeInformation().getVersion());
                ASSERT_EQ("2", *subModelFromOPCUA->getAdministrativeInformation().getRevision());
                ASSERT_EQ("NexoNutrunner_Asset_1", subModelFromOPCUA->getIdShort());
                /* Get SubModel Element */
                auto toolSizeSMElement     = subModelFromOPCUA->submodelElements().getElement("toolSize");
                auto toolRadiusSMElement   = subModelFromOPCUA->submodelElements().getElement("toolRadius");
                auto toolWeightSMElement   = subModelFromOPCUA->submodelElements().getElement("toolWeight");
                auto toolPortableSMElement = subModelFromOPCUA->submodelElements().getElement("toolPort");
                auto toolLifeSMElement     = subModelFromOPCUA->submodelElements().getElement("toolLife");
                /* Get the Property values */
                auto toolSizeValue         = getPropertyValue<std::string>(toolSizeSMElement);
                auto toolSizeValueType     = getPropertyValueType(toolSizeSMElement);
                auto toolRadiusValue       = getPropertyValue<float>(toolRadiusSMElement);
				auto toolRadiusValueType   = getPropertyValueType(toolRadiusSMElement);
                auto toolWeightValue       = getPropertyValue<double>(toolWeightSMElement);
				auto toolWeightValueType   = getPropertyValueType(toolWeightSMElement);
                auto toolPortableValue     = getPropertyValue<bool>(toolPortableSMElement);
				auto toolPortableValueType = getPropertyValueType(toolPortableSMElement);
                auto toolLifeValue         = getPropertyValue<int32_t>(toolLifeSMElement);
				auto toolLifeValueType     = getPropertyValueType(toolLifeSMElement);

                ASSERT_EQ("3/8 inch square units", toolSizeValue);
                ASSERT_EQ("string", toolSizeValueType);
                ASSERT_FLOAT_EQ(20.99234, toolRadiusValue);
				ASSERT_EQ("float", toolRadiusValueType);
                ASSERT_DOUBLE_EQ(3.142, toolWeightValue);
				ASSERT_EQ("double", toolWeightValueType);
                ASSERT_EQ(true , toolPortableValue);
				ASSERT_EQ("boolean", toolPortableValueType);
                ASSERT_EQ(12   , toolLifeValue);
				ASSERT_EQ("int", toolLifeValueType);
            }
        }
    }
#if OPERATIONS_TEST
    /* SubModel Element Operation */
     void TestOperationsSignature()
	 {
		 auto server = m_server.get();
		 auto client = m_client.get();

		 auto api = util::make_unique<AASApiSubModel<Client>>(
		 	 *client, basyx::opcua::utils::node::createNodeIdNumericDefault(UA_NS0ID_OBJECTSFOLDER)
		 );

         /* Get the SubModel*/
		 auto subModelNode = node::getSubModelNode(
			 *client,
			 basyx::opcua::utils::node::createNodeIdNumericDefault(UA_NS0ID_OBJECTSFOLDER),
			 "https://boschrexroth.com/shells/nutrunner/0608842010/1234567890222",
			 "19143e6f-9f36-4f84-a121-3a8d8fd8d835"
		 );

		 basyx::tests::opcua::addOperationsToSubModelManually(client, subModelNode);

		auto subModel = api->getSubModel(
			"https://boschrexroth.com/shells/nutrunner/0608842010/1234567890222",
			"19143e6f-9f36-4f84-a121-3a8d8fd8d835"
		);

        auto copyOperation =  dynamic_cast<IOperation*>(subModel->submodelElements().getElement("Copy"));
        
        ASSERT_EQ("Copy", copyOperation->getIdShort());
        ASSERT_EQ("Instance", KindtoString(copyOperation->getKind()));
        /* Check the input arguments */
        auto inpBoolEle = copyOperation->getInputVariables().getElement("bool_input_arg");
        ASSERT_EQ("bool_input_arg", inpBoolEle->getIdShort());
        ASSERT_TRUE((typeid(bool) == getOperationTypeId(inpBoolEle)));

        auto inpInt32Ele = copyOperation->getInputVariables().getElement("int_input_arg");
        ASSERT_EQ("int_input_arg",  inpInt32Ele->getIdShort());
        ASSERT_TRUE((typeid(int) == getOperationTypeId(inpInt32Ele)));

        auto inpFloatEle = copyOperation->getInputVariables().getElement("float_input_arg");
        ASSERT_EQ("float_input_arg",  inpFloatEle->getIdShort());
        ASSERT_TRUE((typeid(float) == getOperationTypeId(inpFloatEle)));
    
        auto inpDoubleEle = copyOperation->getInputVariables().getElement("double_input_arg");
        ASSERT_EQ("double_input_arg",  inpDoubleEle->getIdShort());
        ASSERT_TRUE((typeid(double) == getOperationTypeId(inpDoubleEle)));

        auto inpStringEle = copyOperation->getInputVariables().getElement("string_input_arg");
        ASSERT_EQ("string_input_arg",  inpStringEle->getIdShort());
        ASSERT_TRUE((typeid(std::string) == getOperationTypeId(inpStringEle)));

        /* Check the output arguments */
        auto outBoolEle = copyOperation->getOutputVariables().getElement("bool_output_arg");
        ASSERT_EQ("bool_output_arg", outBoolEle->getIdShort());
        ASSERT_TRUE((typeid(bool) == getOperationTypeId(outBoolEle)));

        auto outInt32Ele = copyOperation->getOutputVariables().getElement("int_output_arg");
        ASSERT_EQ("int_output_arg",  outInt32Ele->getIdShort());
        ASSERT_TRUE((typeid(int) == getOperationTypeId(outInt32Ele)));

        auto outFloatEle = copyOperation->getOutputVariables().getElement("float_output_arg");
        ASSERT_EQ("float_output_arg",  outFloatEle->getIdShort());
        ASSERT_TRUE((typeid(float) == getOperationTypeId(outFloatEle)));
    
        auto outDoubleEle = copyOperation->getOutputVariables().getElement("double_output_arg");
        ASSERT_EQ("double_output_arg",  outDoubleEle->getIdShort());
        ASSERT_TRUE((typeid(double) == getOperationTypeId(outDoubleEle)));

        auto outStringEle = copyOperation->getOutputVariables().getElement("string_output_arg");
        ASSERT_EQ("string_output_arg",  outStringEle->getIdShort());
        ASSERT_TRUE((typeid(std::string) == getOperationTypeId(outStringEle)));

        auto average3Operation = dynamic_cast<IOperation*>(subModel->submodelElements().getElement("Average3"));
  
        ASSERT_EQ("Average3", average3Operation->getIdShort());
        ASSERT_EQ("Instance", KindtoString(average3Operation->getKind()));
        /* Check the input arguments */
        ASSERT_EQ("double_input_arg_1", average3Operation->getInputVariables().getElement("double_input_arg_1")->getIdShort());
        ASSERT_EQ("double_input_arg_2",  average3Operation->getInputVariables().getElement("double_input_arg_2")->getIdShort());
        ASSERT_EQ("double_input_arg_3", average3Operation->getInputVariables().getElement("double_input_arg_3")->getIdShort());
        /* Check the output arguments */
        ASSERT_EQ("return_average_output_arg", average3Operation->getOutputVariables().getElement("return_average_output_arg")->getIdShort());

     }

     void TestOperationsInvoke()
	 {
		 auto server = m_server.get();
		 auto client = m_client.get();

        /*A SubModel which has Properties as Operation Arguments */
        auto sm = std::make_shared<SubModel>(
            "opSubModel",
            Identifier::Custom("opSubModel")
        );

        auto operation = std::make_shared<AASOperation<>>(
			*client,
            client->translateBrowsePathToNodeId("0:Objects/2:OperationFolder/2:Copy"),
            "test",
            client->translateBrowsePathToNodeId("0:Objects/2:OperationFolder/2:Copy/2:Operation")
        );

        /* Create input arguments */
        auto boolProperty = sm->submodelElements().createElement<Property_t<bool>>("bool_input_arg");
        boolProperty->setValue(true);
        auto intProperty = sm->submodelElements().createElement<Property_t<int32_t>>("int_input_arg");
        intProperty->setValue(5772159);
        auto floatProperty = sm->submodelElements().createElement<Property_t<float>>("float_input_arg");
        floatProperty->setValue(3.141592);
        auto doubleProperty = sm->submodelElements().createElement<Property_t<double>>("double_input_arg");
        doubleProperty->setValue(2.718281828459045);
        auto stringProperty = sm->submodelElements().createElement<Property_t<std::string>>("string_input_arg");
        stringProperty->setValue("some text");

        /* Invoke the Operation "Copy" */
        auto& res = operation->invoke(sm->submodelElements());
        /* Results of Operation "Copy" */
        ASSERT_EQ(true, getPropertyValue<bool>(res.getElement("bool_output_arg")));
        ASSERT_EQ(5772159, getPropertyValue<int32_t>(res.getElement("int_output_arg")));
        ASSERT_FLOAT_EQ (3.141592, getPropertyValue<float>(res.getElement("float_output_arg")));
        ASSERT_DOUBLE_EQ(2.718281828459045, getPropertyValue<double>(res.getElement("double_output_arg")));
        ASSERT_EQ("some text", getPropertyValue<std::string>(res.getElement("string_output_arg")));   
    }
#endif
};

TEST_F(AASAPITest, AASOPCUA)
{
    TestAASSubModelElements();
}
