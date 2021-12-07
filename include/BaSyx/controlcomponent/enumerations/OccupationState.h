/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_CONTROLCOMPONENT_ENUM_OCCUPATIONSTATE_H
#define BASYX_CONTROLCOMPONENT_ENUM_OCCUPATIONSTATE_H

namespace basyx {
namespace controlcomponent {

enum class OccupationState {
    free = 0,
    occupied = 1,
    priority = 2,
    local = 3
};

}
}

#endif
