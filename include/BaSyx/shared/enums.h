/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_ENUMS_H
#define BASYX_SHARED_ENUMS_H

namespace basyx {

enum class EntityType : char {
    CoManagedEntity = 0,
    SelfManagedEntity = 1,
};

enum class Category : char {
    Constant = 0,
    Parameter = 1,
    Variable = 2,
};

};

#endif /* BASYX_SHARED_ENUMS_H */
