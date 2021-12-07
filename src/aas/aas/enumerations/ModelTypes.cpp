/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/enumerations/ModelTypes.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::aas;

using enum_pair_t = std::pair<const char*, ModelTypes>;

static const std::array<enum_pair_t, 29> string_to_enum = 
{
    std::make_pair("Asset",  ModelTypes::Asset),
    std::make_pair("AssetAdministrationShell", ModelTypes::AssetAdministrationShell),
    std::make_pair("ConceptDescription", ModelTypes::ConceptDescription),
    std::make_pair("Submodel", ModelTypes::Submodel),
    std::make_pair("AccessPermissionRule", ModelTypes::AccessPermissionRule),
    std::make_pair("AnnotatedRelationshipElement", ModelTypes::AnnotatedRelationshipElement),
    std::make_pair("BasicEvent", ModelTypes::BasicEvent),
    std::make_pair("Blob", ModelTypes::Blob),
    std::make_pair("Capability", ModelTypes::Capability),
    std::make_pair("ConceptDictionary", ModelTypes::ConceptDictionary),
    std::make_pair("DataElement", ModelTypes::DataElement),
    std::make_pair("File", ModelTypes::File),
    std::make_pair("Entity", ModelTypes::Entity),
    std::make_pair("Event", ModelTypes::Event),
    std::make_pair("MultiLanguageProperty", ModelTypes::MultiLanguageProperty),
    std::make_pair("Operation", ModelTypes::Operation),
    std::make_pair("OperationVariable", ModelTypes::OperationVariable),
    std::make_pair("Property", ModelTypes::Property),
    std::make_pair("Range", ModelTypes::Range),
    std::make_pair("ReferenceElement", ModelTypes::ReferenceElement),
    std::make_pair("RelationshipElement", ModelTypes::RelationshipElement),
    std::make_pair("SubmodelElement", ModelTypes::SubmodelElement),
    std::make_pair("SubmodelElementCollection", ModelTypes::SubmodelElementCollection),
    std::make_pair("View", ModelTypes::View),
    std::make_pair("GlobalReference", ModelTypes::GlobalReference),
    std::make_pair("FragmentReference", ModelTypes::FragmentReference),
    std::make_pair("Constraint", ModelTypes::Constraint),
    std::make_pair("Formula", ModelTypes::Formula),
    std::make_pair("Qualifier", ModelTypes::Qualifier),
};

ModelTypes ModelTypes_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * ModelTypes_::to_string(ModelTypes value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

