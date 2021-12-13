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

#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/opcua/aas/provider/AASAggregatorProvider.h>


namespace tests_opcua_agg_provider
{
    using namespace basyx::opcua;

    const int PORT = 5000;
    const char* SERVER_EP = "opc.tcp://localhost:5000";
    const char* AAS_ID = "i40.fab";
    const char* AAS_ID_SHORT = "NexoNutrunner_AAS";
    const char* SM1_ID = "19143e6f-9f36-4f84-a121-3a8d8fd8d835";
    const char* SM1_ID_SHORT = "NexoNutrunner_Asset_1";
    const char* SM2_ID = "19143e6f-9f36-4f84-a121-3a8d8fd8d836";
    const char* SM2_ID_SHORT = "NexoNutrunner_Asset_2";

    basyx::object AAS();
    basyx::object SM1();
    basyx::object SM2();

    class AASAggregatorProviderTest : public ::testing::Test
    {

    public:
        std::shared_ptr<Server> m_server;

        std::unique_ptr<basyx::aas::map::Submodel> sm_1;

        std::unique_ptr<basyx::aas::map::Submodel> sm_2;

        std::shared_ptr<aas::AASAggregatorProvider<>> c_provider;

    public:

        virtual void SetUp()
        {

            m_server = std::make_shared< Server>(PORT, shared::Namespaces::BASYX_NS_URI);

            m_server->initialize();

            m_server->runInBackground();

            while (!m_server->isServerUp());

            c_provider = std::make_shared<aas::AASAggregatorProvider<>>(
                SERVER_EP,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER)
                );
        }

        virtual void TearDown()
        {
            m_server->abort();
        }

        void test_ShellsAPI();

        void test_SubmodelElementsValueAPI();

