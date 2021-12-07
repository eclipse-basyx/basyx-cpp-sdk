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

#include <BaSyx/aas/api_v2/submodelelement/IRange.h>
#include <BaSyx/aas/simple/submodelelement/Range.h>
#include <BaSyx/aas/map_v2/submodelelement/Range.h>

#include <BaSyx/aas/api_v2/submodelelement/property/XSDAnySimpleType.h>

using namespace basyx::xsd_types;
using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
  simple::Range<int>,
  map::Range<int>
>;

template<class Impl>
class RangeTest :public ::testing::Test {
protected:
  std::unique_ptr<api::IRange<int>> range;

protected:
  void SetUp() override
  {
    this->range = util::make_unique<Impl>(std::string("id"));
  }

  void TearDown() override
  {
  }
};

TYPED_TEST_CASE(RangeTest, ImplTypes);

TYPED_TEST(RangeTest, TestGetDataTypeDef)
{
  ASSERT_EQ(this->range->getDataTypeDef(), XsdTypes_::to_string(XsdTypes::xsd_int));
}

TYPED_TEST(RangeTest, TestMaxMin)
{
  ASSERT_EQ(this->range->getMax(), nullptr);
  ASSERT_EQ(this->range->getMin(), nullptr);

  this->range->setMax(util::make_unique<int>(3));
  ASSERT_EQ(*this->range->getMax(), 3);

  this->range->setMin(util::make_unique<int>(-2));
  ASSERT_EQ(*this->range->getMin(), -2);
}
