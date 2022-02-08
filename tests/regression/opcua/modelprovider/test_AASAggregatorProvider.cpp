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
    const char* AAS_ID = "i40.fab";
    const char* AAS_ID_SHORT = "NexoNutrunner_AAS";
    const char* SM1_ID = "19143e6f-9f36-4f84-a121-3a8d8fd8d835";
    const char* SM1_ID_SHORT = "NexoNutrunner_Asset_1";
    const char* SM2_ID = "19143e6f-9f36-4f84-a121-3a8d8fd8d836";
    const char* SM2_ID_SHORT = "NexoNutrunner_Asset_2";

    class AASAggregatorProviderTest : public ::testing::Test
    {

    protected:
        const char* endpoint = "opc.tcp://localhost:4842";
        std::unique_ptr<basyx::opcua::Server> m_server;
        std::shared_ptr<aas::AASAggregatorProvider<>> m_provider;
        std::thread m_serverThread;
    public:
        virtual void SetUp()
        {
            m_server = util::make_unique<basyx::opcua::Server>(4842, shared::Namespaces::BASYX_NS_URI);
            m_server->initialize();
            m_serverThread = std::thread{ [this]() {m_server->run(); } };

            m_provider = util::make_unique<aas::AASAggregatorProvider<>>(
                endpoint,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER)
                );
        }

        virtual void TearDown()
        {
            m_server->abort();
            m_serverThread.join();
        }

        basyx::object AAS();
        basyx::object SM1();
        basyx::object SM2();
    };

    TEST_F(AASAggregatorProviderTest, ShellsApi)
    {
        /* API : CREATE  shells/{aasID}*/
        basyx::object::error err = m_provider->setModelPropertyValue("shells/i40.fab", AAS());
        ASSERT_TRUE(err == basyx::object::error::None);
        /* API : GET  shells*/
        auto values = m_provider->getModelPropertyValue("shells");
        ASSERT_TRUE(!values.IsNull());
        /* API : DELETE  shells/{aasID}*/
        err = m_provider->deleteValue("shells/i40.fab");
        ASSERT_TRUE(err == basyx::object::error::None);
        values = m_provider->getModelPropertyValue("shells");
        ASSERT_TRUE(values.empty());
        /* Indentifier mistmatch between model and path */
        basyx::object::error response = m_provider->setModelPropertyValue("shells/i40.fab", AAS());
        values = m_provider->getModelPropertyValue("shells");
        ASSERT_FALSE(values.IsNull());
        err = m_provider->setModelPropertyValue("shells/i40.fab", AAS());
        ASSERT_TRUE(err == basyx::object::error::None);
        /* Delete the AAS*/
        err = m_provider->deleteValue("shells/i40.fab");
        ASSERT_TRUE(err == basyx::object::error::None);
    }

    TEST_F(AASAggregatorProviderTest, SubmodelElementsValueApi)
    {
        /* GET Test */
        /* Create AAS*/
        basyx::object::error err = m_provider->setModelPropertyValue("shells/i40.fab", AAS());
        ASSERT_TRUE(err == basyx::object::error::None);
        /* Add Submodel1 to AAS*/
        /*API :  CREATE shells/{aasID}/aas/submodels/{smIdShort}*/
        err = m_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1", SM1()
        );
        err = m_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_2", SM2()
        );
        ASSERT_TRUE(err == basyx::object::error::None);
        auto response = m_provider->getModelPropertyValue("shells/i40.fab/aas/submodels");
        ASSERT_FALSE(response.IsNull());
        /* Two submodels */
        ASSERT_EQ(2, response.size());
        /* Get the value of the property */
        /*API :  GET shells/{aasID}/aas/submodels/{smIdShort}/submodelElements/{smEleIdShort}/value*/
        response = m_provider->getModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife/value"
        );
        ASSERT_FALSE(response.IsNull());
        ASSERT_EQ(12, response.Get<int32_t>());
        response = m_provider->getModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife_u64/value"
        );
        /* Set new value to the property*/
        /*API :  UPDATE shells/{aasID}/aas/submodels/{smIdShort}/submodelElements/{smEleIdShort}/value*/
        err = m_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife/value",
            basyx::object(-129));
        ASSERT_TRUE(err == basyx::object::error::None);
        /* Get the new value of the property */
        response = m_provider->getModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/toolLife/value"
        );
        ASSERT_FALSE(response.IsNull());
        ASSERT_EQ(-129, response.Get<int32_t>());
        /* Delete the Submodel */
        /*API :  DELETE shells/{aasID}/aas/submodels/{smIdShort} */
        err = m_provider->deleteValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_2");
        ASSERT_TRUE(err == basyx::object::error::None);
        /* Delete the AAS*/
        err = m_provider->deleteValue("shells/i40.fab");
        ASSERT_TRUE(err == basyx::object::error::None);
    }

    TEST_F(AASAggregatorProviderTest, SubmodelElementsApi)
    {
        using namespace basyx::aas;
        /* GET Test */
        /* Create AAS*/
        basyx::object::error err = m_provider->setModelPropertyValue("shells/i40.fab", AAS());
        ASSERT_TRUE(err == basyx::object::error::None);
        /* Add Submodel1 to AAS*/
        err = m_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1", SM1()
        );
        ASSERT_TRUE(err == basyx::object::error::None);
        /* A complex property */
        map::Property<simple::GYearMonth> p_year_month("year_month");
        p_year_month.setValue(simple::GYearMonth(1, 2));
        /* Add Submodel1 to AAS*/
        /* CREATE */
        err = m_provider->setModelPropertyValue(
            "shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/year_month", p_year_month.getMap()
        );
        ASSERT_TRUE(err == basyx::object::error::None);
        /* API : GET  shells/{aasId}/aas/submodels/{smIdShort}/submodel/submodelElements*/
        auto response = m_provider->getModelPropertyValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements");
        ASSERT_FALSE(response.IsNull());
        /* Seven Properties */
        ASSERT_EQ(7, response.size());
        /* DELETE */
        response = m_provider->getModelPropertyValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/year_month");
        ASSERT_FALSE(response.IsNull());
        ASSERT_EQ(p_year_month.getMap().getProperty("value"), response.getProperty("value"));
        ASSERT_EQ(p_year_month.getMap().getProperty("valueType"), response.getProperty("valueType"));
        ASSERT_EQ(p_year_month.getMap().getProperty("kind"), response.getProperty("kind"));
        ASSERT_EQ(p_year_month.getMap().getProperty("idShort"), response.getProperty("idShort"));
        ASSERT_EQ(p_year_month.getMap().getProperty("modelType"), response.getProperty("modelType"));
        /* API : GET  shells/{aasId}/aas/submodels/{smIdShort}/submodel/values*/
        response = m_provider->getModelPropertyValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/values");
        ASSERT_FALSE(response.IsNull());
        /* Seven Properties */
        ASSERT_EQ(7, response.size());
        /* DELETE */
        err = m_provider->deleteValue("shells/i40.fab/aas/submodels/NexoNutrunner_Asset_1/submodel/submodelElements/year_month");
        ASSERT_TRUE(err == basyx::object::error::None);
        /* Delete the AAS*/
        err = m_provider->deleteValue("shells/i40.fab");
        ASSERT_TRUE(err == basyx::object::error::None);
    }

    /* Build AAS  */
    basyx::object AASAggregatorProviderTest::AAS()
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
    basyx::object AASAggregatorProviderTest::SM1()
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
    basyx::object AASAggregatorProviderTest::SM2()
    {
        using namespace basyx::aas;
        using namespace basyx::xsd_types;

        /* Create Submodel */
        auto sm_2 = util::make_unique<map::Submodel>(SM2_ID_SHORT, simple::Identifier::Custom(SM2_ID));

        sm_2->setAdministrativeInformation(basyx::aas::map::AdministrativeInformation("1", "2"));

        return sm_2->getMap();
    }
}

