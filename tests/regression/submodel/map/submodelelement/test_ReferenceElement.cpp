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
 * test_ReferenceElement.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/submodelelement/ReferenceElement.h"
#include "BaSyx/submodel/map/reference/Reference.h"
#include "support/AdditionalAssertions.hpp"
#include "support/ReferenceMock.hpp"

using namespace basyx::submodel;

class ReferenceElementTest : public ::testing::Test
{
protected:
  ReferenceElement ref_elem;

  void SetUp() override
  {}

  void TearDown() override
  {
  }
};

TEST_F(ReferenceElementTest, TestSimpleConstructor)
{}

TEST_F(ReferenceElementTest, TestConstructFromObject)
{
  auto obj = ModelType(IReferenceElement::Path::Modeltype).getMap();
  obj.insertKey("testKey", "testValue");

  ref_elem = ReferenceElement(obj);

  auto map = ref_elem.getMap();
  basyx::assertions::AssertMapContainsValue<std::string>(map, "testKey", "testValue");
}

TEST_F(ReferenceElementTest, TestConstructWithReference)
{
  std::shared_ptr<IReference> ref = std::make_shared<basyx::testing::ReferenceMock>();

  ref_elem = ReferenceElement(*ref);

  auto ref_obj = ref_elem.getMap().getProperty(IProperty::Path::Value);
  basyx::testing::assertTestingReference(ref_obj);
}

TEST_F(ReferenceElementTest, TestSetValue)
{
  std::shared_ptr<IReference> ref = std::make_shared<basyx::testing::ReferenceMock>();

  ref_elem.setValue(*ref);

  auto ref_obj = ref_elem.getMap().getProperty(IProperty::Path::Value);
  basyx::testing::assertTestingReference(ref_obj);
}

TEST_F(ReferenceElementTest, TestGetValue)
{
  auto obj = ModelType(IReferenceElement::Path::Modeltype).getMap();

  basyx::testing::ReferenceMock ref;
  obj.insertKey(IProperty::Path::Value, ref.getMap());

  ref_elem = ReferenceElement(obj);

  std::shared_ptr<IReference> val = ref_elem.getValue();
  basyx::testing::assertTestingReference(*val);
}

