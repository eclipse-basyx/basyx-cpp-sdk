/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_OPERATION_OPERATIONVARIABLE_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_OPERATION_OPERATIONVARIABLE_H

#include <BaSyx/aas/api_v2/submodelelement/operation/IOperationVariable.h>
#include <BaSyx/aas/simple/submodelelement/SubmodelElement.h>

namespace basyx {
namespace aas {
namespace simple {

class OperationVariable : 
	public virtual SubmodelElement, 
	public virtual api::IOperationVariable
{
private:
	std::unique_ptr<ISubmodelElement> value;
public:
	OperationVariable(const std::string & idShort)
	  : SubmodelElement(idShort, ModelingKind::Template)
	{}

	OperationVariable(const std::string & idShort, std::unique_ptr<ISubmodelElement> value)
		: SubmodelElement(idShort, ModelingKind::Template)
		, value(std::move(value))
	{}

	OperationVariable(const OperationVariable & other) = default;
	OperationVariable(OperationVariable && other) noexcept = default;

	OperationVariable & operator=(const OperationVariable & other) = default;
	OperationVariable & operator=(OperationVariable && other) noexcept = default;

	~OperationVariable() = default;
public:
	// Inherited via IOperationVariable
	virtual ISubmodelElement & getValue() const
	{
		return *this->value;
	};
};


}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_OPERATION_OPERATIONVARIABLE_H */
