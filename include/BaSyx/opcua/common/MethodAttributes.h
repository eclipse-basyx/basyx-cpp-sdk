/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef METHOD_ATTRIBUTES_H
#define METHOD_ATTRIBUTES_H

#include <string>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class MethodAttributes
        {
        public:
            MethodAttributes() = default;

            MethodAttributes(const std::string& t_displayName,
                const std::string& t_description,
                const std::string& t_locale);

            virtual ~MethodAttributes();

            MethodAttributes& operator=(MethodAttributes&& t_other) noexcept;

            MethodAttributes& operator=(const MethodAttributes& t_other);

            UA_MethodAttributes& getUA_MethodAttributes() const;

        private:
            UA_MethodAttributes* m_attributes = nullptr;
        };
    }
}

#endif