/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_REFERENCE_IKEY_H
#define BASYX_SUBMODEL_API_V2_REFERENCE_IKEY_H

#include <string>

#include <BaSyx/aas/enumerations/KeyType.h>
#include <BaSyx/aas/enumerations/KeyElements.h>

namespace basyx {
namespace aas {
namespace api {

class IKey
{
public:
  struct Path
  {
    static constexpr char Type[] = "type";
    static constexpr char Local[] = "local";
    static constexpr char Value[] = "value";
    static constexpr char IdType[] = "idType";
  };
public:
	virtual ~IKey() = 0;

	virtual KeyElements getType() const = 0;
	virtual bool isLocal() const = 0;
	virtual std::string getValue() const = 0;
	virtual KeyType getIdType() const = 0;
};

inline IKey::~IKey() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_REFERENCE_IKEY_H */
