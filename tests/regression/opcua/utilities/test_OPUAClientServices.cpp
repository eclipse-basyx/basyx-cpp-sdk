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
#include <BaSyx/opcua/common/NodeCommon.h>

namespace basyx
{
    namespace tests
    {
        namespace opcua
        {
            class OPCUAClientServicesTest : public ::testing::Test
            {
                std::unique_ptr<basyx::opcua::Server> m_server;
            public:
                virtual void SetUp()
                {
                    using namespace basyx::opcua;

                    m_server = util::make_unique<basyx::opcua::Server>(7000, shared::Namespaces::BASYX_NS_URI);

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

            void testChildReferences()
            {
                using namespace basyx::opcua;

                Client client("opc.tcp://localhost:7000", shared::Namespaces::BASYX_NS_URI);

                client.connect();

                Services<Client> services(client);

                auto children = services.getChildReferences(
                    NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 85),
                    NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, UA_NS0ID_ORGANIZES)
                );

                ASSERT_EQ(children.size(), 2);


                auto iter = std::find_if(children.begin(), children.end(), [](const NodeId& node){
                    return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 23470) == node);
                });

                ASSERT_TRUE(iter != children.end());

                iter = std::find_if(children.begin(), children.end(), [](const NodeId& node){
                    return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 23470) == node);
                });

                ASSERT_TRUE(iter != children.end());

                children.clear();

                children = services.getAllChildReferences(NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 85));

                ASSERT_EQ(children.size(), 3);
                
                iter = std::find_if(children.begin(), children.end(), [](const NodeId& node){
                    return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 61) == node);
                });

                ASSERT_TRUE(iter != children.end());

                iter = std::find_if(children.begin(), children.end(), [](const NodeId& node){
                    return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 23470) == node);
                });

                ASSERT_TRUE(iter != children.end());
                
                iter = std::find_if(children.begin(), children.end(), [](const NodeId& node){
                    return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 2253) == node);
                });

                ASSERT_TRUE(iter != children.end());

                client.disconnect();
            }

            void testNodeDescription()
            {
                using namespace basyx::opcua;

                Client client("opc.tcp://localhost:7000", shared::Namespaces::BASYX_NS_URI);

                client.connect();

                Services<Client> services(client);

                UA_StatusCode status = services.addObjectNode(
                    NodeId::string("foo"),
                    NodeId::numeric(85),
                    NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
                    NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                    QualifiedName(0, "foo"),
                    ObjectAttributes("foo", "foo description", "en-US")
                );

                ASSERT_EQ(status, UA_STATUSCODE_GOOD);

                LocalizedText description;

                status = services.getNodeDescription(NodeId::string("foo"), description);

                ASSERT_EQ(status, UA_STATUSCODE_GOOD);
                ASSERT_EQ(description.getLocale(), "en-US");
                ASSERT_EQ(description.getText(), "foo description");

                client.disconnect();
            }

            TEST_F(OPCUAClientServicesTest, clientServices)
            {
                testChildReferences();
                testNodeDescription();
            }
        }
    }
}
