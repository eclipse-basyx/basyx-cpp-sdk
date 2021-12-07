/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_QUALIFIER_IHASSEMANTICS_H
#define BASYX_SUBMODEL_API_V2_QUALIFIER_IHASSEMANTICS_H

#include <BaSyx/aas/api_v2/reference/IReference.h>

#include <string>
#include <memory>

namespace basyx {
namespace aas {
namespace api {

class IHasSemantics
{
public:
	virtual ~IHasSemantics() = 0;

	virtual const IReference * getSemanticId() const = 0;
};

inline IHasSemantics::~IHasSemantics() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IHASSEMANTICS_H */
