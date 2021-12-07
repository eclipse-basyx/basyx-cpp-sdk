/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef SUBSCRPTION_LIST_H
#define SUBSCRPTION_LIST_H

#include <tuple>
#include <vector>
#include <functional>
#include <unordered_map>
#include <BaSyx/log/log.h>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx {
    namespace opcua {

        class Subscription
        {
        public:
            Subscription(std::function<void(uint32_t, UA_DataValue&)> t_subscriptionCallback)
                : m_samplingInterval(500.0), m_subscriptionCallback(t_subscriptionCallback) {}

            Subscription(double t_samplingInterval,
                std::function<void(uint32_t, UA_DataValue&)> t_subscriptionCallback)
                : m_samplingInterval(t_samplingInterval), m_subscriptionCallback(t_subscriptionCallback) {}

            ~Subscription() = default;

            void addMonitoringItem(const UA_NodeId& t_node,
                double t_samplingInterval,
                std::function<void(UA_DataValue&)> t_callback);

            void addMonitoringItem(const UA_NodeId& t_node, double t_samplingInterval);

            double getSamplingInterval() const;

            void invokeSubsriptionCallback(uint32_t t_subId, UA_DataValue& t_value) const;

            void invokeMonitoringItemCallback(uint32_t t_subId, uint32_t t_monId, UA_DataValue& t_value) const;

            void updateCallbackMap(uint32_t t_monId, uint32_t t_ListIndex);

            std::vector<std::tuple<UA_NodeId, double, std::function<void(UA_DataValue&)>>>& getMonitoringList();

        private:
            double m_samplingInterval;

            std::function<void(uint32_t, UA_DataValue&)> m_subscriptionCallback;

            std::vector<std::tuple<UA_NodeId, double, std::function<void(UA_DataValue&)>>> m_list;
            /*MonId , List Index */
            std::unordered_map<uint32_t, size_t> m_monCallbacks;

        };

    }
}

#endif