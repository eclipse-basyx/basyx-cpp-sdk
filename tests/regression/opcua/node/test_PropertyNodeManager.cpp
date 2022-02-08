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
#include <BaSyx/opcua/aas/node/PropertyNodeManager.h>
#include <tests/regression/opcua/OPCUATestSetup.h>

namespace tests_opcua_property_node_mgr
{
    using namespace basyx::opcua;
    using namespace test_opcua_setup;

    class PropertyNodeManager_test : public ::testing::Test
    {

    public:
        std::shared_ptr<aas::PropertyNodeManager<Client>> propNodeMgr;
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        std::thread m_serverThread;
        std::unique_ptr<Services<Client>> m_services;
        LocalizedText desc{ "en-US", "some prop description" };
    public:

        virtual void SetUp()
        {
            m_opcuaSetup = util::make_unique<OPCUATestSetup>();
            m_serverThread = std::thread{ [this]() {m_opcuaSetup->getServer().run(); } };
            m_opcuaSetup->getClient().connect();
            m_services = util::make_unique< Services<Client>>(m_opcuaSetup->getClient());
            propNodeMgr = std::make_shared<aas::PropertyNodeManager<Client>>(
                m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER)
             );
        }

        virtual void TearDown()
        {
            m_opcuaSetup->getClient().disconnect();
            m_opcuaSetup->getServer().abort();
            m_serverThread.join();
        }

    };

    TEST_F(PropertyNodeManager_test, Create)
    {
        NodeId propOutNode1, propOutNode2, identifierNode;
        auto nsIdx = m_services->getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo", propOutNode1, desc));
        ASSERT_FALSE(propOutNode1.isNull());
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo_bar", propOutNode2, desc));
        ASSERT_FALSE(propOutNode1.isNull());
    }

    TEST_F(PropertyNodeManager_test, IdShortAndRetreive)
    {
        NodeId propOutNode1, propOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo_", propOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo_bar_", propOutNode2, desc));
        std::string smNodeBrowseNameText = m_services->getBrowseNameFromNodeId(propOutNode1).getText();
        ASSERT_NE(smNodeBrowseNameText, std::string());
        std::string idShort = shared::string::getInstanceName(smNodeBrowseNameText);
        ASSERT_EQ("foo_", idShort);
    }

    TEST_F(PropertyNodeManager_test, RetreiveAll)
    {
        NodeId propOutNode1, propOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo___", propOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo_bar___", propOutNode2, desc));
        std::vector<std::tuple<NodeId, std::string>> nodes = propNodeMgr->retrieveAll();
        ASSERT_EQ(nodes.size(), 2);
        ASSERT_TRUE(std::get<0>(nodes[0]) == propOutNode1);
        ASSERT_TRUE(std::get<0>(nodes[1]) == propOutNode2);
    }

    TEST_F(PropertyNodeManager_test, Description)
    {
        LocalizedText descPropOut1;
        NodeId propOutNode1;
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo__", propOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->getNodeDescription(propOutNode1, descPropOut1));
        ASSERT_TRUE(descPropOut1 == desc);
    }

    TEST_F(PropertyNodeManager_test, Remove)
    {
        NodeId propOutNode1;
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->create("foo____", propOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, propNodeMgr->remove("foo____"));
    }
}