        void test_SubmodelElementsAPI();
    };

    /* AAS Aggregator Provider*/
    TEST_F(AASAggregatorProviderTest, aggregatorProviderAPI)
    {
        test_ShellsAPI();
        test_SubmodelElementsValueAPI();
        test_SubmodelElementsAPI();
    }

    void AASAggregatorProviderTest::test_ShellsAPI()
    {
        /* API : CREATE  shells/{aasID}*/
        basyx::object::error err = c_provider->setModelPropertyValue("shells/i40.fab", AAS());

        ASSERT_TRUE(err == basyx::object::error::None);

        /* API : GET  shells*/
        auto values = c_provider->getModelPropertyValue("shells");

        ASSERT_TRUE(!values.IsNull());

        /* API : DELETE  shells/{aasID}*/
        err = c_provider->deleteValue("shells/i40.fab");

        ASSERT_TRUE(err == basyx::object::error::None);

        values = c_provider->getModelPropertyValue("shells");

        ASSERT_TRUE(values.empty());

        /* Indentifier mistmatch between model and path */
        basyx::object::error response = c_provider->setModelPropertyValue("shells/i40.fab", AAS());

        values = c_provider->getModelPropertyValue("shells");

        ASSERT_FALSE(values.IsNull());

        err = c_provider->setModelPropertyValue("shells/i40.fab", AAS());

        ASSERT_TRUE(err == basyx::object::error::None);


        /* Delete the AAS*/
        err = c_provider->deleteValue("shells/i40.fab");

        ASSERT_TRUE(err == basyx::object::error::None);
    }

    void AASAggregatorProviderTest::test_SubmodelElementsValueAPI()
    {
        /* GET Test */

        /* Create AAS*/
        basyx::object::error err = c_provider->setModelPropertyValue("shells/i40.fab", AAS());

        ASSERT_TRUE(err == basyx::object::error::None);

        /* Add Submodel1 to AAS*/
        /*API :  CREATE shells/{aasID}/aas/submodels/{smIdShort}*/
        err = c_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1", SM1()
        );

        err = c_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_2", SM2()
        );

        ASSERT_TRUE(err == basyx::object::error::None);

        auto response = c_provider->getModelPropertyValue("shells/i40.fab/aas/submodels");

        ASSERT_FALSE(response.IsNull());
        /* Two submodels */
        ASSERT_EQ(2, response.size());

        /* Get the value of the property */
        /*API :  GET shells/{aasID}/aas/submodels/{smIdShort}/submodelElements/{smEleIdShort}/value*/
        response = c_provider->getModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife/value"
        );

        ASSERT_FALSE(response.IsNull());
        ASSERT_EQ(12, response.Get<int32_t>());

        response = c_provider->getModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife_u64/value"
        );

        /* Set new value to the property*/
        /*API :  UPDATE shells/{aasID}/aas/submodels/{smIdShort}/submodelElements/{smEleIdShort}/value*/
        err = c_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife/value",
            basyx::object(-129));

        ASSERT_TRUE(err == basyx::object::error::None);

        /* Get the new value of the property */
        response = c_provider->getModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife/value"
        );

        ASSERT_FALSE(response.IsNull());
        ASSERT_EQ(-129, response.Get<int32_t>());


        /* Delete the Submodel */
        /*API :  DELETE shells/{aasID}/aas/submodels/{smIdShort} */
        err = c_provider->deleteValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_2");

        ASSERT_TRUE(err == basyx::object::error::None);

        /* Delete the AAS*/
        err = c_provider->deleteValue("shells/i40.fab");

        ASSERT_TRUE(err == basyx::object::error::None);
    }

    void AASAggregatorProviderTest::test_SubmodelElementsAPI()
    {
        using namespace basyx::aas;
        /* GET Test */



        /* Create AAS*/
        basyx::object::error err = c_provider->setModelPropertyValue("shells/i40.fab", AAS());

        ASSERT_TRUE(err == basyx::object::error::None);

        /* Add Submodel1 to AAS*/
        err = c_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1", SM1()
        );

        ASSERT_TRUE(err == basyx::object::error::None);

        /* A complex property */
        map::Property<simple::GYearMonth> p_year_month("year_month");
        p_year_month.setValue(simple::GYearMonth(1, 2));

        /* Add Submodel1 to AAS*/
        /* CREATE */
        err = c_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/year_month", p_year_month.getMap()
        );

        ASSERT_TRUE(err == basyx::object::error::None);

        /* API : GET  shells/{aasId}/aas/submodels/{smIdShort}/submodel/submodelElements*/
        auto response = c_provider->getModelPropertyValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements");

        ASSERT_FALSE(response.IsNull());
        /* Seven Properties */
        ASSERT_EQ(7, response.size());

        /* DELETE */
        response = c_provider->getModelPropertyValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/year_month");

        ASSERT_FALSE(response.IsNull());

        ASSERT_EQ(p_year_month.getMap().getProperty("value"), response.getProperty("value"));
        ASSERT_EQ(p_year_month.getMap().getProperty("valueType"), response.getProperty("valueType"));
        ASSERT_EQ(p_year_month.getMap().getProperty("kind"), response.getProperty("kind"));
        ASSERT_EQ(p_year_month.getMap().getProperty("idShort"), response.getProperty("idShort"));
        ASSERT_EQ(p_year_month.getMap().getProperty("modelType"), response.getProperty("modelType"));

        /* API : GET  shells/{aasId}/aas/submodels/{smIdShort}/submodel/values*/
        response = c_provider->getModelPropertyValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/values");

        ASSERT_FALSE(response.IsNull());
        /* Seven Properties */
        ASSERT_EQ(7, response.size());


        /* DELETE */
        err = c_provider->deleteValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/year_month");

        ASSERT_TRUE(err == basyx::object::error::None);

        /* Delete the AAS*/
        err = c_provider->deleteValue("shells/i40.fab");

        ASSERT_TRUE(err == basyx::object::error::None);
    }

    /* Build AAS  */
    basyx::object AAS()
    {
        using namespace basyx::aas;

        /* Build an AssetAdministrationShell */
        auto aas = std::make_shared<map::AssetAdministrationShell>(AAS_ID_SHORT,
            simple::Identifier::URI(AAS_ID),
            map::Asset{ std::string(), simple::Identifier::Custom(std::string()) }
        );

        /* Set Administration attributes */
        aas->setAdministrativeInformation(basyx::aas::map::AdministrativeInformation("1", "2"));

        return aas->getMap();
    }

    /* Build a submodel */
    basyx::object SM1()
    {
        using namespace basyx::aas;

        /* Build Submodel */
        auto sm_1 = util::make_unique<map::Submodel>(SM1_ID_SHORT, simple::Identifier::Custom(SM1_ID));

        /* Set Administration attributes */
        sm_1->setAdministrativeInformation(basyx::aas::map::AdministrativeInformation("1", "2"));

        /* Build Property and add to Submodel*/
        auto toolSize = sm_1->submodelElements().createElement<map::Property<std::string>>("toolSize");
        toolSize->setValue("3/8 inch square units");

        simple::Key miscRef(KeyElements::Property,
            false,
            KeyType::Custom,
            "19143e6f-9f36-4f84-a121");

        basyx::aas::map::Reference toolReferences({ miscRef });
        toolSize->setValueId(toolReferences);

        /*  Second property */
        auto toolWeight = sm_1->submodelElements().createElement<map::Property<double>>("toolWeight");
        toolWeight->setValue(3.142);

        auto toolWeight_f = sm_1->submodelElements().createElement<map::Property<float>>("toolWeight_f");
        toolWeight_f->setValue(3.142);

        /* Third property */
        auto toolPortable = sm_1->submodelElements().createElement<map::Property<bool>>("toolPort");
        toolPortable->setValue(true);

        /* Fourth property */
        auto toolLife = sm_1->submodelElements().createElement<map::Property<int32_t>>("toolLife");
        toolLife->setValue(12);

        auto tool_year_month = sm_1->submodelElements().createElement<map::Property<simple::GYearMonth>>("toolYearMonth");
        tool_year_month->setValue(simple::GYearMonth(1, 2));

        return sm_1->getMap();
    }

    /* Create a submodel */
    basyx::object SM2()
    {
        using namespace basyx::aas;
        using namespace basyx::xsd_types;

        /* Create Submodel */
        auto sm_2 = util::make_unique<map::Submodel>(SM2_ID_SHORT, simple::Identifier::Custom(SM2_ID));

        sm_2->setAdministrativeInformation(basyx::aas::map::AdministrativeInformation("1", "2"));

        return sm_2->getMap();
    }
}

