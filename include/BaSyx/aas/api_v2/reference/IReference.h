/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_REFERENCE_IREFERENCE_H
#define BASYX_SUBMODEL_API_V2_REFERENCE_IREFERENCE_H

#include <BaSyx/aas/simple/reference/Key.h>

#include <vector>

namespace basyx {
namespace aas {
namespace api {


class IReference
{
public:
	virtual ~IReference() = 0;

	virtual std::vector<simple::Key> getKeys() const = 0;
	virtual void addKey(const simple::Key & key) = 0;

	virtual bool empty() const = 0;
};

inline IReference::~IReference() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_REFERENCE_IREFERENCE_H */
