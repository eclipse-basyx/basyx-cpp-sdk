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
 * test_Referable.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/Referable.h"
#include "BaSyx/submodel/map/reference/Reference.h"
#include "support/AdditionalAssertions.hpp"
#include "support/ReferableMock.hpp"

using namespace basyx::submodel;
using namespace basyx::testing;

class ReferableTest : public ::testing::Test
{
protected:
  Referable referable;
  void SetUp() override
  {}

  void TearDown() override
  {
    auto map = referable.getMap();
    basyx::assertions::AssertMapContains(map, IReferable::Path::Category);
    basyx::assertions::AssertMapContains(map, IReferable::Path::Description);
    basyx::assertions::AssertMapContains(map, IReferable::Path::Parent);
    basyx::assertions::AssertMapContains(map, IReferable::Path::IdShort);
  }
};

TEST_F(ReferableTest, TestSimpleConstruction)
{}

TEST_F(ReferableTest, TestConstructionFromObject)
{
  basyx::object obj = basyx::object::make_map();
  obj.insertKey("test", "test");

  referable = Referable{obj};

  // test should be contained in map
  auto map = referable.getMap();
  basyx::assertions::AssertMapContainsValue<std::string>(map, "test", "test");
}

TEST_F(ReferableTest, TestLongConstructor)
{
  Description desc = testingDescription();
  referable = Referable{ReferableMock::Path::id, ReferableMock::Path::category, desc};

  // test should be contained in map
  auto map = referable.getMap();

  assertTestingReferable(map);
}

TEST_F(ReferableTest, TestConstructFromOtherPtr)
{
  auto ref_mock = std::make_shared<ReferableMock>();
  
  referable = Referable(*ref_mock);

  // test should be contained in map
  auto map = referable.getMap();

  assertTestingReferable(map);
}

TEST_F(ReferableTest, TestConstructFromOther)
{
  ReferableMock ref_mock;

  referable = Referable(ref_mock);

  // test should be contained in map
  auto map = referable.getMap();

  assertTestingReferable(map);
}

TEST_F(ReferableTest, TestGetIdShort)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);

  auto id = referable.getIdShort();
  ASSERT_EQ(id, ReferableMock::Path::id);
}

TEST_F(ReferableTest, TestGetCategory)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);

  auto cateogry = referable.getCategory();
  ASSERT_EQ(cateogry, ReferableMock::Path::category);
}

TEST_F(ReferableTest, TestGetDescription)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);

  auto description = referable.getDescription();
  ASSERT_EQ(description, testingDescription());
}

TEST_F(ReferableTest, TestGetParent)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);

  auto parent = referable.getParent();
  basyx::testing::assertContainsKeyMock(parent);
}

TEST_F(ReferableTest, TestSetIdShort)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);

  referable.setIdShort(ReferableMock::Path::id + std::string("test"));

  auto map = referable.getMap();
  ASSERT_EQ(ReferableMock::Path::id + std::string("test"), map.getProperty(IReferable::Path::IdShort).GetStringContent());
}

TEST_F(ReferableTest, TestSetCategory)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);

  referable.setCategory(ReferableMock::Path::category + std::string("test"));

  auto map = referable.getMap();
  ASSERT_EQ(ReferableMock::Path::category + std::string("test"), map.getProperty(IReferable::Path::Category).GetStringContent());
}

TEST_F(ReferableTest, TestSetDescription)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);
  auto desc = Description(ReferableMock::Path::description_lang + std::string("test"), ReferableMock::Path::description_text + std::string("test"));

  referable.setDescription(desc);

  auto map = referable.getMap();
  ASSERT_EQ(desc, Description(map.getProperty(IReferable::Path::Description)));
}

TEST_F(ReferableTest, TestSetParent)
{
  ReferableMock ref_mock;
  referable = Referable(ref_mock);
  Reference ref; 

  referable.setParent(ref);

  auto map = referable.getMap();
  auto parent_obj = map.getProperty(IReferable::Path::Parent);
  ASSERT_FALSE(basyx::testing::referenceObjectContainsKeyMock(parent_obj));
}
