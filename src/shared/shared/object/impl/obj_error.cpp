/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/shared/object/obj_error.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::detail;

using enum_pair_t = std::pair<const char*, error>;

static const std::array<enum_pair_t, 7> string_to_enum = 
{
    std::make_pair("None",  error::None),
    std::make_pair("PropertyNotFound", error::PropertyNotFound),
    std::make_pair("IndexOutOfBounds", error::IndexOutOfBounds),
    std::make_pair("NotInvokable", error::NotInvokable),
    std::make_pair("ObjectAlreadyExists", error::ObjectAlreadyExists),
    std::make_pair("MalformedRequest", error::MalformedRequest),
    std::make_pair("ProviderException", error::ProviderException),
};

error error_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * error_::to_string(error value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

