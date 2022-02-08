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

namespace tests_opcua_client_services
{
    using namespace basyx::opcua;

    class OPCUAClientServicesTest : public ::testing::Test
    {
    protected:
        const char* endpoint = "opc.tcp://localhost:4842";
        std::unique_ptr<basyx::opcua::Server> m_server;
        std::unique_ptr<basyx::opcua::Client> m_client;
        std::thread m_serverThread;
    public:
        virtual void SetUp()
        {
            m_server = util::make_unique<basyx::opcua::Server>(4842, shared::Namespaces::BASYX_NS_URI);
            m_server->initialize();
            m_serverThread = std::thread{ [this]() {m_server->run();}};
            m_client = util::make_unique<Client>(endpoint, shared::Namespaces::BASYX_NS_URI);
            m_client->connect();
        }

        virtual void TearDown()
        {
            m_client->disconnect();
            m_server->abort();
            m_serverThread.join();
        }
    };

    TEST_F(OPCUAClientServicesTest, testChildReferences)
    {
        Services<Client> services(*m_client.get());

        auto children = services.getChildReferences(
            NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 85),
            NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, UA_NS0ID_ORGANIZES)
        );
        ASSERT_EQ(children.size(), 1);

        auto iter = std::find_if(children.begin(), children.end(), [](const NodeId& node) {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 23470) == node);
            });

        children.clear();
        children = services.getAllChildReferences(NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 85));
        ASSERT_EQ(children.size(), 2);

        iter = std::find_if(children.begin(), children.end(), [](const NodeId& node) {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 61) == node);
            });
        ASSERT_TRUE(iter != children.end());

        iter = std::find_if(children.begin(), children.end(), [](const NodeId& node) {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 23470) == node);
            });

        iter = std::find_if(children.begin(), children.end(), [](const NodeId& node) {
            return (NodeId(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, 2253) == node);
            });
        ASSERT_TRUE(iter != children.end());
    }

    TEST_F(OPCUAClientServicesTest, testNodeDescription)
    {
        using namespace basyx::opcua;

        Services<Client> services(*m_client.get());

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

    }
}