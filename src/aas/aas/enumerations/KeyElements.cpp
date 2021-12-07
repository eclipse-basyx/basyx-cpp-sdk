/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/enumerations/KeyElements.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::aas;

using enum_pair_t = std::pair<const char*, KeyElements>;

static const std::array<enum_pair_t, 27> string_to_enum = 
{
    std::make_pair("GlobalReference",  KeyElements::GlobalReference),
    std::make_pair("FragmentReference", KeyElements::FragmentReference),
    std::make_pair("AccessPermissionRule", KeyElements::AccessPermissionRule),
    std::make_pair("AnnotatedRelationshipElement", KeyElements::AnnotatedRelationshipElement),
    std::make_pair("BasicEvent", KeyElements::BasicEvent),
    std::make_pair("Blob", KeyElements::Blob),
    std::make_pair("Capability", KeyElements::Capability),
    std::make_pair("ConceptDictionary", KeyElements::ConceptDictionary),
    std::make_pair("DataElement", KeyElements::DataElement),
    std::make_pair("Entity", KeyElements::Entity),
    std::make_pair("Event", KeyElements::Event),
    std::make_pair("File", KeyElements::File),
    std::make_pair("MultiLanguageProperty", KeyElements::MultiLanguageProperty),
    std::make_pair("Operation", KeyElements::Operation),
    std::make_pair("OperationVariable", KeyElements::OperationVariable),
    std::make_pair("Property", KeyElements::Property),
    std::make_pair("Range", KeyElements::Range),
    std::make_pair("ReferenceElement", KeyElements::ReferenceElement),
    std::make_pair("RelationshipElement", KeyElements::RelationshipElement),
    std::make_pair("SubmodelElement", KeyElements::SubmodelElement),
    std::make_pair("SubmodelElementCollection", KeyElements::SubmodelElementCollection),
    std::make_pair("View", KeyElements::View),
    std::make_pair("Unknown", KeyElements::Unknown),
    std::make_pair("Asset", KeyElements::Asset),
    std::make_pair("AssetAdministrationShell", KeyElements::AssetAdministrationShell),
    std::make_pair("ConceptDescription", KeyElements::ConceptDescription),
    std::make_pair("Submodel", KeyElements::Submodel),
};

KeyElements KeyElements_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * KeyElements_::to_string(KeyElements value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

