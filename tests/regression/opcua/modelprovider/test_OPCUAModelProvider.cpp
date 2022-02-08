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

namespace tests_opcua_model_provider
{
    using namespace basyx::opcua;
    using namespace basyx::aas;

    basyx::object createTestObject();

    class OPCUAModelProviderTest : public ::testing::Test
    {
    protected:
        const char* endpoint = "opc.tcp://localhost:4842";
        std::unique_ptr<basyx::opcua::Server> m_server;
        std::unique_ptr<basyx::opcua::provider::OPCUAModelProvider<>> provider;
        std::thread m_serverThread;
    public:
        virtual void SetUp()
        {
            m_server = util::make_unique<basyx::opcua::Server>(4842, shared::Namespaces::BASYX_NS_URI);
            m_server->initialize();
            m_serverThread = std::thread{ [this]() {m_server->run(); } };

            provider = util::make_unique<basyx::opcua::provider::OPCUAModelProvider<>>(
                endpoint,
                shared::Namespaces::BASYX_NS_URI,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER),
                false/* Enables Embedded Type information */
            );
        }

        virtual void TearDown()
        {
            m_server->abort();
            m_serverThread.join();
        }
    };

    TEST_F(OPCUAModelProviderTest, ModelProviderAccessElements)
    {
        ASSERT_EQ(basyx::object::error::None, provider->createValue("testObj", createTestObject()));
        /* Access the elements */
        ASSERT_DOUBLE_EQ((provider->getModelPropertyValue("testObj/doubleValue").Get<double>()), 20.4);
        ASSERT_EQ(provider->getModelPropertyValue("testObj/intValue").Get<int32_t>(), 20);
        ASSERT_EQ(provider->getModelPropertyValue("testObj/stringValue").Get<std::string&>(), "Some string");
        ASSERT_EQ(basyx::object::error::None, provider->deleteValue("testObj"));
    }

    TEST_F(OPCUAModelProviderTest, ModelProviderAccessPreliminaryList)
    {
        ASSERT_EQ(basyx::object::error::None, provider->createValue("testObj", createTestObject()));
        /* Prliminary list with of double type */
        auto object = provider->getModelPropertyValue("testObj/primList");
        ASSERT_EQ(basyx::object::error::None, object.getError());
        auto priliminaryList = object.Get<basyx::object::list_t<double>>();
        /* Check the order preservation */
        ASSERT_DOUBLE_EQ(priliminaryList[0], 3.142);
        ASSERT_DOUBLE_EQ(priliminaryList[1], 2.72);
        ASSERT_EQ(basyx::object::error::None, provider->deleteValue("testObj"));
    }

    TEST_F(OPCUAModelProviderTest, ModelProviderAccessObjectList)
    {
        ASSERT_EQ(basyx::object::error::None, provider->createValue("testObj", createTestObject()));
        auto object = provider->getModelPropertyValue("testObj/objectList");
        /* Check the order preservation of object list */
        ASSERT_EQ(basyx::object::error::None, object.getError());
        auto objectList = object.Get<basyx::object::object_list_t>();
        ASSERT_EQ(basyx::object::object_cast<std::string>(objectList[0]), "A string");
        ASSERT_DOUBLE_EQ(basyx::object::object_cast<double>(objectList[1]), 33.444);
        ASSERT_EQ(basyx::object::object_cast<bool>(objectList[2]), true);
        ASSERT_EQ(basyx::object::object_cast<int32_t>(objectList[3]), 99);
        ASSERT_EQ(basyx::object::error::None, provider->deleteValue("testObj"));
    }

    TEST_F(OPCUAModelProviderTest, ModelProviderSet)
    {
        ASSERT_EQ(basyx::object::error::None, provider->createValue("testObj", createTestObject()));
        /* Set the value */
        auto setStatus = provider->setModelPropertyValue("testObj/doubleValue", 99.39472198486328125);
        ASSERT_EQ(setStatus, basyx::object::error::None);
        ASSERT_DOUBLE_EQ(provider->getModelPropertyValue("testObj/doubleValue").Get<double>(), 99.39472198486328125);
        ASSERT_EQ(basyx::object::error::None, provider->deleteValue("testObj"));
    }


    TEST_F(OPCUAModelProviderTest, ModelProviderDelete)
    {
        ASSERT_EQ(basyx::object::error::None, provider->createValue("testObj", createTestObject()));
        /* Delete the element */
        auto deleteStatus = provider->deleteValue("testObj/stringValue");
        ASSERT_EQ(deleteStatus, basyx::object::error::None);
        /* Get the element again*/
        auto getStatus = provider->getModelPropertyValue("testObj/stringValue");
        //ASSERT_EQ(basyx::object::make_null(), getStatus);
        ASSERT_EQ(basyx::object::error::None, provider->deleteValue("testObj"));
    }

    /* Test object */
    basyx::object createTestObject()
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