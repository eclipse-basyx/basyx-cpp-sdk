/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_CLIENT_H
#define OPCUA_CLIENT_H

#include <string>
#include <atomic>
#include <unordered_map>
#include <tuple>
#include <BaSyx/shared/types.h>
#include <BaSyx/shared/object.h>
#include <BaSyx/log/log.h>
#include <BaSyx/opcua/common/BrowsePath.h>
#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/client/Subscription.h>

namespace basyx 
{
	namespace opcua 
	{
		class Client
		{
		public:
			static constexpr const int  NAMESPACE_UNKOWN = -1;
			static constexpr const char loggerName[] = "basyx::opcua::Client";

			Client() = delete;

			Client(const std::string& t_endpoint,
				   const std::string& t_namespaceUri = shared::Namespaces::BASYX_NS_URI) :
				   m_endpoint(t_endpoint),
				   m_running(true),
				   m_namespace(t_namespaceUri),
				   m_rootNode(UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER)),
				   m_logger(loggerName) {}

			Client(const std::string& t_endpoint,
				   std::vector<Subscription> t_subscriptionList,
				   const std::string& t_namespaceUri = shared::Namespaces::BASYX_NS_URI) :
				   m_endpoint(t_endpoint),
				   m_subscriptionList(t_subscriptionList),
				   m_running(true),
				   m_namespace(t_namespaceUri),
				   m_rootNode(UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER)),
				   m_logger(loggerName) {}

			virtual ~Client();

			UA_StatusCode connect();

			UA_StatusCode disconnect();

			UA_Client* getUAClient();

			void setRootNode(const NodeId& t_node);

			const NodeId& getRootNode() const;

			int32_t getNamespaceIndexDefault() const;

			int32_t getNamespaceIndex(const std::string & t_namespaceIdentifier) const;

			void addSubscription(Subscription& t_subscriptions);

			std::vector<Subscription>& getSubscriptionList();

			void listen();

			void abort();

			void removeSubscription(uint32_t t_subId);

			const std::unordered_map<uint32_t, Subscription>& getSubscriptions() const;

		private:
			/* Reference : examples of open62541 */
			static void dataChangeHandler(UA_Client* t_client,
										  UA_UInt32 t_subId,
										  void* t_subContext,
										  UA_UInt32 t_monId,
										  void* t_monContext,
										  UA_DataValue* t_value);

			static void subscriptionInactivityCallback(UA_Client *client,
													   UA_UInt32 subId,
				                                       void *subContext);

			static void statChangeHandler(UA_Client *client,
										  UA_ClientState clientState);
		private:
			UA_Client*   m_client = nullptr;
			NodeId    m_rootNode;
			std::string  m_namespace;
			std::string  m_endpoint;
			std::atomic<bool> m_running;
			std::vector<Subscription> m_subscriptionList;
			std::unordered_map<uint32_t, Subscription> m_subsriptions;
			basyx::log m_logger;
		};
	}
}
#endif
