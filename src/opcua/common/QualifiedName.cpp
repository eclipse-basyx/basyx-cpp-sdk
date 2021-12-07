/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/QualifiedName.h>

namespace basyx
{
    namespace opcua
    {
        QualifiedName::QualifiedName(uint16_t t_nameSpaceIndex, const std::string & t_text)
        {
            m_name = UA_QualifiedName_new();

            *m_name = UA_QUALIFIEDNAME_ALLOC(t_nameSpaceIndex, const_cast<char*>(t_text.c_str()));
        }

        QualifiedName::QualifiedName(const UA_QualifiedName & t_name)
        {
            if (m_name != nullptr)
            {
                UA_QualifiedName_delete(m_name);
            }

            m_name = UA_QualifiedName_new();

            UA_QualifiedName_copy(&t_name, m_name);
        }

        QualifiedName::~QualifiedName()
        {
            UA_QualifiedName_delete(m_name);

            m_name = nullptr;
        }

        QualifiedName & QualifiedName::operator=(QualifiedName && t_other) noexcept
        {
            if (m_name != nullptr)
            {
                UA_QualifiedName_delete(m_name);
            }

            m_name = UA_QualifiedName_new();

            UA_QualifiedName_copy(&t_other.getUA_QualifiedName(), m_name);

            return *this;
        }

        QualifiedName & QualifiedName::operator=(const QualifiedName & t_other)
        {
            if (m_name != nullptr)
            {
                UA_QualifiedName_delete(m_name);
            }

            m_name = UA_QualifiedName_new();

            UA_QualifiedName_copy(&t_other.getUA_QualifiedName(), m_name);

            return *this;
        }

        bool QualifiedName::operator==(QualifiedName & t_other)
        {
            return UA_QualifiedName_equal(&t_other.getUA_QualifiedName(), m_name);
        }

        bool QualifiedName::operator!=(QualifiedName & t_other)
        {
            return !(*this == t_other);
        }

        std::string QualifiedName::toString() const
        {
            return std::string(
                std::to_string(m_name->namespaceIndex) + ":" +
                std::string(reinterpret_cast<char*>(m_name->name.data), m_name->name.length)
            );
        }
    }
}
