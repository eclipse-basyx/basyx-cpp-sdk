/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENUM_ControlComponentConstants_H
#define BASYX_SUBMODEL_ENUM_ControlComponentConstants_H

#include <string>

namespace basyx {
namespace controlcomponent {

enum class ControlComponentConstants {
    status,
    orderList,
    LOCAL,
    operations,
    service,
    clear,
    stop,
    abort,
    unsuspend,
    suspend,
    unhold,
    hold,
    reset,
    start,
    simulation,
    manual,
    Auto,
    semiauto,
    priority,
    occupy,
    free,
    bstate,
    cmd,
    localOverwriteFree,
    localOverwrite,
    prevError,
    errorState,
    workState,
    opMode,
    exState,
    exMode,
    lastOccupier,
    occupier,
    occupationState,
};

class ControlComponentConstants_
{
public:
    static ControlComponentConstants from_string(const std::string & name);
    static const char * to_string(ControlComponentConstants value);
};


}
}

#endif
