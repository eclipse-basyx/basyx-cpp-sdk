/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/MethodAttributes.h>

namespace basyx
{
    namespace opcua
    {
        MethodAttributes::MethodAttributes(const std::string& t_displayName,
            const std::string& t_description,
            const std::string& t_locale)
        {
            m_attributes = UA_MethodAttributes_new();

            *m_attributes = UA_MethodAttributes_default;

            m_attributes->description = UA_LOCALIZEDTEXT_ALLOC(t_locale.c_str(), t_description.c_str());
            m_attributes->displayName = UA_LOCALIZEDTEXT_ALLOC(t_locale.c_str(), t_displayName.c_str());
            m_attributes->userExecutable = true;
            m_attributes->executable = true;
        }

        MethodAttributes::~MethodAttributes()
        {
            UA_MethodAttributes_delete(m_attributes);
        }

        MethodAttributes & MethodAttributes::operator=(MethodAttributes && t_other) noexcept
        {
            if (m_attributes != nullptr)
            {
                UA_MethodAttributes_delete(m_attributes);
            }

            *m_attributes = UA_MethodAttributes_default;

            UA_MethodAttributes_copy(&t_other.getUA_MethodAttributes(), m_attributes);

            return *this;
        }

        MethodAttributes & MethodAttributes::operator=(const MethodAttributes & t_other)
        {
            if (m_attributes != nullptr)
            {
                UA_MethodAttributes_delete(m_attributes);
            }

            *m_attributes = UA_MethodAttributes_default;

            UA_MethodAttributes_copy(&t_other.getUA_MethodAttributes(), m_attributes);

            return *this;
        }

        UA_MethodAttributes & MethodAttributes::getUA_MethodAttributes() const
        {
            return *m_attributes;
        }
    }
}
