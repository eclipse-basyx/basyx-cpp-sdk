/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_CONSTRAINT_ICONSTRAINT_H
#define BASYX_SUBMODEL_API_V2_CONSTRAINT_ICONSTRAINT_H

#include <BaSyx/aas/api_v2/common/IModelType.h>

namespace basyx {
namespace aas {
namespace api {


class IConstraint
{
public:
	virtual ~IConstraint() = 0;
};

inline IConstraint::~IConstraint() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_CONSTRAINT_ICONSTRAINT_H */
