/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/operation/Operation.h>

using namespace basyx::aas::map;
using namespace basyx::aas::api;

constexpr char Operation::Path::Invokable[];
constexpr char Operation::Path::InputVariable[];
constexpr char Operation::Path::OutputVariable[];
constexpr char Operation::Path::InoutputVariable[];

Operation::Operation(const std::string & idShort, basyx::object invokable)
	: SubmodelElement(idShort)
	, invokable(basyx::object::make_null())
{
	this->invokable = invokable;
	this->map.insertKey(Path::Invokable, this->invokable);
	this->map.insertKey(Path::InputVariable, inputVariables.getMap());
	this->map.insertKey(Path::OutputVariable, outputVariables.getMap());
	this->map.insertKey(Path::InoutputVariable, inOutVariables.getMap());
}

Operation::Operation(basyx::object obj)
	: SubmodelElement(obj)
{
	this->map.insertKey(Path::Invokable, obj.getProperty(Path::Invokable));

	if ( not obj.getProperty(Path::InputVariable).IsNull() )
	{
		for (auto ov : obj.getProperty(Path::InputVariable).Get<object::object_map_t>())
		{
		  auto elem = util::make_unique<OperationVariable>(ov.second);
			this->inputVariables.addElement(std::move(elem));
		}
	}

	if ( not obj.getProperty(Path::OutputVariable).IsNull() )
	{
		for (auto ov : obj.getProperty(Path::OutputVariable).Get<object::object_map_t>())
		{
			this->outputVariables.addElement(util::make_unique<OperationVariable>(ov.second));
		}
	}

	if ( not obj.getProperty(Path::InoutputVariable).IsNull() )
	{
		for (auto ov : obj.getProperty(Path::InoutputVariable).Get<object::object_map_t>())
		{
			this->inOutVariables.addElement(util::make_unique<OperationVariable>(ov.second));
		}
	}

	this->map.insertKey(Path::InputVariable, inputVariables.getMap());
	this->map.insertKey(Path::OutputVariable, outputVariables.getMap());
	this->map.insertKey(Path::InoutputVariable, inOutVariables.getMap());
}

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
	return this->invokable.invoke(args);
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
