/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_CONTROLCOMPONENT_ENUM_EXECUTIONMODE_H
#define BASYX_CONTROLCOMPONENT_ENUM_EXECUTIONMODE_H

#include <string>

namespace basyx {
namespace controlcomponent {

enum class ExecutionMode {
    Auto = 1,
    Semiauto = 2,
    Manual = 3,
    Reserved = 4,
    Simulation = 5
};

}
}

#endif
