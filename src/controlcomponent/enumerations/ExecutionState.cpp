/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/controlcomponent/enumerations/ExecutionState.h>

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::controlcomponent;

using enum_pair_t = std::pair<const char*, ExecutionState>;

static const std::array<enum_pair_t, 17> string_to_enum = 
{
    std::make_pair("idle",  ExecutionState::idle),
    std::make_pair("starting", ExecutionState::starting),
    std::make_pair("execute", ExecutionState::execute),
    std::make_pair("completing", ExecutionState::completing),
    std::make_pair("complete", ExecutionState::complete),
    std::make_pair("resetting", ExecutionState::resetting),
    std::make_pair("holding", ExecutionState::holding),
    std::make_pair("held", ExecutionState::held),
    std::make_pair("unholding", ExecutionState::unholding),
    std::make_pair("suspending", ExecutionState::suspending),
    std::make_pair("suspended", ExecutionState::suspended),
    std::make_pair("unsuspending", ExecutionState::unsuspending),
    std::make_pair("stopping", ExecutionState::stopping),
    std::make_pair("stopped", ExecutionState::stopped),
    std::make_pair("aborting", ExecutionState::aborting),
    std::make_pair("aborted", ExecutionState::aborted),
    std::make_pair("clearing", ExecutionState::clearing),
};

ExecutionState ExecutionState_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * ExecutionState_::to_string(ExecutionState value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

