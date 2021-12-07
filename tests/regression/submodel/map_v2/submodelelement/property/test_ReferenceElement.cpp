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

#include <BaSyx/aas/map_v2/submodelelement/property/ReferenceElement.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class ReferenceElementTest : public ::testing::Test {};

TEST_F(ReferenceElementTest, TestObjectConstructor)
{
  // compose parent classes
  object object = TestingObjects::object::testingSubmodelElement();
  object.insertKey(ReferenceElement::Path::Value, TestingObjects::map::testingReference_1().getMap());
  object.insertKey(ReferenceElement::Path::Kind, ModelingKind_::to_string(ModelingKind::Template));

  // build from object
  ReferenceElement referenceElement{object};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(referenceElement));
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *referenceElement.getValue());
}

TEST_F(ReferenceElementTest, TestObjectCopy)
{
  ReferenceElement referenceElement{std::string{"test id"}};

  referenceElement.setValue(TestingObjects::map::testingReference_1());

  auto map = referenceElement.getMap();
  ReferenceElement copied{map};

  ASSERT_EQ(TestingObjects::map::testingReference_1(), *copied.getValue());
}