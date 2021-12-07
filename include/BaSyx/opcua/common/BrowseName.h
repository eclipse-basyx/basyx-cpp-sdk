/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BROWSE_NAME_H
#define BROWSE_NAME_H

#include <string>
#include <tuple>
#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
    namespace opcua
    {
        class BrowseName
        {
        private:
            struct Attrs
            {
                static constexpr const size_t NameSpaceIndex = 0;
                static constexpr const size_t BrowseText = 1;
            };
        public:
            BrowseName() : m_name(std::make_tuple(0, std::string())) {}

            BrowseName(BrowseName&& t_other) noexcept :
                m_name(std::move(t_other.m_name)) {}

            BrowseName(const BrowseName& t_other) :m_name(t_other.m_name) {}

            BrowseName& operator=(BrowseName&& t_other) noexcept
            {
                if (this != &t_other)
                {
                    m_name = std::move(t_other.m_name);
                }
                return *this;
            }

            BrowseName& operator=(const BrowseName& t_other)
            {
                if (this != &t_other)
                {
                    m_name = t_other.m_name;
                }
                return *this;
            }

            BrowseName(const std::string& t_browsNameString)
            {
                auto browseNameVect = std::move(opcua::shared::string::splitByColon(t_browsNameString));

                m_name = std::make_tuple(
                    static_cast<int32_t>(std::stoi(browseNameVect.at(0))),
                    browseNameVect.at(1)
                );
            }

            BrowseName(int32_t t_namespaceIdx, const std::string& t_text) :
                m_name{ std::make_tuple(t_namespaceIdx, std::move(t_text)) } {}

            virtual ~BrowseName() = default;

            const std::string& getText() const
            {
                return std::get<Attrs::BrowseText>(m_name);
            }

            int32_t getNamespaceIdx() const
            {
                return std::get<Attrs::NameSpaceIndex>(m_name);
            }

            static BrowseName build(int32_t t_namespaceIdx, const std::string& t_text)
            {
                return BrowseName(t_namespaceIdx, std::move(t_text));
            }

            bool operator ==(const BrowseName& t_browseName)
            {
                return ((std::get<Attrs::NameSpaceIndex>(this->m_name) == t_browseName.getNamespaceIdx()) &&
                    (std::get<Attrs::BrowseText>(this->m_name) == t_browseName.getText()));
            }

            std::string toString()
            {
                return std::to_string(getNamespaceIdx()) + ":" + getText();
            }

        private:
            std::tuple<int32_t, std::string> m_name;
        };

    }
}
#endif