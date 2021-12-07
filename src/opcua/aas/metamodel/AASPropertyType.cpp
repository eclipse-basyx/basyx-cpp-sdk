/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/metamodel/AASPropertyType.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            namespace metamodel
            {
                constexpr char AASPropertyType::AttrNames::InstanceName[];
                constexpr char AASPropertyType::AttrNames::BrowseText[];
                constexpr char AASPropertyType::AttrNames::DisplayName[];
                constexpr char AASPropertyType::AttrNames::Description[];
                constexpr char AASPropertyType::AttrNames::NodeHandle[];
                constexpr char AASPropertyType::AttrNames::BrowseText_Value[];
                constexpr char AASPropertyType::AttrNames::DisplayName_Value[];
                constexpr char AASPropertyType::AttrNames::Description_Value[];
                constexpr char AASPropertyType::AttrNames::NodeHandle_Value[];
                constexpr char AASPropertyType::AttrNames::BrowseText_ValueType[];
                constexpr char AASPropertyType::AttrNames::DisplayName_ValueType[];
                constexpr char AASPropertyType::AttrNames::Description_ValueType[];
                constexpr char AASPropertyType::AttrNames::NodeHandle_ValueType[];
                constexpr char AASPropertyType::AttrNames::BrowseText_ReferenceValueId[];
                constexpr char AASPropertyType::AttrNames::DisplayName_ReferenceValueId[];
                constexpr char AASPropertyType::AttrNames::Description_ReferenceValueId[];
                constexpr char AASPropertyType::AttrNames::NodeHandle_ReferenceValueId[];

                constexpr char AASPropertyType::TypeName::bool_[];
                constexpr char AASPropertyType::TypeName::int8[];
                constexpr char AASPropertyType::TypeName::uint8[];
                constexpr char AASPropertyType::TypeName::int16[];
                constexpr char AASPropertyType::TypeName::uint16[];
                constexpr char AASPropertyType::TypeName::int32[];
                constexpr char AASPropertyType::TypeName::uint32[];
                constexpr char AASPropertyType::TypeName::int64[];
                constexpr char AASPropertyType::TypeName::uint64[];
                constexpr char AASPropertyType::TypeName::float_[];
                constexpr char AASPropertyType::TypeName::double_[];
                constexpr char AASPropertyType::TypeName::string_[];
                constexpr char AASPropertyType::TypeName::date[];
                constexpr char AASPropertyType::TypeName::time[];
                constexpr char AASPropertyType::TypeName::anyUri[];
                constexpr char AASPropertyType::TypeName::dayTimeDuration[];
                constexpr char AASPropertyType::TypeName::yearMonthDuration[];
                constexpr char AASPropertyType::TypeName::dateTime[];
                constexpr char AASPropertyType::TypeName::gDay[];
                constexpr char AASPropertyType::TypeName::gMonth[];
                constexpr char AASPropertyType::TypeName::gMonthDay[];
                constexpr char AASPropertyType::TypeName::gYear[];
                constexpr char AASPropertyType::TypeName::gYearMonth[];
            }
        }
    }
}