/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/metamodel/IAASIdentifiableType.h>

using namespace basyx::opcua;
using namespace basyx::opcua::aas::metamodel;

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            namespace metamodel
            {
                constexpr char IAASIdentifiableType::AttrNames::InstanceName[];
                constexpr char IAASIdentifiableType::AttrNames::BrowseText[];
                constexpr char IAASIdentifiableType::AttrNames::DisplayName[];
                constexpr char IAASIdentifiableType::AttrNames::Description[];
                constexpr char IAASIdentifiableType::AttrNames::NodeHandle[];
                constexpr char IAASIdentifiableType::AttrNames::BrowseText_Identification[];
                constexpr char IAASIdentifiableType::AttrNames::DisplayName_Identification[];
                constexpr char IAASIdentifiableType::AttrNames::Description_Identification[];
                constexpr char IAASIdentifiableType::AttrNames::NodeHandle_Identification[];
                constexpr char IAASIdentifiableType::AttrNames::BrowseText_Administration[];
                constexpr char IAASIdentifiableType::AttrNames::DisplayName_Administration[];
                constexpr char IAASIdentifiableType::AttrNames::Description_Administration[];
                constexpr char IAASIdentifiableType::AttrNames::NodeHandle_Administration[];
            }
        }
    }
}
