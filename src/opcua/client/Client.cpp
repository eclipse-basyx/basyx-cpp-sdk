/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <thread>
#include <BaSyx/opcua/client/Client.h>

namespace basyx
{
    namespace opcua
    {
        constexpr char Client::loggerName[];

        Client::~Client()
        {
            UA_StatusCode status;

            if (nullptr != m_client)
            {
                status = disconnect();

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger.error("Disconnection failed - " + shared::diag::getErrorString(status));
                }

                UA_Client_delete(m_client);

                m_client = nullptr;

                m_logger.info("Destroyed");
            }
        }

        UA_StatusCode basyx::opcua::Client::connect()
        {
            UA_StatusCode status;

            m_client = UA_Client_new();

            status = UA_ClientConfig_setDefault(UA_Client_getConfig(m_client));

            UA_ClientConfig *config = UA_Client_getConfig(m_client);

            config->clientContext = static_cast<Client*>(this);

            config->stateCallback = Client::statChangeHandler;

            config->subscriptionInactivityCallback = Client::subscriptionInactivityCallback;


            if (status != UA_STATUSCODE_GOOD)
            {
                m_logger.error("Configuration failure - " + shared::diag::getErrorString(status));

                return status;
            }

            status = UA_Client_connect(m_client, const_cast<char*>(m_endpoint.c_str()));

            if (status != UA_STATUSCODE_GOOD)
            {
                m_logger.error("Connection failed - " + shared::diag::getErrorString(status));

                return status;
            }
            else
            {
                m_logger.info("Connected ");
            }

            return UA_STATUSCODE_GOOD;
        }

        UA_StatusCode basyx::opcua::Client::disconnect()
        {
            m_logger.info("Disconnecting ...");

            auto status = UA_Client_disconnect(m_client);

            if (UA_STATUSCODE_GOOD != status)
            {
                m_logger.error("Disconnection failed - " + shared::diag::getErrorString(status));
            }

            return status;
        }

        UA_Client * Client::getUAClient()
        {
            return m_client;
        }

        void basyx::opcua::Client::setRootNode(const NodeId & t_node)
        {
            m_rootNode = t_node;
        }

        const NodeId & basyx::opcua::Client::getRootNode() const
        {
            return m_rootNode;
        }

        int32_t Client::getNamespaceIndexDefault() const
        {
            return  getNamespaceIndex(shared::Namespaces::BASYX_NS_URI);
        }

        int32_t Client::getNamespaceIndex(const std::string & t_namespaceIdentifier) const {

            uint16_t ret = 0;
            UA_StatusCode status = UA_STATUSCODE_GOOD;

            UA_String ns_uri = shared::string::UAStringFromStdString(t_namespaceIdentifier);
            status = UA_Client_NamespaceGetIndex(m_client, &ns_uri, &ret);

            if (status != UA_STATUSCODE_GOOD)
            {
                return NAMESPACE_UNKOWN;
            }

            return static_cast<int>(ret);
        }

        void Client::addSubscription(Subscription& t_subscriptions)
        {
            Subscription* subsription;

            UA_CreateSubscriptionRequest subscriptionRequest;// = UA_CreateSubscriptionRequest_default();

            UA_CreateSubscriptionRequest_init(&subscriptionRequest);

            subscriptionRequest.requestedPublishingInterval = 500.0;
            subscriptionRequest.requestedLifetimeCount = 10000;
            subscriptionRequest.requestedMaxKeepAliveCount = 10;
            subscriptionRequest.maxNotificationsPerPublish = 0;
            subscriptionRequest.publishingEnabled = true;
            subscriptionRequest.priority = 0;

            subscriptionRequest.requestedPublishingInterval = t_subscriptions.getSamplingInterval();

            auto subscriptionResponse = UA_Client_Subscriptions_create(
                m_client,
                subscriptionRequest,
                this,
                NULL,
                NULL
            );


            m_subsriptions.emplace(subscriptionResponse.subscriptionId, std::move(t_subscriptions));

            m_logger.trace("New subscription added - ID = " + std::to_string(subscriptionResponse.subscriptionId));

            auto it = m_subsriptions.find(subscriptionResponse.subscriptionId);

            if (it != m_subsriptions.end())
            {
                subsription = &it->second;
            }
            else
            {
                m_logger.error("Subscription Item : " + std::to_string(subscriptionResponse.subscriptionId) + " not found!");
                return;
            }

            UA_UInt32 monListIndex(0);
            for (const auto& monItem : subsription->getMonitoringList())
            {

                auto monitoringRequest = UA_MonitoredItemCreateRequest_default(std::get<0>(monItem));

                monitoringRequest.requestedParameters.samplingInterval = std::get<1>(monItem);

                auto monitoringResponse = UA_Client_MonitoredItems_createDataChange(
                    m_client,
                    subscriptionResponse.subscriptionId,
                    UA_TIMESTAMPSTORETURN_BOTH,
                    monitoringRequest,
                    this,
                    dataChangeHandler,
                    NULL
                );

                if (monitoringResponse.statusCode != UA_STATUSCODE_GOOD)
                {
                    m_logger.error("MonitoringItem cannot be added - " +
                        std::string(UA_StatusCode_name(monitoringResponse.statusCode))
                    );
                    return;
                }
                /* Updates MonitoringItem id to the callback list index*/
                subsription->updateCallbackMap(monitoringResponse.monitoredItemId, monListIndex);
                m_logger.trace("Monitoring items added - ID = " + std::to_string(monitoringResponse.monitoredItemId));
                monListIndex++;
            }
        }

