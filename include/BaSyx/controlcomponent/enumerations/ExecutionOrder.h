/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_CONTROLCOMPONENT_ENUM_EXECUTIONORDER_H
#define BASYX_CONTROLCOMPONENT_ENUM_EXECUTIONORDER_H

#include <string>

namespace basyx {
namespace controlcomponent {

enum class ExecutionOrder {
    start,
    complete,
    reset,
    hold,
    unhold,
    suspend,
    unsuspend,
    clear,
    stop,
    abort,
};

class ExecutionOrder_
{
public:
    static ExecutionOrder from_string(const std::string & name);
    static const char * to_string(ExecutionOrder value);
};


}
}

#endif
