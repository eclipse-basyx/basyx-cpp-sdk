/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H

#include <string>

namespace basyx {
namespace aas {

enum class LevelType {
    Max,
    Min,
    Nom,
    Typ,
    Undefined,
};

class LevelType_
{
public:
    static LevelType from_string(const std::string & name);
    static const char * to_string(LevelType value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_LEVELTYPE_H */
