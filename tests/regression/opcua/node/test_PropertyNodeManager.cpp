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
    using namespace tests_opcua_setup;

    class PropertyNodeManager_test : public ::testing::Test
    {

    public:
        std::shared_ptr<aas::PropertyNodeManager<Client>> propNodeMgr;
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        const int serverPort = 6002;
    public:

        virtual void SetUp()
        {
            m_opcuaSetup = util::make_unique<OPCUATestSetup>(serverPort);

            propNodeMgr = std::make_shared<aas::PropertyNodeManager<Client>>(
                m_opcuaSetup->getClient(),
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER)
                );
        }

        virtual void TearDown()
        {
            m_opcuaSetup->getServer().abort();
        }

    };

    TEST_F(PropertyNodeManager_test, nodes)
    {
        // create test
        LocalizedText desc("en-US", "some prop description");
        Services<Client> services(m_opcuaSetup->getClient());

        NodeId propOutNode1, propOutNode2, identifierNode;
        UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

        auto nsIdx = services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

        status = propNodeMgr->create("foo", propOutNode1, desc);
        ASSERT_EQ(status, UA_STATUSCODE_GOOD);
        ASSERT_FALSE(propOutNode1.isNull());
        status = propNodeMgr->create("foo_bar", propOutNode2, desc);
        ASSERT_EQ(status, UA_STATUSCODE_GOOD);
        ASSERT_FALSE(propOutNode1.isNull());
        // Description test
        LocalizedText descPropOut1;
        status = services.getNodeDescription(propOutNode1, descPropOut1);
        ASSERT_EQ(status, UA_STATUSCODE_GOOD);
        ASSERT_TRUE(descPropOut1 == desc);
        // idshort test
        std::string smNodeBrowseNameText = services.getBrowseNameFromNodeId(propOutNode1).getText();
        ASSERT_NE(smNodeBrowseNameText, std::string());
        std::string idShort = shared::string::getInstanceName(smNodeBrowseNameText);
        ASSERT_EQ("foo", idShort);
        // retrieve all test
        std::vector<std::tuple<NodeId, std::string>> nodes = propNodeMgr->retrieveAll();
        ASSERT_EQ(nodes.size(), 2);
        ASSERT_TRUE(std::get<0>(nodes[0]) == propOutNode1);
        ASSERT_TRUE(std::get<0>(nodes[1]) == propOutNode2);
        // remove test
        status = UA_STATUSCODE_BADUNKNOWNRESPONSE;
        status = propNodeMgr->remove("foo");
        ASSERT_EQ(status, UA_STATUSCODE_GOOD);
    }
}