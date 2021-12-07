/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/LocalizedText.h>

namespace basyx
{
    namespace opcua
    {

        LocalizedText::LocalizedText(const UA_LocalizedText& t_text)
        {
            std::string locale(reinterpret_cast<char*>(t_text.locale.data), t_text.locale.length);
            std::string text(reinterpret_cast<char*>(t_text.text.data), t_text.text.length);

            m_localizedText = std::make_tuple(locale, text);
        }

       //LocalizedText & LocalizedText::operator=(LocalizedText && t_other) noexcept
       //{
       //    std::get<0>(m_localizedText) = std::move(t_other.getLocale());
       //    std::get<1>(m_localizedText) = std::move(t_other.getText());
       //
       //    return *this;
       //}

        LocalizedText & LocalizedText::operator=(const LocalizedText & t_other)
        {
            std::get<0>(m_localizedText) = t_other.getLocale();
            std::get<1>(m_localizedText) = t_other.getText();

            return *this;
        }

        const std::string LocalizedText::getLocale() const
        {
            return std::get<0>(m_localizedText);
        }

        const std::string LocalizedText::getText() const
        {
            return std::get<1>(m_localizedText);
        }

        bool LocalizedText::operator==(const LocalizedText & t_other)
        {
            return (this->getLocale() == t_other.getLocale())
                && (this->getText() == t_other.getText());
        }

        bool LocalizedText::operator!=(const LocalizedText & t_other)
        {
            return !(*this == t_other);
        }

        UA_LocalizedText LocalizedText::getUA_LocalizedText() const
        {
            return UA_LOCALIZEDTEXT(const_cast<char*>(getLocale().c_str()),
                const_cast<char*>(getText().c_str()));
        }

        std::string LocalizedText::toString() const
        {
            return "(" + getLocale() + ")" + getText();
        }
    }
}