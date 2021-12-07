/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_SERVER_H
#define OPCUA_SERVER_H

#include <atomic>
#include <thread>
#include <BaSyx/util/util.h>
#include <BaSyx/log/log.h>
#include <BaSyx/opcua/server/open62541Server.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
	namespace opcua
	{
		class Server
		{
			static constexpr int SERVER_LOOP_US_MULT{ 10 };
		public:
			Server() = delete;

			Server(uint16_t t_port) :
				m_port(t_port),
				m_logger("basyx::opuca::Server"),
				m_rootNode(UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER)),
				m_running(true),
				m_serverUp(false) {}

			Server(uint16_t t_port, const std::string& t_nsUri) :
				m_port(t_port),
				m_namespace(t_nsUri),
				m_logger("basyx::opuca::Server"),
				m_rootNode(UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER)),
				m_running(true),
				m_serverUp(false) {}

			virtual ~Server();

			void initialize();

			void run();

			void runInBackground();

			void abort();

			bool isServerUp();

			void waitUntilUp();

			void setRootNode(const NodeId& t_nodeId);

			const NodeId& getRootNode() const;

			uint16_t addNameSpace(const char* t_namespaceUri);

			UA_Server* getUAServer();

			int32_t getNamespaceIndexDefault() const;

			int32_t getNamespaceIndex(const std::string & t_namespaceIdentifier) const;

		private:
			UA_Server* m_server = nullptr;
			NodeId m_rootNode;
			uint16_t m_port;
			std::string  m_namespace;
			basyx::log m_logger;
			std::atomic<bool> m_running;
			std::atomic<bool> m_serverUp;
		};

	}
}

#endif
