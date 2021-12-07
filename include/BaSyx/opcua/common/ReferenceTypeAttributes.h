/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef REFERENCETYPE_ATTRIBUTES_H
#define REFERENCETYPE_ATTRIBUTES_H

#include <string>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class ReferenceTypeAttributes
        {
        public:
            ReferenceTypeAttributes() = default;

            ReferenceTypeAttributes(const std::string& t_displayName,
                const std::string& t_description,
                const std::string& t_locale);

            virtual ~ReferenceTypeAttributes();

            ReferenceTypeAttributes& operator=(ReferenceTypeAttributes&& t_other) noexcept;

            ReferenceTypeAttributes& operator=(const ReferenceTypeAttributes& t_other);

            UA_ReferenceTypeAttributes& getUA_ReferenceTypeAttributes() const;

        private:
            UA_ReferenceTypeAttributes* m_attributes = nullptr;
        };
    }
}
#endif