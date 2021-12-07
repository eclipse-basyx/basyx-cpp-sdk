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

#include <BaSyx/aas/api_v2/dataspecification/IValueList.h>
#include <BaSyx/aas/simple/dataspecification/ValueList.h>
#include <BaSyx/aas/map_v2/dataspecification/ValueList.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
    simple::ValueList,
    map::ValueList
>;

template<class Impl>
class ValueListTest :public ::testing::Test {
protected:
  using impl_t = Impl;
protected:
  std::unique_ptr<api::IValueList> valueList;
protected:
  void SetUp() override
  {
    this->valueList = util::make_unique<Impl>();
  }

  void TearDown() override
  {
  }
};

TYPED_TEST_CASE(ValueListTest, ImplTypes);

TYPED_TEST(ValueListTest, TestConstructor)
{
  auto list = this->valueList->getValueReferencePairs();
  ASSERT_EQ(list.size(), 0);
}

TYPED_TEST(ValueListTest, TestAddSingleValueRefPair)
{
  simple::ValueReferencePair referencePair("pair", simple::Reference());

  this->valueList->addValueReferencePair(referencePair);

  auto list = this->valueList->getValueReferencePairs();

  ASSERT_EQ(list.size(), 1);
  ASSERT_EQ(list[0].getValue(), referencePair.getValue());
}

TYPED_TEST(ValueListTest, TestAddMultipleValueRefPair)
{
  simple::ValueReferencePair referencePair0("pair0", simple::Reference());
  simple::ValueReferencePair referencePair1("pair1", simple::Reference());
  simple::ValueReferencePair referencePair2("pair2", simple::Reference());

  this->valueList->addValueReferencePair(referencePair0);
  this->valueList->addValueReferencePair(referencePair1);
  this->valueList->addValueReferencePair(referencePair2);

  auto list = this->valueList->getValueReferencePairs();

  ASSERT_EQ(list.size(), 3);
  ASSERT_EQ(list[0].getValue(), referencePair0.getValue());
  ASSERT_EQ(list[1].getValue(), referencePair1.getValue());
  ASSERT_EQ(list[2].getValue(), referencePair2.getValue());
}

