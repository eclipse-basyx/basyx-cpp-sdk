/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_TEST_SET_UP_H
#define OPCUA_TEST_SET_UP_H

#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>

namespace test_opcua_setup
{
    class OPCUATestSetup
    {
        const char* endpoint = "opc.tcp://localhost:4842";
        using Server_t = basyx::opcua::Server;
        using Client_t = basyx::opcua::Client;
    private:
        std::unique_ptr<basyx::opcua::Server> m_server;
        std::unique_ptr<basyx::opcua::Client> m_client;
        // Namespace where the AAS metamodel will be defined
        const char* nsUri = basyx::opcua::shared::Namespaces::BASYX_NS_URI;

    public:

        OPCUATestSetup()
        {
            using namespace basyx::opcua;
            m_server = util::make_unique<Server_t>(4842, nsUri);
            m_server->initialize();
            auto nsIdx = m_server->getNamespaceIndex(nsUri);
            // Create the AAS Metamdodel in the server
            aas::metamodel::AASMetamodel::define(nsIdx, *m_server.get());
            m_client = util::make_unique<Client_t>(endpoint, nsUri);
        }

        Server_t& getServer()
        {
            return *m_server.get();
        }

        Client_t& getClient()
        {
            return *m_client.get();
        }
    };
}
#endif