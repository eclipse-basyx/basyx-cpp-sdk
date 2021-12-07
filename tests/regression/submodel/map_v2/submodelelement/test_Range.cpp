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

#include <BaSyx/aas/map_v2/submodelelement/Range.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class RangeTest : public ::testing::Test {};

TEST_F(RangeTest, TestObjectConstructorEmpty)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Range<simple::Date> range{object};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(range));
  ASSERT_EQ(nullptr, range.getMin());
  ASSERT_EQ(nullptr, range.getMax());
}

TEST_F(RangeTest, TestObjectConstructorUInt64)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Range<uint64_t> range{object};
  uint64_t min = 262654545;
  uint64_t max = 2626545452;
  range.setMin(util::make_unique<uint64_t>(min));
  range.setMax(util::make_unique<uint64_t>(max));

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(range));
  ASSERT_EQ(min, *range.getMin());
  ASSERT_EQ(max, *range.getMax());

  Range<uint64_t> copied{range.getMap()};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(copied));
  ASSERT_EQ(min, *copied.getMin());
  ASSERT_EQ(max, *copied.getMax());
}

TEST_F(RangeTest, TestObjectConstructorDouble)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Range<double> range{object};
  double min = 2.0;
  double max = 2625656565656.200012;
  range.setMin(util::make_unique<double>(min));
  range.setMax(util::make_unique<double>(max));

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(range));
  ASSERT_EQ(min, *range.getMin());
  ASSERT_EQ(max, *range.getMax());

  Range<double> copied{range.getMap()};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(copied));
  ASSERT_EQ(min, *copied.getMin());
  ASSERT_EQ(max, *copied.getMax());
}

TEST_F(RangeTest, TestObjectConstructorString)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Range<std::string> range{object};
  std::string min{"ab"};
  std::string max{"zz"};
  range.setMin(util::make_unique<std::string>(min));
  range.setMax(util::make_unique<std::string>(max));

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(range));
  ASSERT_EQ(min, *range.getMin());
  ASSERT_EQ(max, *range.getMax());

  Range<std::string> copied{range.getMap()};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(copied));
  ASSERT_EQ(min, *copied.getMin());
  ASSERT_EQ(max, *copied.getMax());
}

TEST_F(RangeTest, TestObjectConstructorDayTimeDuration)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Range<simple::DayTimeDuration> range{object};
  simple::DayTimeDuration min{std::chrono::duration<long>(2)};
  simple::DayTimeDuration max{std::chrono::duration<long>(200)};
  range.setMin(util::make_unique<simple::DayTimeDuration>(min));
  range.setMax(util::make_unique<simple::DayTimeDuration>(max));

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(range));
  ASSERT_EQ(min.getDuration(), range.getMin()->getDuration());
  ASSERT_EQ(max.getDuration(), range.getMax()->getDuration());

  Range<simple::DayTimeDuration> copied{range.getMap()};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(copied));
  ASSERT_EQ(min.getDuration(), copied.getMin()->getDuration());
  ASSERT_EQ(max.getDuration(), copied.getMax()->getDuration());
}

TEST_F(RangeTest, TestObjectConstructorGMonth)
{
  auto object = TestingObjects::object::testingSubmodelElement();

  // build from object
  Range<simple::GMonth> range{object};
  simple::GMonth min{2};
  simple::GMonth max{5};
  range.setMin(util::make_unique<simple::GMonth>(min));
  range.setMax(util::make_unique<simple::GMonth>(max));

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(range));
  ASSERT_EQ(min.getMonth(), range.getMin()->getMonth());
  ASSERT_EQ(max.getMonth(), range.getMax()->getMonth());
  ASSERT_EQ(min.getTimezone().getTimezone(), range.getMin()->getTimezone().getTimezone());
  ASSERT_EQ(max.getTimezone().getTimezone(), range.getMax()->getTimezone().getTimezone());

  Range<simple::GMonth> copied{range.getMap()};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(copied));
  ASSERT_EQ(min.getMonth(), copied.getMin()->getMonth());
  ASSERT_EQ(max.getMonth(), copied.getMax()->getMonth());
  ASSERT_EQ(min.getTimezone().getTimezone(), copied.getMin()->getTimezone().getTimezone());
  ASSERT_EQ(max.getTimezone().getTimezone(), copied.getMax()->getTimezone().getTimezone());
}