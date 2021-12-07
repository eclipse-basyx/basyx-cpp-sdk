/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/ObjectTypeAttributes.h>

namespace basyx
{
    namespace opcua
    {
        ObjectTypeAttributes::ObjectTypeAttributes(const std::string& t_displayName,
            const std::string& t_description,
            const std::string& t_locale)
        {
            m_attributes = UA_ObjectTypeAttributes_new();

            *m_attributes = UA_ObjectTypeAttributes_default;

            m_attributes->description = UA_LOCALIZEDTEXT_ALLOC(t_locale.c_str(), t_description.c_str());
            m_attributes->displayName = UA_LOCALIZEDTEXT_ALLOC(t_locale.c_str(), t_displayName.c_str());
        }

        ObjectTypeAttributes::~ObjectTypeAttributes()
        {
            UA_ObjectTypeAttributes_delete(m_attributes);
        }

        ObjectTypeAttributes & ObjectTypeAttributes::operator=(ObjectTypeAttributes && t_other) noexcept
        {
            if (m_attributes != nullptr)
            {
                UA_ObjectTypeAttributes_delete(m_attributes);
            }

            *m_attributes = UA_ObjectTypeAttributes_default;

            UA_ObjectTypeAttributes_copy(&t_other.getUA_ObjectTypeAttributes(), m_attributes);

            return *this;
        }

        ObjectTypeAttributes & ObjectTypeAttributes::operator=(const ObjectTypeAttributes & t_other)
        {
            if (m_attributes != nullptr)
            {
                UA_ObjectTypeAttributes_delete(m_attributes);
            }

            *m_attributes = UA_ObjectTypeAttributes_default;

            UA_ObjectTypeAttributes_copy(&t_other.getUA_ObjectTypeAttributes(), m_attributes);

            return *this;
        }

        UA_ObjectTypeAttributes & ObjectTypeAttributes::getUA_ObjectTypeAttributes() const
        {
            return *m_attributes;
        }
    }
}
