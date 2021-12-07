/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OBJECTTYPE_ATTRIBUTES_H
#define OBJECTTYPE_ATTRIBUTES_H

#include <string>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class ObjectTypeAttributes
        {
        public:
            ObjectTypeAttributes() = default;

            ObjectTypeAttributes(const std::string& t_displayName,
                const std::string& t_description,
                const std::string& t_locale);

            virtual ~ObjectTypeAttributes();

            ObjectTypeAttributes& operator=(ObjectTypeAttributes&& t_other) noexcept;

            ObjectTypeAttributes& operator=(const ObjectTypeAttributes& t_other);

            UA_ObjectTypeAttributes& getUA_ObjectTypeAttributes() const;

        private:
            UA_ObjectTypeAttributes* m_attributes = nullptr;
        };
    }
}

#endif