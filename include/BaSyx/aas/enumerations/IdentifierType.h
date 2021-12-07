/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIERTYPE_H
#define BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIERTYPE_H

#include <BaSyx/aas/enumerations/KeyType.h>

#include <string>

namespace basyx {
namespace aas {

using IdentifierType = KeyType;
using IdentifierType_ = KeyType_;

//enum class IdentifierType {
//    Custom,
//    IRDI,
//    URI,
//    Unknown,
//};
//
//class IdentifierType_
//{
//public:
//    static IdentifierType from_string(const std::string & name);
//    static const char * to_string(IdentifierType value);
//};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIERTYPE_H */
