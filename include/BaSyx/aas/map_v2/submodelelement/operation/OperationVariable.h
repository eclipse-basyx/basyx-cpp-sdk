/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_OPERATION_OPERATIONVARIABLE_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_OPERATION_OPERATIONVARIABLE_H

#include <BaSyx/aas/api_v2/submodelelement/operation/IOperationVariable.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>

namespace basyx {
namespace aas {
namespace map {

class OperationVariable : 
	public SubmodelElement, 
	public api::IOperationVariable,
	public ModelType<ModelTypes::OperationVariable>
{
public:
  struct Path {
    static constexpr const char Value[] = "value";
  };

private:
	std::unique_ptr<SubmodelElement> value;

public:
	OperationVariable(const std::string & idShort, std::unique_ptr<SubmodelElement> value);
	OperationVariable(basyx::object obj);

	OperationVariable(const OperationVariable & other);
	OperationVariable(OperationVariable && other) noexcept;

	OperationVariable & operator=(const OperationVariable & other) = default;
	OperationVariable & operator=(OperationVariable && other) noexcept = default;

	~OperationVariable() = default;

	// Inherited via IOperationVariable
	virtual SubmodelElement & getValue() const;

	virtual inline KeyElements getKeyElementType() const override { return KeyElements::OperationVariable; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_OPERATION_OPERATIONVARIABLE_H */
