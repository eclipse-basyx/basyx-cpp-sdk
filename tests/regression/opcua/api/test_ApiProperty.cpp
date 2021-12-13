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
    using namespace tests_opcua_setup;
    using namespace basyx::aas;

    class ApiProperty_test : public ::testing::Test
    {

    public:
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        const int serverPort = 6006;
    public:
        virtual void SetUp()
        {
            m_opcuaSetup = util::make_unique<OPCUATestSetup>(serverPort);
        }
        virtual void TearDown()
        {
            m_opcuaSetup->getServer().abort();
        }

        std::unique_ptr<map::Property<int32_t>> PROPI32()
        {
            auto prop_int32 = util::make_unique<map::Property<int32_t>>("foo_prop_i32");

            std::string some_catogory("some_category");

            prop_int32->setCategory("some_category");
            prop_int32->setValue(33);

            return std::move(prop_int32);
        }
    };

    TEST_F(ApiProperty_test, api)
    {
        using namespace basyx::opcua::aas;

        auto prop_int32 = PROPI32();

        ApiProperty<Client> api(m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER));
        ASSERT_EQ(UA_STATUSCODE_GOOD, api.createProperty(*prop_int32.get()));
        // Get and Set Value
        int32_t vali32;
        ASSERT_EQ(api.getValue("foo_prop_i32", vali32), UA_STATUSCODE_GOOD);
        ASSERT_EQ(vali32, 33);
        ASSERT_EQ(api.setValue("foo_prop_i32", 3142), UA_STATUSCODE_GOOD);
        ASSERT_EQ(api.getValue("foo_prop_i32", vali32), UA_STATUSCODE_GOOD);
        ASSERT_EQ(vali32, 3142);
        // Get and Set ValueType
        std::string otherAttr;
        ASSERT_EQ(api.getValueType("foo_prop_i32", otherAttr), UA_STATUSCODE_GOOD);
        ASSERT_EQ(otherAttr, "int");
        ASSERT_EQ(api.setValueType("foo_prop_i32", "integer"), UA_STATUSCODE_GOOD);
        ASSERT_EQ(api.getValueType("foo_prop_i32", otherAttr), UA_STATUSCODE_GOOD);
        ASSERT_EQ(otherAttr, "integer");
        // Get and Set Category
        ASSERT_EQ(api.getCategory("foo_prop_i32", otherAttr), UA_STATUSCODE_GOOD);
        ASSERT_EQ(otherAttr, "some_category");
        ASSERT_EQ(api.setCategory("foo_prop_i32", "some category 2"), UA_STATUSCODE_GOOD);
        ASSERT_EQ(api.getCategory("foo_prop_i32", otherAttr), UA_STATUSCODE_GOOD);
        ASSERT_EQ(otherAttr, "some category 2");
    }
}