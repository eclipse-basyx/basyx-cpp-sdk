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
#include <BaSyx/opcua/aas/node/AssetAdministrationShellNodeManager.h>
#include <tests/regression/opcua/OPCUATestSetup.h>

namespace tests_opcua_agg_node_mgr
{
    using namespace test_opcua_setup;
    using namespace basyx::opcua;

    class AssetAdministrationShellNode_test : public ::testing::Test
    {

    public:
        std::shared_ptr<aas::AssetAdministrationShellNodeManager<Client>> aasNodeMgr;
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        std::unique_ptr<Services<Client>> m_services;
        std::thread m_serverThread;
        LocalizedText desc{ "en-US", "some aas description" };
    public:

        virtual void SetUp()
        {
            m_opcuaSetup = util::make_unique<OPCUATestSetup>();
            m_serverThread = std::thread{ [this]() {m_opcuaSetup->getServer().run(); } };
            m_opcuaSetup->getClient().connect();
            m_services = util::make_unique<Services<Client>>(m_opcuaSetup->getClient());
            aasNodeMgr = std::make_shared<aas::AssetAdministrationShellNodeManager<Client>>(
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

    TEST_F(AssetAdministrationShellNode_test, Create)
    {
        NodeId aasOutNode1, aasOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo", aasOutNode1, desc));
        ASSERT_FALSE(aasOutNode1.isNull());
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo_bar", aasOutNode2, desc));
        ASSERT_FALSE(aasOutNode2.isNull());
    }

    TEST_F(AssetAdministrationShellNode_test, IdShortAndRetreive)
    {;
        NodeId aasOutNode1, aasOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo_", aasOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo_bar_", aasOutNode2, desc));
        std::string smNodeBrowseNameText = m_services->getBrowseNameFromNodeId(aasOutNode1).getText();
        ASSERT_NE(smNodeBrowseNameText, std::string());
        std::string idShort = shared::string::getInstanceName(smNodeBrowseNameText);
        ASSERT_EQ("foo_", idShort);
    }

    TEST_F(AssetAdministrationShellNode_test, RetreiveAll)
    {
        NodeId aasOutNode1, aasOutNode2;
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo__", aasOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo_bar__", aasOutNode2, desc));
        auto nodes = aasNodeMgr->retrieveAll();
        ASSERT_EQ(nodes.size(), 2);
        ASSERT_TRUE(std::get<0>(nodes[0]) == aasOutNode1);
        ASSERT_TRUE(std::get<0>(nodes[1]) == aasOutNode2);
    }

    TEST_F(AssetAdministrationShellNode_test, Description)
    {
        NodeId aasOutNode1, aasOutNode2;
        LocalizedText descAasOut1;
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo___", aasOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo_bar___", aasOutNode2, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->getNodeDescription(aasOutNode1, descAasOut1));
        ASSERT_TRUE(descAasOut1 == desc);
    }

    TEST_F(AssetAdministrationShellNode_test, Remove)
    {
        using namespace basyx::opcua;
        NodeId aasOutNode1, aasOutNode2, idShortNode_1, idShortNode_2;

        auto nsIdx = m_services->getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);
        // Browsepath for IdShort nodes
        BrowsePath path(
            BrowseName(nsIdx, aas::metamodel::IAASIdentifiableType::AttrNames::BrowseText_Identification),
            BrowseName(nsIdx, aas::metamodel::AASIdentifierType::AttrNames::BrowseText_ID)
        );
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo____", aasOutNode1, desc));
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->create("foo_bar____", aasOutNode2, desc));
        // Resolve the idShort nodes
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->translateBrowsePathToNodeIdService(path, aasOutNode1, idShortNode_1));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->translateBrowsePathToNodeIdService(path, aasOutNode2, idShortNode_2));
        // The idShorts values should be written in IdShort Node inorder to perform a remove
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->writeValue<std::string>(idShortNode_1, "foo____"));
        ASSERT_EQ(UA_STATUSCODE_GOOD, m_services->writeValue<std::string>(idShortNode_2, "foo_bar____"));
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->remove("foo____"));
        ASSERT_EQ(UA_STATUSCODE_GOOD, aasNodeMgr->remove("foo_bar____"));
    }
}