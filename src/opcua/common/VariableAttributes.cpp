/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/VariableAttributes.h>

namespace basyx
{
    namespace opcua
    {
        VariableAttributes::VariableAttributes(const NodeId & t_typeId,
            const std::string & t_displayName,
            const std::string & t_description,
            const std::string & t_locale)
        {
            m_attributes = UA_VariableAttributes_new();

            *m_attributes = UA_VariableAttributes_default;

            m_attributes->description = UA_LOCALIZEDTEXT_ALLOC(t_locale.c_str(), t_description.c_str());
            m_attributes->displayName = UA_LOCALIZEDTEXT_ALLOC(t_locale.c_str(), t_displayName.c_str());
            m_attributes->dataType = t_typeId.getUANode();
            m_attributes->accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        }

        VariableAttributes::~VariableAttributes()
        {
            UA_VariableAttributes_delete(m_attributes);
        }

        VariableAttributes & VariableAttributes::operator=(VariableAttributes && t_other) noexcept
        {
            if (m_attributes != nullptr)
            {
                UA_VariableAttributes_delete(m_attributes);
            }

            *m_attributes = UA_VariableAttributes_default;

            UA_VariableAttributes_copy(&t_other.getUA_VariableAttributes(), m_attributes);

            return *this;
        }

        VariableAttributes & VariableAttributes::operator=(const VariableAttributes & t_other)
        {
            if (m_attributes != nullptr)
            {
                UA_VariableAttributes_delete(m_attributes);
            }

            *m_attributes = UA_VariableAttributes_default;

            UA_VariableAttributes_copy(&t_other.getUA_VariableAttributes(), m_attributes);

            return *this;
        }

        UA_VariableAttributes & VariableAttributes::getUA_VariableAttributes() const
        {
            return *m_attributes;
        }
    }
}
