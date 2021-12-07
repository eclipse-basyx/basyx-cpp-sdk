/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/controlcomponent/enumerations/ControlComponentConstants.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::controlcomponent;

using enum_pair_t = std::pair<const char*, ControlComponentConstants>;

static const std::array<enum_pair_t, 34> string_to_enum = 
{
    std::make_pair("status",  ControlComponentConstants::status),
    std::make_pair("orderList", ControlComponentConstants::orderList),
    std::make_pair("LOCAL", ControlComponentConstants::LOCAL),
    std::make_pair("operations", ControlComponentConstants::operations),
    std::make_pair("service", ControlComponentConstants::service),
    std::make_pair("clear", ControlComponentConstants::clear),
    std::make_pair("stop", ControlComponentConstants::stop),
    std::make_pair("abort", ControlComponentConstants::abort),
    std::make_pair("unsuspend", ControlComponentConstants::unsuspend),
    std::make_pair("suspend", ControlComponentConstants::suspend),
    std::make_pair("unhold", ControlComponentConstants::unhold),
    std::make_pair("hold", ControlComponentConstants::hold),
    std::make_pair("reset", ControlComponentConstants::reset),
    std::make_pair("start", ControlComponentConstants::start),
    std::make_pair("simulation", ControlComponentConstants::simulation),
    std::make_pair("manual", ControlComponentConstants::manual),
    std::make_pair("auto", ControlComponentConstants::Auto),
    std::make_pair("semiauto", ControlComponentConstants::semiauto),
    std::make_pair("priority", ControlComponentConstants::priority),
    std::make_pair("occupy", ControlComponentConstants::occupy),
    std::make_pair("free", ControlComponentConstants::free),
    std::make_pair("bstate", ControlComponentConstants::bstate),
    std::make_pair("cmd", ControlComponentConstants::cmd),
    std::make_pair("localOverwriteFree", ControlComponentConstants::localOverwriteFree),
    std::make_pair("localOverwrite", ControlComponentConstants::localOverwrite),
    std::make_pair("prevError", ControlComponentConstants::prevError),
    std::make_pair("errorState", ControlComponentConstants::errorState),
    std::make_pair("workState", ControlComponentConstants::workState),
    std::make_pair("opMode", ControlComponentConstants::opMode),
    std::make_pair("exState", ControlComponentConstants::exState),
    std::make_pair("exMode", ControlComponentConstants::exMode),
    std::make_pair("lastOccupier", ControlComponentConstants::lastOccupier),
    std::make_pair("occupier", ControlComponentConstants::occupier),
    std::make_pair("occupationState", ControlComponentConstants::occupationState),
};

ControlComponentConstants ControlComponentConstants_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * ControlComponentConstants_::to_string(ControlComponentConstants value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

