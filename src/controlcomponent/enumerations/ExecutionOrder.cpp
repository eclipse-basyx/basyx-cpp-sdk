/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/controlcomponent/enumerations/ExecutionOrder.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::controlcomponent;

using enum_pair_t = std::pair<const char*, ExecutionOrder>;

static const std::array<enum_pair_t, 10> string_to_enum = 
{
    std::make_pair("start",  ExecutionOrder::start),
    std::make_pair("complete", ExecutionOrder::complete),
    std::make_pair("reset", ExecutionOrder::reset),
    std::make_pair("hold", ExecutionOrder::hold),
    std::make_pair("unhold", ExecutionOrder::unhold),
    std::make_pair("suspend", ExecutionOrder::suspend),
    std::make_pair("unsuspend", ExecutionOrder::unsuspend),
    std::make_pair("clear", ExecutionOrder::clear),
    std::make_pair("stop", ExecutionOrder::stop),
    std::make_pair("abort", ExecutionOrder::abort),
};

ExecutionOrder ExecutionOrder_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * ExecutionOrder_::to_string(ExecutionOrder value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

