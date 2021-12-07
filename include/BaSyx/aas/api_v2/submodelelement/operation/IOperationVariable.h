/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_OPERATION_IOPERATIONVARIABLE_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_OPERATION_IOPERATIONVARIABLE_H


#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>

#include <memory>

namespace basyx {
namespace aas {
namespace api {

class IOperationVariable : public virtual ISubmodelElement
{
public:
	virtual ~IOperationVariable() = 0;

	virtual ISubmodelElement & getValue() const = 0;

	virtual KeyElements getKeyElementType() const override { return KeyElements::OperationVariable; };
};

inline IOperationVariable::~IOperationVariable() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_OPERATION_IOPERATIONVARIABLE_H */

