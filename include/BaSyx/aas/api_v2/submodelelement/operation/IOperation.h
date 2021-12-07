/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_OPERATION_IOPERATION_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_OPERATION_IOPERATION_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/api_v2/submodelelement/operation/IOperationVariable.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>

#include <BaSyx/shared/object.h>

#include <memory>
#include <vector>

namespace basyx {
namespace aas {
namespace api {

class IOperation : public virtual ISubmodelElement
{
public:
	virtual ~IOperation() = 0;

	virtual IElementContainer<IOperationVariable> & getInputVariables() = 0;
	virtual IElementContainer<IOperationVariable> & getOutputVariables() = 0;
	virtual IElementContainer<IOperationVariable> & getInOutputVariables() = 0;

	virtual basyx::object invoke(basyx::object args) = 0;
};

inline IOperation::~IOperation() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_OPERATION_IOPERATION_H */
