/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/enumerations/DataTypeIEC61360.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::aas;

using enum_pair_t = std::pair<const char*, DataTypeIEC61360>;

static const std::array<enum_pair_t, 13> string_to_enum = 
{
    std::make_pair("Boolean",  DataTypeIEC61360::Boolean),
    std::make_pair("Date", DataTypeIEC61360::Date),
    std::make_pair("Rational", DataTypeIEC61360::Rational),
    std::make_pair("Rational_Measure", DataTypeIEC61360::Rational_Measure),
    std::make_pair("Real_Count", DataTypeIEC61360::Real_Count),
    std::make_pair("Real_Currency", DataTypeIEC61360::Real_Currency),
    std::make_pair("Real_Measure", DataTypeIEC61360::Real_Measure),
    std::make_pair("String", DataTypeIEC61360::String),
    std::make_pair("String_Translatable", DataTypeIEC61360::String_Translatable),
    std::make_pair("Time", DataTypeIEC61360::Time),
    std::make_pair("Timestamp", DataTypeIEC61360::Timestamp),
    std::make_pair("Url", DataTypeIEC61360::Url),
    std::make_pair("Undefined", DataTypeIEC61360::Undefined),
};

DataTypeIEC61360 DataTypeIEC61360_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * DataTypeIEC61360_::to_string(DataTypeIEC61360 value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

