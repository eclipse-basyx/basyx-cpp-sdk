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
#include <BaSyx/opcua/provider/OPCUAModelProvider.h>


namespace tests_opcua_model_provider_meta
{
    using namespace basyx::opcua;
    using namespace basyx::opcua::provider;

    basyx::object objectWithoutTypeMetadata();
    basyx::object objectWithTypeMetadata();

    class OPCUAModelProviderTypeMetaTest : public ::testing::Test
    {
        std::unique_ptr<basyx::opcua::Server> m_server;
    public:

        virtual void SetUp()
        {
            m_server = util::make_unique<basyx::opcua::Server>(4843, shared::Namespaces::BASYX_NS_URI);

            m_server->initialize();

            m_server->runInBackground();

            /* Wait until the server is Up*/
            while (!m_server->isServerUp());

        }

        virtual void TearDown()
        {
            m_server->abort();
        }
    };

    TEST_F(OPCUAModelProviderTypeMetaTest, ModelProviderTypeMeta)
    {
        /* Create the Model Provider */
        OPCUAModelProvider<Client> provider(
            "opc.tcp://localhost:4843",
            shared::Namespaces::BASYX_NS_URI,
            NodeId::numeric(UA_NS0ID_OBJECTSFOLDER),
            true					/* Enables Embedded Type information */
        );

        /* Create the VAB object in OPC-UA Server */
        auto status = provider.createValue("testObj", objectWithTypeMetadata());

        /* Get the elements with specified paths */
        auto s8_get = provider.getModelPropertyValue("testObj/s8");
        auto s16_get = provider.getModelPropertyValue("testObj/s16");
        auto s32_get = provider.getModelPropertyValue("testObj/s32");
        auto s64_get = provider.getModelPropertyValue("testObj/s64");

        auto u8_get = provider.getModelPropertyValue("testObj/u8");
        auto u16_get = provider.getModelPropertyValue("testObj/u16");
        auto u32_get = provider.getModelPropertyValue("testObj/u32");
        auto u64_get = provider.getModelPropertyValue("testObj/u64");

        auto flt_get = provider.getModelPropertyValue("testObj/flt");
        auto dbl_get = provider.getModelPropertyValue("testObj/dbl");

        auto str_get = provider.getModelPropertyValue("testObj/str");

        ASSERT_EQ(s8_get, TypesTransformer::objectWithMeta<int8_t>(-125));
        ASSERT_EQ(s16_get, TypesTransformer::objectWithMeta<int16_t>(-32000));
        ASSERT_EQ(s32_get, TypesTransformer::objectWithMeta<int32_t>(-2147483640));
        ASSERT_EQ(s64_get, TypesTransformer::objectWithMeta<int64_t>(-9223372036854775808ULL));
        ASSERT_EQ(u8_get, TypesTransformer::objectWithMeta<uint8_t>(245));
        ASSERT_EQ(u16_get, TypesTransformer::objectWithMeta<uint16_t>(65530));
        ASSERT_EQ(u32_get, TypesTransformer::objectWithMeta<uint32_t>(4294967290));
        ASSERT_EQ(u64_get, TypesTransformer::objectWithMeta<uint64_t>(18446744073709551615U));
        ASSERT_EQ(flt_get, TypesTransformer::objectWithMeta<float>(-3.141592));
        ASSERT_EQ(dbl_get, TypesTransformer::objectWithMeta<double>(3.141592653589793));
        ASSERT_EQ(str_get, TypesTransformer::objectWithMeta<std::string>("!!opc-ua!!"));
    }

    /* Test object */
    basyx::object objectWithTypeMetadata()
    {
        auto map = basyx::object::make_map();

        auto s8 = TypesTransformer::objectWithMeta<int8_t>(-125);
        auto s16 = TypesTransformer::objectWithMeta<int16_t>(-32000);
        auto s32 = TypesTransformer::objectWithMeta<int32_t>(-2147483640);
        auto s64 = TypesTransformer::objectWithMeta<int64_t>(-9223372036854775808ULL);

        auto u8 = TypesTransformer::objectWithMeta<uint8_t>(245);
        auto u16 = TypesTransformer::objectWithMeta<uint16_t>(65530);
        auto u32 = TypesTransformer::objectWithMeta<uint32_t>(4294967290);
        auto u64 = TypesTransformer::objectWithMeta<uint64_t>(18446744073709551615U);

        auto flt = TypesTransformer::objectWithMeta<float>(-3.141592);
        auto dbl = TypesTransformer::objectWithMeta<double>(3.141592653589793);

        auto str = TypesTransformer::objectWithMeta<std::string>("!!opc-ua!!");


        map.insertKey("s8", std::move(s8));
        map.insertKey("s16", std::move(s16));
        map.insertKey("s32", std::move(s32));
        map.insertKey("s64", std::move(s64));

        map.insertKey("u8", std::move(u8));
        map.insertKey("u16", std::move(u16));
        map.insertKey("u32", std::move(u32));
        map.insertKey("u64", std::move(u64));

        map.insertKey("flt", std::move(flt));
        map.insertKey("dbl", std::move(dbl));

        map.insertKey("str", std::move(str));

        return map;
    }

    /* Test object */
    basyx::object objectWithoutTypeMetadata()
    {

        basyx::object objectList = basyx::object::make_list<basyx::object>({ "A string",33.444,true, 99 });

        basyx::object primliminaryList = basyx::object::make_list <double>({ 3.142, 2.72 });

        basyx::object map = basyx::object::make_map();

        map.insertKey("intValue", basyx::object(20));
        map.insertKey("doubleValue", basyx::object(20.4));
        map.insertKey("stringValue", basyx::object("Some string"));
        map.insertKey("objectList", basyx::object(objectList));
        map.insertKey("primList", basyx::object(primliminaryList));

        return map;
    }
}