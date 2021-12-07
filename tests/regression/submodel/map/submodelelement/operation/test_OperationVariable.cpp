/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
* test_OperationVariable.cpp
*
*      Author: wendel
*/

#include <gtest/gtest.h>

#include <BaSyx/submodel/map/submodelelement/operation/OperationVariable.h>
#include <BaSyx/submodel/map/submodelelement/property/Property.h>

#include "support/AdditionalAssertions.hpp"
#include "support/ReferableMock.hpp"
#include "support/ReferenceMock.hpp"


using namespace basyx::submodel;

class OperationVariableTest : public ::testing::Test
{
protected:
	OperationVariable op_var;

	void SetUp() override
	{}

	void TearDown() override
	{
	}
};

TEST_F(OperationVariableTest, TestConstructor)
{
}

TEST_F(OperationVariableTest, TestConstructionFromObject)
{
	ModelType modelType;
	auto obj = modelType.getMap();
	obj.insertKey(ModelType::Path::Name, IOperationVariable::Path::ModelType, true);
	obj.insertKey("testPath", "testKey");

	op_var = OperationVariable(obj);

	auto map = op_var.getMap();
	basyx::assertions::AssertMapContainsValue<std::string>(map, "testPath", "testKey");
}

TEST_F(OperationVariableTest, TestGetType)
{
	ModelType modelType;
	auto obj = modelType.getMap();
	obj.insertKey(ModelType::Path::Name, IOperationVariable::Path::ModelType, true);
	obj.insertKey(IOperationVariable::Path::Type, "testingType");

	op_var = OperationVariable(obj);

	auto type = op_var.getType();

	ASSERT_EQ(type, "testingType");
}

TEST_F(OperationVariableTest, TestSetType)
{
	op_var.setType("testingType");

	auto map = op_var.getMap();

	basyx::assertions::AssertMapContainsValue<std::string>(map, IOperationVariable::Path::Type, "testingType");
}

TEST_F(OperationVariableTest, TestGetSetValue)
{
	Property<int> prop;
	prop.setValue(5);

	op_var.setValue(prop);
	auto submodelElement = op_var.getValue();
	auto elem = std::dynamic_pointer_cast<SubmodelElement>(submodelElement);
	Property<int> prop2(elem->getMap());

	ASSERT_EQ(prop2.getValue(), 5);

	return;
}