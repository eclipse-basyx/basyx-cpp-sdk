/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef LOCALIZED_TEXT_H
#define LOCALIZED_TEXT_H

#include <string>
#include <tuple>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class LocalizedText
        {
        public:
            LocalizedText() : LocalizedText(std::string(), std::string()){}

            LocalizedText(const std::string& t_locale, const std::string& t_text):
                m_localizedText(std::make_tuple(t_locale, t_text)){}

            LocalizedText(const UA_LocalizedText& t_node);

            ~LocalizedText() = default;

            //LocalizedText& operator=(LocalizedText&& t_other) noexcept;

            LocalizedText& operator=(const LocalizedText& t_other);

            const std::string getLocale() const;

            const std::string getText() const;

            bool operator ==(const LocalizedText& t_other);

            bool operator !=(const LocalizedText& t_other);

            UA_LocalizedText getUA_LocalizedText() const;

            std::string toString() const;
        private:
            std::tuple<std::string, std::string> m_localizedText;
        };
    }
}
#endif