/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef QUALIFIED_NAME_H
#define QUALIFIED_NAME_H

#include <string>
#include <BaSyx/opcua/client/open62541Client.h>

namespace basyx
{
    namespace opcua
    {
        class QualifiedName
        {
        public:
            QualifiedName() : QualifiedName(0, "") {}

            QualifiedName(uint16_t t_nameSpaceIndex, const std::string& t_text);

            QualifiedName(const UA_QualifiedName& t_node);

            ~QualifiedName();

            QualifiedName& operator=(QualifiedName&& t_other) noexcept;

            QualifiedName& operator=(const QualifiedName& t_other);

            bool operator ==(QualifiedName& t_other);

            bool operator !=(QualifiedName& t_other);

            UA_QualifiedName& getUA_QualifiedName() const
            {
                return *m_name;
            }

            std::string toString() const;

        private:
            UA_QualifiedName* m_name = nullptr;
        };
    }
}



#endif