        void Client::dataChangeHandler(UA_Client* t_client,
            UA_UInt32 t_subId,
            void* t_subContext,
            UA_UInt32 t_monId,
            void* t_monContext,
            UA_DataValue* t_value)
        {

            auto context = static_cast<Client*>(t_monContext);

            auto it = context->getSubscriptions().find(t_subId);

            if (it != context->getSubscriptions().end())
            {
                auto subscriptionList = &it->second;

                if (subscriptionList)
                {
                    if (t_value != nullptr)
                    {
                        subscriptionList->invokeSubsriptionCallback(t_subId, *t_value);

                        subscriptionList->invokeMonitoringItemCallback(t_subId, t_monId, *t_value);
                    }
                }

            }
            else
            {
                basyx::log::topic(Client::loggerName).error("Subscription : " + std::to_string(t_subId) + " not found");
            }

        }

        void Client::subscriptionInactivityCallback(UA_Client* t_client, UA_UInt32 t_subId, void * t_subContext)
        {
            if ((t_client == nullptr) || (t_subContext == nullptr))
            {
                basyx::log::topic(Client::loggerName).error("Client for Subscription context not intilitialized");
                return;
            }

            auto clientInstance{ static_cast<Client*>(t_subContext) };

            basyx::log::topic(Client::loggerName).error("Inactivity for subscription " + std::to_string(t_subId));

            /* When there is no activity (eg: connection lost), reconnect */
            clientInstance->connect();
        }

        void Client::statChangeHandler(UA_Client* t_client, UA_ClientState clientState)
        {
            if (t_client == nullptr)
            {
                basyx::log::topic(Client::loggerName).error("Client not intilitialized");
                return;
            }
            switch (clientState)
            {
            case UA_CLIENTSTATE_DISCONNECTED:
                basyx::log::topic(Client::loggerName).info("The client is disconnected");
                break;
            case UA_CLIENTSTATE_WAITING_FOR_ACK:
                basyx::log::topic(Client::loggerName).info("Waiting for ack");
                break;
            case UA_CLIENTSTATE_CONNECTED:
                basyx::log::topic(Client::loggerName).info("A TCP connection to the server is open");
                break;
            case UA_CLIENTSTATE_SECURECHANNEL:
                basyx::log::topic(Client::loggerName).info("A SecureChannel to the server is open");
                break;
            case UA_CLIENTSTATE_SESSION:
            {
                basyx::log::topic(Client::loggerName).info("A session with the server is open");

                auto* config = UA_Client_getConfig(t_client);

                auto& clientInstance = *static_cast<Client*>(config->clientContext);
                /* Re-subscribe when a new session is started */
                for (auto& subscription : clientInstance.getSubscriptionList())
                {
                    clientInstance.addSubscription(subscription);
                }
            }
            break;
            case UA_CLIENTSTATE_SESSION_RENEWED:
                basyx::log::topic(Client::loggerName).info("A session with the server is open (renewed)");
                break;
            case UA_CLIENTSTATE_SESSION_DISCONNECTED:
                basyx::log::topic(Client::loggerName).info("Session disconnected");
                break;
            }
        }

        void Client::removeSubscription(uint32_t t_subId)
        {

            UA_DeleteSubscriptionsRequest delReq;
            UA_DeleteSubscriptionsRequest_init(&delReq);
            delReq.subscriptionIds = &t_subId;
            delReq.subscriptionIdsSize = 1;

            auto response = UA_Client_Subscriptions_delete(m_client, delReq);

            if (response.responseHeader.serviceResult != UA_STATUSCODE_GOOD) {
                m_logger.error("Subscription ID -" + std::to_string(t_subId) + " cannot be deleted ");
                return;
            }

            m_logger.trace("Subscription ID -" + std::to_string(t_subId) + " deleted ");
        }

        const std::unordered_map<uint32_t, Subscription>& Client::getSubscriptions() const
        {
            return m_subsriptions;
        }

        std::vector<Subscription>& Client::getSubscriptionList()
        {
            return m_subscriptionList;
        }

        void Client::listen()
        {
            if (m_subsriptions.empty()) {
                m_logger.info("No subscriptions to listen");
                return;
            }
            m_logger.info("Listening to MonitoredItems ...");

            while (m_running.load()) {
                UA_StatusCode status = UA_Client_connect(m_client, m_endpoint.c_str());

                if (status != UA_STATUSCODE_GOOD) {
                    m_logger.error("Client not connected, retrying in 1 sec");
                    UA_sleep_ms(1000);
                    continue;
                }
                UA_Client_run_iterate(m_client, 1000);
            }
            /* When the listening is terminated, remove the subscriptions form the server */
            for (const auto& subsription : m_subsriptions) {
                removeSubscription(subsription.first);
            }
        }

        void Client::abort()
        {
            m_running = false;
        }
    }
}