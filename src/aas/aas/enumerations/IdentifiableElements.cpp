/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/enumerations/IdentifiableElements.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::aas;

using enum_pair_t = std::pair<const char*, IdentifiableElements>;

static const std::array<enum_pair_t, 4> string_to_enum = 
{
    std::make_pair("Asset",  IdentifiableElements::Asset),
    std::make_pair("AssetAdministrationShell", IdentifiableElements::AssetAdministrationShell),
    std::make_pair("ConceptDescription", IdentifiableElements::ConceptDescription),
    std::make_pair("Submodel", IdentifiableElements::Submodel),
};

IdentifiableElements IdentifiableElements_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * IdentifiableElements_::to_string(IdentifiableElements value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

