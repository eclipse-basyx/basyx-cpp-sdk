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

namespace basyx
{
    namespace tests
    {
        namespace opcua_aas_nodes
        {
            using namespace basyx::opcua;
            using namespace basyx::opcua::aas::metamodel;

            class AssetAdministrationShellNode_test : public ::testing::Test
            {

            public:
                std::shared_ptr<aas::AssetAdministrationShellNodeManager<Client>> aasNodeMgr;
                std::unique_ptr<opcua::OPCUATestSetup> m_opcuaSetup;
                const int serverPort = 6000;              
            public:

                virtual void SetUp()
                {
                    m_opcuaSetup = util::make_unique<opcua::OPCUATestSetup>(serverPort);

                    aasNodeMgr = std::make_shared<aas::AssetAdministrationShellNodeManager<Client>>(
                        m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER)
                    );

                }
                virtual void TearDown()
                {
                    m_opcuaSetup->getServer().abort();
                }
            };

            TEST_F(AssetAdministrationShellNode_test, nodes)
            {
                LocalizedText desc("en-US","some aas description");
                // create test
                Services<Client> services(m_opcuaSetup->getClient());

                NodeId aasOutNode1, aasOutNode2, identifierNode;
                UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                auto nsIdx = services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

                status = aasNodeMgr->create("foo", aasOutNode1, desc);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_FALSE(aasOutNode1.isNull());
                status = aasNodeMgr->create("foo_bar", aasOutNode2, desc);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_FALSE(aasOutNode2.isNull());
                // idshort test
                std::string smNodeBrowseNameText = services.getBrowseNameFromNodeId(aasOutNode1).getText();
                ASSERT_NE(smNodeBrowseNameText, std::string());
                std::string idShort = shared::string::getInstanceName(smNodeBrowseNameText);
                ASSERT_EQ("foo", idShort);
                // retieve test
                status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                BrowsePath identifierPath(
                    BrowseName(nsIdx, IAASIdentifiableType::AttrNames::BrowseText_Identification),
                    BrowseName(nsIdx, AASIdentifierType::AttrNames::BrowseText_ID)
                );
                status = services.translateBrowsePathToNodeIdService(identifierPath, aasOutNode1, identifierNode);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);;
                status = services.writeValue(identifierNode, std::string("foo_id"));
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);;
                status = aasNodeMgr->retrieve("foo_id", aasOutNode1);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_FALSE(aasOutNode1.isNull());
                // Description test
                LocalizedText descAasOut1;
                status = services.getNodeDescription(aasOutNode1, descAasOut1);
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_TRUE(descAasOut1 == desc);
                // retrieve all test
                std::vector<std::tuple<NodeId, std::string>> nodes = aasNodeMgr->retrieveAll();
                ASSERT_EQ(nodes.size(), 2);
                ASSERT_TRUE(std::get<0>(nodes[0]) == aasOutNode1);
                ASSERT_TRUE(std::get<0>(nodes[1]) == aasOutNode2);
                // remove test
                status = UA_STATUSCODE_BADUNKNOWNRESPONSE;
                status = aasNodeMgr->remove("foo_id");
                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
            }
        }
    }
}