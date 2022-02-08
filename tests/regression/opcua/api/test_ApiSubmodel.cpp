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
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/opcua/aas/api_v2/ApiSubmodel.h>
#include <tests/regression/opcua/OPCUATestSetup.h>

namespace tests_opcua_api_submodel
{
    using namespace basyx::opcua;
    using namespace basyx::aas;
    using namespace test_opcua_setup;

    class ApiSubmodel_test : public ::testing::Test
    {
    protected:
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        std::unique_ptr<map::Submodel> sm = SM();
        std::unique_ptr<basyx::opcua::aas::ApiSubmodel<Client>> api;
        std::thread m_serverThread;
    public:
        virtual void SetUp()
        {
            using namespace basyx::opcua;
            m_opcuaSetup = util::make_unique<OPCUATestSetup>();
            m_serverThread = std::thread{ [this]() {m_opcuaSetup->getServer().run(); } };
            auto nsIdx = m_opcuaSetup->getServer().getNamespaceIndex(shared::Namespaces::BASYX_NS_URI);
            aas::metamodel::AASMetamodel::define(nsIdx, m_opcuaSetup->getServer());
            m_opcuaSetup->getClient().connect();

            api = util::make_unique<aas::ApiSubmodel<Client>>(m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER));
        }

        virtual void TearDown()
        {
            m_opcuaSetup->getClient().disconnect();
            m_opcuaSetup->getServer().abort();
            m_serverThread.join();
        }

        std::unique_ptr<map::Submodel> SM();
    };

    TEST_F(ApiSubmodel_test, SubmodelAttributes)
    {
        using namespace basyx::opcua::aas;

        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createSubmodel(*sm.get()));
        auto smNew = api->getSubmodel("foo_sm");
        ASSERT_NE(smNew, nullptr);
        ASSERT_NE(smNew->getAdministrativeInformation().getRevision(), nullptr);
        ASSERT_EQ(*smNew->getAdministrativeInformation().getRevision(), "2");
        ASSERT_NE(smNew->getAdministrativeInformation().getVersion(), nullptr);
        ASSERT_EQ(*smNew->getAdministrativeInformation().getVersion(), "1");
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteSubmodel("foo_sm"));
    }

    TEST_F(ApiSubmodel_test, SubmodelAttributesPropertyInt)
    {
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createSubmodel(*sm.get()));
        auto prop = api->getAllProperties("foo_sm");
        auto prop_1 = (prop[0]->getIdShort() == "prop_i32") ? std::move(prop[0]) : std::move(prop[1]);
        ASSERT_EQ("prop_i32", prop_1->getIdShort());
        ASSERT_EQ("int", prop_1->getValueType());
        ASSERT_EQ(23, dynamic_cast<map::Property<int>*>(prop_1.get())->getValue());
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteSubmodel("foo_sm"));
    }

    TEST_F(ApiSubmodel_test, SubmodelAttributesPropertyString)
    {
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createSubmodel(*sm.get()));
        auto prop = api->getAllProperties("foo_sm");
        auto prop_2 = (prop[1]->getIdShort() == "prop_str") ? std::move(prop[1]) : std::move(prop[0]);
        ASSERT_EQ("prop_str", prop_2->getIdShort());
        ASSERT_EQ("string", prop_2->getValueType());
        ASSERT_EQ("string property", dynamic_cast<map::Property<std::string>*>(prop_2.get())->getValue());
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteSubmodel("foo_sm"));
    }

    TEST_F(ApiSubmodel_test, SubmodelDelete)
    {
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createSubmodel(*sm.get()));
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteSubmodel("foo_sm"));
    }

    /* Build a Submodel  */
    std::unique_ptr<map::Submodel> ApiSubmodel_test::SM()
    {
        auto sm = util::make_unique<map::Submodel>("foo_sm", simple::Identifier::Custom("foo_sm_ident"));
        /* Set Administration attributes */
        sm->setAdministrativeInformation(basyx::aas::map::AdministrativeInformation("1", "2"));

        // Add some properties
        auto prop_i32 = util::make_unique<map::Property<int>>("prop_i32");
        prop_i32->setValue(23);
        prop_i32->setCategory("VARAIBLE");

        auto prop_str = util::make_unique<map::Property<std::string>>("prop_str");
        prop_str->setValue("string property");
        prop_str->setCategory("CONSTANT");

        sm->submodelElements().addElement(std::move(prop_i32));
        sm->submodelElements().addElement(std::move(prop_str));

        return std::move(sm);
    }
}