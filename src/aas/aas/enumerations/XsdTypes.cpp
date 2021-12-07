/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/enumerations/XsdTypes.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::aas;

using enum_pair_t = std::pair<const char*, XsdTypes>;

static const std::array<enum_pair_t, 24> string_to_enum = 
{
    std::make_pair("NotSupported",  XsdTypes::xsd_NotSupported),
    std::make_pair("boolean", XsdTypes::xsd_boolean),
    std::make_pair("byte", XsdTypes::xsd_byte),
    std::make_pair("short", XsdTypes::xsd_short),
    std::make_pair("int", XsdTypes::xsd_int),
    std::make_pair("long", XsdTypes::xsd_long),
    std::make_pair("unsignedByte", XsdTypes::xsd_unsignedByte),
    std::make_pair("unsignedShort", XsdTypes::xsd_unsignedShort),
    std::make_pair("unsignedInt", XsdTypes::xsd_unsignedInt),
    std::make_pair("unsignedLong", XsdTypes::xsd_unsignedLong),
    std::make_pair("double", XsdTypes::xsd_double),
    std::make_pair("float", XsdTypes::xsd_float),
    std::make_pair("string", XsdTypes::xsd_string),
    std::make_pair("anyuri", XsdTypes::xsd_anyuri),
    std::make_pair("date", XsdTypes::xsd_date),
    std::make_pair("dateTime", XsdTypes::xsd_dateTime),
    std::make_pair("dayTimeDuration", XsdTypes::xsd_dayTimeDuration),
    std::make_pair("yearMonthDuration", XsdTypes::xsd_yearMonthDuration),
    std::make_pair("time", XsdTypes::xsd_time),
    std::make_pair("gYearMonth", XsdTypes::xsd_gYearMonth),
    std::make_pair("gYear", XsdTypes::xsd_gYear),
    std::make_pair("gMonthDay", XsdTypes::xsd_gMonthDay),
    std::make_pair("gDay", XsdTypes::xsd_gDay),
    std::make_pair("gMonth", XsdTypes::xsd_gMonth),
};

XsdTypes XsdTypes_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * XsdTypes_::to_string(XsdTypes value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

