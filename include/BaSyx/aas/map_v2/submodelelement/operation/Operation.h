/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_OPERATION_OPERATION_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_OPERATION_OPERATION_H

#include <BaSyx/aas/api_v2/submodelelement/operation/IOperation.h>
#include <BaSyx/aas/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>

namespace basyx {
namespace aas {
namespace map {

class Operation : 
	public api::IOperation,
	public SubmodelElement,
	public ModelType<ModelTypes::Operation>
{
public:
  struct Path {
    static constexpr char Invokable[] = "invokable";
    static constexpr char InputVariable[] = "inputVariable";
    static constexpr char OutputVariable[] = "outputVariable";
    static constexpr char InoutputVariable[] = "inoutputVariable";
  };
private:
	ElementContainer<api::IOperationVariable> inputVariables;
	ElementContainer<api::IOperationVariable> outputVariables;
	ElementContainer<api::IOperationVariable> inOutVariables;
	basyx::object invokable;
public:
	Operation(const std::string & idShort, basyx::object invokable);
  Operation(basyx::object obj);
	
	~Operation() = default;

	// Inherited via IOperation
	virtual api::IElementContainer<api::IOperationVariable> & getInputVariables() override;
	virtual api::IElementContainer<api::IOperationVariable> & getOutputVariables() override;
	virtual api::IElementContainer<api::IOperationVariable> & getInOutputVariables() override;
	virtual basyx::object invoke(basyx::object args) override;

  void addInputVariable(std::unique_ptr<OperationVariable> operationVariable);
  void addOutputVariable(std::unique_ptr<OperationVariable> operationVariable);
  void addInOutVariable(std::unique_ptr<OperationVariable> operationVariable);

	virtual KeyElements getKeyElementType() const override { return KeyElements::Operation; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_OPERATION_OPERATION_H */
