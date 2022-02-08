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
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/opcua/aas/node/SubmodelNodeManager.h>
#include <tests/regression/opcua/OPCUATestSetup.h>

namespace tests_opcua_sm_node_mgr
{
    using namespace basyx::opcua;
    using namespace test_opcua_setup;

    class SubmodelNodeManager_test : public ::testing::Test
    {
    public:
        std::unique_ptr<aas::SubmodelNodeManager<Client>> smNodeMgr;
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        std::unique_ptr<Services<Client>> m_services;
        std::thread m_serverThread;
        LocalizedText desc { "en-US", "some sm description" };
    public:

        virtual void SetUp()
        {
            m_opcuaSetup = util::make_unique<OPCUATestSetup>();
            m_serverThread = std::thread{ [this]() {m_opcuaSetup->getServer().run(); } };
            m_opcuaSetup->getClient().connect();
            m_services = util::make_unique<Services<Client>>(m_opcuaSetup->getClient());
            smNodeMgr = util::make_unique<aas::SubmodelNodeManager<Client>>(
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

    TEST_F(SubmodelNodeManager_test, Create)
    {
        NodeId smOutNode1, smOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo", smOutNode1, desc));
        ASSERT_FALSE(smOutNode1.isNull());
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo_bar", smOutNode2, desc));
        ASSERT_FALSE(smOutNode2.isNull());
    }

    TEST_F(SubmodelNodeManager_test, IdShortAndRetreive)
    {
        NodeId smOutNode1;
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo__", smOutNode1, desc));
        std::string smNodeBrowseNameText = m_services->getBrowseNameFromNodeId(smOutNode1).getText();
        ASSERT_NE(smNodeBrowseNameText, std::string());
        std::string idShort = shared::string::getInstanceName(smNodeBrowseNameText);
        ASSERT_EQ("foo__", idShort);
    }

    TEST_F(SubmodelNodeManager_test, RetreiveAll)
    {
        NodeId smOutNode1, smOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo__", smOutNode1, desc));
        ASSERT_FALSE(smOutNode1.isNull());
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo_bar__", smOutNode2, desc));
        ASSERT_FALSE(smOutNode2.isNull());
        std::vector<std::tuple<NodeId, std::string>> nodes = smNodeMgr->retrieveAll();
        ASSERT_EQ(nodes.size(), 2);
        ASSERT_TRUE(std::get<0>(nodes[0]) == smOutNode1);
        ASSERT_TRUE(std::get<0>(nodes[1]) == smOutNode2);
    }

    TEST_F(SubmodelNodeManager_test, Description)
    {
        LocalizedText descSmOut1;
        NodeId smOutNode1, smOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo_", smOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->getNodeDescription(smOutNode1, descSmOut1));
        ASSERT_TRUE(descSmOut1 == desc);
    }

    TEST_F(SubmodelNodeManager_test, Remove)
    {
        NodeId smOutNode1, idShortNode;
        auto nsIdx = m_services->getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);
        // Browsepath for IdShort node
        BrowsePath path(
            BrowseName(nsIdx, aas::metamodel::IAASIdentifiableType::AttrNames::BrowseText_Identification),
            BrowseName(nsIdx, aas::metamodel::AASIdentifierType::AttrNames::BrowseText_ID)
        );
        ASSERT_EQ(UA_STATUSCODE_GOOD, smNodeMgr->create("foo___", smOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->translateBrowsePathToNodeIdService(path, smOutNode1, idShortNode));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->writeValue<std::string>(idShortNode, "foo___"));
        ASSERT_EQ( UA_STATUSCODE_GOOD, smNodeMgr->remove("foo___"));
    }
}