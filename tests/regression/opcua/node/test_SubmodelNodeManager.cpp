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

namespace basyx
{
    namespace tests
    {
        namespace opcua_sm_nodes
        {
            using namespace basyx::opcua;
            using namespace aas::metamodel;

            class SubmodelNodeManager_test : public ::testing::Test
            {
            public:
                std::unique_ptr<aas::SubmodelNodeManager<Client>> smNodeMgr;
                std::unique_ptr<opcua::OPCUATestSetup> m_opcuaSetup;
                const int serverPort = 6001;
            public:
                virtual void SetUp()
                {
                    m_opcuaSetup = util::make_unique<opcua::OPCUATestSetup>(serverPort);

                    smNodeMgr = util::make_unique<aas::SubmodelNodeManager<Client>>(
                        m_opcuaSetup->getClient(),
                        NodeId::numeric(UA_NS0ID_OBJECTSFOLDER)
                    );
                }

                virtual void TearDown()
                {
                    m_opcuaSetup->getServer().abort();
                }
            };

            TEST_F(SubmodelNodeManager_test, nodes)
            {
                // create test
                LocalizedText desc("en-US","some sm description");

                Services<Client> services(m_opcuaSetup->getClient());
                NodeId smOutNode1, smOutNode2, identifierNode;
                UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                auto nsIdx = services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);
                status = smNodeMgr->create("foo", smOutNode1, desc);

                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_FALSE(smOutNode1.isNull());
                status = smNodeMgr->create("foo_bar", smOutNode2, desc);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_FALSE(smOutNode2.isNull());
                // Description test
                LocalizedText descSmOut1;
                status = services.getNodeDescription(smOutNode1, descSmOut1);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_TRUE(descSmOut1 == desc);
                // idshort test
                std::string smNodeBrowseNameText = services.getBrowseNameFromNodeId(smOutNode1).getText();
                ASSERT_NE(smNodeBrowseNameText, std::string());
                std::string idShort = shared::string::getInstanceName(smNodeBrowseNameText);
                ASSERT_EQ("foo", idShort);
                // retrieve all test
                std::vector<std::tuple<NodeId, std::string>> nodes = smNodeMgr->retrieveAll();
                ASSERT_EQ(nodes.size(), 2);
                ASSERT_TRUE(std::get<0>(nodes[0]) == smOutNode1);
                ASSERT_TRUE(std::get<0>(nodes[1]) == smOutNode2);
                // remove test
                status = UA_STATUSCODE_BADUNKNOWNRESPONSE;
                status = smNodeMgr->remove("foo");
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);

            }
        }
    }
}