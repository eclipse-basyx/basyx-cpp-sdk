/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OBJECT_ATTRIBUTES_H
#define OBJECT_ATTRIBUTES_H

#include <string>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class ObjectAttributes
        {
        public:
            ObjectAttributes() = default;

            ObjectAttributes(const std::string& t_displayName,
                const std::string& t_description,
                const std::string& t_locale);

            virtual ~ObjectAttributes();

            ObjectAttributes& operator=(ObjectAttributes&& t_other) noexcept;

            ObjectAttributes& operator=(const ObjectAttributes& t_other);

            UA_ObjectAttributes& getUA_ObjectAttributes() const;

        private:
            UA_ObjectAttributes* m_attributes = nullptr;
        };
    }
}

#endif