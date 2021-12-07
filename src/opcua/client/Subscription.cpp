/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/client/Subscription.h>

namespace basyx
{
    namespace opcua
    {
        void Subscription::addMonitoringItem(const UA_NodeId& t_node,
            double t_samplingInterval,
            std::function<void(UA_DataValue&)> t_callback)
        {

            m_list.emplace_back(
                std::make_tuple(t_node, t_samplingInterval, t_callback)
            );
        }

        void Subscription::addMonitoringItem(const UA_NodeId& t_node, double t_samplingInterval)
        {
            m_list.emplace_back(
                std::make_tuple(t_node, t_samplingInterval, nullptr)
            );
        }

        double Subscription::getSamplingInterval() const
        {
            return m_samplingInterval;
        }

        void Subscription::invokeSubsriptionCallback(uint32_t t_subId, UA_DataValue& t_value) const
        {
            m_subscriptionCallback(t_subId, t_value);
            basyx::log::topic("basyx::opcua::Client").trace(
                "SubscriptionItem - " + std::to_string(t_subId) + " changed"
            );
        }

        void Subscription::invokeMonitoringItemCallback(uint32_t t_subId, uint32_t t_monId, UA_DataValue& t_value) const
        {
            auto it = m_monCallbacks.find(t_monId);
            if (it != m_monCallbacks.end()) {
                if (std::get<2>(m_list.at(it->second)))
                {
                    std::get<2>(m_list.at(it->second))(t_value);
                }
                basyx::log::topic("basyx::opcua::Client").trace(
                    "MonitoredItem - " + std::to_string(t_monId) +
                    " of SubscriptionItem - " + std::to_string(t_subId) +
                    " changed"
                );
            }
            else {
                basyx::log::topic("basyx::opcua::Client").error("Monitored Item : " + std::to_string(t_monId) + " callback failed");
            }
        }

        void Subscription::updateCallbackMap(uint32_t t_monId, uint32_t t_ListIndex)
        {
            m_monCallbacks.emplace(t_monId, t_ListIndex);
        }

        std::vector<std::tuple<UA_NodeId, double, std::function<void(UA_DataValue&)>>>& Subscription::getMonitoringList()
        {
            return m_list;
        }

    }
}