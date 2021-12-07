/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/metamodel/AASMultiLanguagePropertyType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>
#include <BaSyx/opcua/aas/metamodel/AASReferenceType.h>
#include <BaSyx/opcua/aas/metamodel/AASReference.h>
#include <BaSyx/opcua/aas/metamodel/DictionaryEntryFragmentedId.h>
#include <BaSyx/opcua/aas/metamodel/DictionaryEntryIdShort.h>

using namespace basyx::opcua::aas::metamodel;

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            namespace metamodel
            {
                constexpr char AASMultiLanguagePropertyType::AttrNames::BrowseText[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::DisplayName[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::Description[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::NodeHandle[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::BrowseName_Value[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::DisplayName_Value[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::Description_Value[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::NodeHandle_Value[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::BrowseName_ReferenceValueId[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::DisplayName_ReferenceValueId[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::Description_ReferenceValueId[];
                constexpr char AASMultiLanguagePropertyType::AttrNames::NodeHandle_ReferenceValueId[];
            }
        }
    }
}
