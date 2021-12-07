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

#include <BaSyx/aas/map_v2/constraint/Qualifier.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class QualifierTest : public ::testing::Test {
};

TEST_F(QualifierTest, TestObjectConstructor)
{
  auto object = ModelType<ModelTypes::Qualifier>().getMap();
  object.insertKey(Qualifier::Path::QualifierType, "Qualifier type");
  object.insertKey(Qualifier::Path::ValueType, "Value type");
  object.insertKey(Qualifier::Path::ValueDataType, "Value data type");
  object.insertKey(Qualifier::Path::ValueId, TestingObjects::map::testingReference_1().getMap());
  object.insertKey(Qualifier::Path::SemanticId, TestingObjects::map::testingReference_2().getMap());

  Qualifier qualifier{object};

  ASSERT_EQ("Qualifier type", qualifier.getQualifierType());
  ASSERT_EQ("Value type", qualifier.getValueType());
  ASSERT_EQ("Value data type", *qualifier.getValueDataType());
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *qualifier.getValueId());
  ASSERT_EQ(TestingObjects::map::testingReference_2(), *qualifier.getSemanticId());
}

TEST_F(QualifierTest, TestObjectCopy)
{
  Qualifier qualifier
  {
    "Qualifier type",
    "Value type",
    "Value data type",
    TestingObjects::map::testingReference_1()
  };
  qualifier.setSemanticId(util::make_unique<Reference>(TestingObjects::map::testingReference_2()));

  auto map = qualifier.getMap();
  Qualifier copied{map};

  ASSERT_EQ("Qualifier type", qualifier.getQualifierType());
  ASSERT_EQ("Value type", qualifier.getValueType());
  ASSERT_EQ("Value data type", *qualifier.getValueDataType());
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *qualifier.getValueId());
  ASSERT_EQ(TestingObjects::map::testingReference_2(), *qualifier.getSemanticId());
}