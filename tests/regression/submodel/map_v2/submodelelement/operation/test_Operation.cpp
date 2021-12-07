/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <gtest/gtest.h>

#include <BaSyx/aas/map_v2/submodelelement/operation/Operation.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class OperationTest : public ::testing::Test {};

TEST_F(OperationTest, TestObjectConstructorEmpty)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Operation operation{object};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(operation));
  ASSERT_EQ(operation.getInputVariables().size(), 0);
  ASSERT_EQ(operation.getOutputVariables().size(), 0);
  ASSERT_EQ(operation.getInOutputVariables().size(), 0);
}

TEST_F(OperationTest, TestObjectConstructor)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  ElementContainer<OperationVariable> inputVariables;
  inputVariables.addElement(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable()));
  object.insertKey(Operation::Path::InputVariable, inputVariables.getMap());

  ElementContainer<OperationVariable> outputVariables;
  outputVariables.addElement(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(3)));
  object.insertKey(Operation::Path::OutputVariable, outputVariables.getMap());

  ElementContainer<OperationVariable> inOutVariables;
  inOutVariables.addElement(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(9)));
  object.insertKey(Operation::Path::InoutputVariable, inOutVariables.getMap());

  // build from object
  Operation operation{object};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(operation));

  auto & ins = operation.getInputVariables();
  ASSERT_EQ(ins.size(), 1);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*ins.getElement(0)));

  auto & outs = operation.getOutputVariables();
  ASSERT_EQ(outs.size(), 1);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*outs.getElement(0), 3));

  auto & inouts = operation.getInOutputVariables();
  ASSERT_EQ(inouts.size(), 1);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*inouts.getElement(0), 9));
}

TEST_F(OperationTest, TestCopiedObject)
{
  Operation operation {"test id", object::make_null() };
  operation.addInputVariable(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(1)));
  operation.addInputVariable(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(2)));
  operation.addOutputVariable(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(3)));
  operation.addOutputVariable(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(4)));
  operation.addInOutVariable(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(5)));
  operation.addInOutVariable(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable(6)));


  Operation copied {operation.getMap() };

  ASSERT_EQ(copied.getIdShort(), "test id");

  auto & ins = copied.getInputVariables();
  ASSERT_EQ(ins.size(), 2);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*ins.getElement(0), 1));
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*ins.getElement(1), 2));

  auto & outs = copied.getOutputVariables();
  ASSERT_EQ(outs.size(), 2);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*outs.getElement(0), 3));
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*outs.getElement(1), 4));

  auto & inouts = copied.getInOutputVariables();
  ASSERT_EQ(inouts.size(), 2);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*inouts.getElement(0), 5));
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*inouts.getElement(1), 6));
}

TEST_F(OperationTest, TestSubmodelElementFactory)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  ElementContainer<OperationVariable> inputVariables;
  inputVariables.addElement(util::make_unique<OperationVariable>(TestingObjects::map::testingOperationVariable()));
  object.insertKey(Operation::Path::InputVariable, inputVariables.getMap());

  object.insert(ModelType<ModelTypes::Operation>().getMap());

  // build from object
  auto se = SubmodelElementFactory::Create(object);
  Operation & operation = dynamic_cast<Operation&>(*se);

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(operation));

  auto & ins = operation.getInputVariables();
  ASSERT_EQ(ins.size(), 1);
  ASSERT_TRUE(TestingObjects::map::testingOperationVariable(*ins.getElement(0)));
}