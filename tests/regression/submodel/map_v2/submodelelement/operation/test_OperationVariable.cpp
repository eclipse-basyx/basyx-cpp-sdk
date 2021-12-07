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

#include <BaSyx/aas/map_v2/submodelelement/operation/OperationVariable.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class OperationVariableTest : public ::testing::Test {};

TEST_F(OperationVariableTest, TestObjectConstructor)
{
  auto object = TestingObjects::object::testingSubmodelElement();
  object.insertKey(OperationVariable::Path::Value, TestingObjects::map::testingFile().getMap());

  // build from object
  OperationVariable ov{object};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(ov));
  ASSERT_TRUE(TestingObjects::map::testingFile(ov.getValue()));
}

TEST_F(OperationVariableTest, TestCopiedObject)
{
  OperationVariable ov {"test id", util::make_unique<File>(TestingObjects::map::testingFile())};

  OperationVariable copied {ov.getMap()};

  ASSERT_EQ(copied.getIdShort(), "test id");

  ASSERT_TRUE(TestingObjects::map::testingFile(copied.getValue()));
}

TEST_F(OperationVariableTest, TestSubmodelElementFactory)
{
  auto object = TestingObjects::object::testingSubmodelElement();
  object.insertKey(OperationVariable::Path::Value, TestingObjects::map::testingFile().getMap());

  object.insert(ModelType<ModelTypes::OperationVariable>().getMap());

  // build from object
  auto se = SubmodelElementFactory::Create(object);
  OperationVariable & ov = dynamic_cast<OperationVariable&>(*se);

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(ov));
  ASSERT_TRUE(TestingObjects::map::testingFile(ov.getValue()));
}