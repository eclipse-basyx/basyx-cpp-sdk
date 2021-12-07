/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/operation/Operation.h>

using namespace basyx::aas::simple;
using namespace basyx::aas::api;

basyx::aas::simple::Operation::Operation(const std::string & idShort)
	: SubmodelElement(idShort)
	, invokable(basyx::object::make_null())
{
};

IElementContainer<IOperationVariable> & Operation::getInputVariables()
{
	return this->inputVariables;
}

IElementContainer<IOperationVariable> & Operation::getOutputVariables()
{
	return this->outputVariables;
}

IElementContainer<IOperationVariable> & Operation::getInOutputVariables()
{
	return this->inOutVariables;
}

basyx::object Operation::invoke(basyx::object args)
{
	return this->invokable;
}

void Operation::addInputVariable(std::unique_ptr<OperationVariable> operationVariable)
{
  this->inputVariables.addElement(std::move(operationVariable));
}

void Operation::addOutputVariable(std::unique_ptr<OperationVariable> operationVariable)
{
  this->outputVariables.addElement(std::move(operationVariable));
}

void Operation::addInOutVariable(std::unique_ptr<OperationVariable> operationVariable)
{
  this->inOutVariables.addElement(std::move(operationVariable));
}
