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
#include <BaSyx/opcua/aas/api_v2/ApiProperty.h>
#include <tests/regression/opcua/OPCUATestSetup.h>

namespace tests_opcua_api_property
{
    using namespace basyx::opcua;
    using namespace basyx::aas;
    using namespace test_opcua_setup;

    class ApiProperty_test : public ::testing::Test
    {
    protected:
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        std::thread m_serverThread;
        std::unique_ptr<map::Property<int32_t>> prop_int32 = PROPI32();
        std::unique_ptr<basyx::opcua::aas::ApiProperty<Client>> api;
    public:
        virtual void SetUp()
        {
            using namespace basyx::opcua;
            m_opcuaSetup = util::make_unique<OPCUATestSetup>();
            m_serverThread = std::thread{ [this]() {m_opcuaSetup->getServer().run(); } };
            auto nsIdx = m_opcuaSetup->getServer().getNamespaceIndex(shared::Namespaces::BASYX_NS_URI);
            aas::metamodel::AASMetamodel::define(nsIdx, m_opcuaSetup->getServer());
            m_opcuaSetup->getClient().connect();

            api = util::make_unique<aas::ApiProperty<Client>>(m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER));
        }

        virtual void TearDown()
        {
            m_opcuaSetup->getClient().disconnect();
            m_opcuaSetup->getServer().abort();
            m_serverThread.join();
        }

        std::unique_ptr<map::Property<int32_t>> PROPI32();
    };

    TEST_F(ApiProperty_test, apiGetSetValue)
    {
        int32_t vali32;
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createProperty(*prop_int32.get()));
        ASSERT_EQ(api->getValue("foo_prop_i32", vali32), UA_STATUSCODE_GOOD);
        ASSERT_EQ(vali32, 33);
        ASSERT_EQ(api->setValue("foo_prop_i32", 3142), UA_STATUSCODE_GOOD);
        ASSERT_EQ(api->getValue("foo_prop_i32", vali32), UA_STATUSCODE_GOOD);
        ASSERT_EQ(vali32, 3142);
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteProperty("foo_prop_i32"));
    }

    TEST_F(ApiProperty_test, apiGetSetValueType)
    {
        std::string otherAttr;
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createProperty(*prop_int32.get()));
        ASSERT_EQ(api->getValueType("foo_prop_i32", otherAttr), UA_STATUSCODE_GOOD);
        ASSERT_EQ(otherAttr, "int");
        ASSERT_EQ(api->setValueType("foo_prop_i32", "integer"), UA_STATUSCODE_GOOD);
        ASSERT_EQ(api->getValueType("foo_prop_i32", otherAttr), UA_STATUSCODE_GOOD);
        ASSERT_EQ(otherAttr, "integer");
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteProperty("foo_prop_i32"));
    }

    TEST_F(ApiProperty_test, apiGetSetCategory)
    {
        std::string category;
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createProperty(*prop_int32.get()));
        ASSERT_EQ(api->getCategory("foo_prop_i32", category), UA_STATUSCODE_GOOD);
        ASSERT_EQ(category, "some_category");
        ASSERT_EQ(api->setCategory("foo_prop_i32", "some category 2"), UA_STATUSCODE_GOOD);
        ASSERT_EQ(api->getCategory("foo_prop_i32", category), UA_STATUSCODE_GOOD);
        ASSERT_EQ(category, "some category 2");
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteProperty("foo_prop_i32"));
    }

    std::unique_ptr<map::Property<int32_t>> ApiProperty_test::PROPI32()
    {
        auto prop_int32 = util::make_unique<map::Property<int32_t>>("foo_prop_i32");

        std::string some_catogory("some_category");
        prop_int32->setCategory("some_category");
        prop_int32->setValue(33);

        return std::move(prop_int32);
    }
}