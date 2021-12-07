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

namespace basyx
{
	namespace tests
	{
		namespace opcua
		{
            class OPCUATestSetup
            {
                using Server_t = basyx::opcua::Server;
                using Client_t = basyx::opcua::Client;
                using AASMetamodel_t = basyx::opcua::aas::metamodel::AASMetamodel;
             private:
                std::unique_ptr<basyx::opcua::Server> m_server;
                std::unique_ptr<basyx::opcua::Client> m_client;
                
                const char* serverAddress = "localhost";
                // Namespace where the AAS metamodel will be defined
                const char* nsUri = basyx::opcua::shared::Namespaces::BASYX_NS_URI;

             public:

                OPCUATestSetup(const int t_port)
                {
                    std::string clientEndPoint("opc.tcp://" + std::string(serverAddress) +":"+ std::to_string(t_port));

                    m_server = util::make_unique<Server_t>(t_port, nsUri);
                    m_server->initialize();

                    auto nsIdx = m_server->getNamespaceIndex(nsUri);
                    // Create the AAS Metamdodel in the server
                    AASMetamodel_t::define(nsIdx, *m_server.get());
                    // Detach ther server thread
                    m_server->runInBackground();
                    // Wait until the server is up
                    while (!m_server->isServerUp()) { ; }

                    m_client =  util::make_unique<Client_t>(clientEndPoint, nsUri);

                    m_client->connect();

                }

                Server_t& getServer()
                {
                    return * m_server.get();
                }

                Client_t& getClient()
                {
                    return *m_client.get();
                }
            };
        }
    }
}
#endif