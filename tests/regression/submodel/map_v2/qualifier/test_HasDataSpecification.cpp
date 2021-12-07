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

#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class HasDataSpecificationTest : public ::testing::Test {
protected:
  void SetUp() override
  {
  }

  void TearDown() override
  {
  }
};

TEST_F(HasDataSpecificationTest, TestObjectConstructor)
{
  basyx::object object = basyx::object::make_map();

  basyx::object list = basyx::object::make_list<basyx::object>();
  list.insert(TestingObjects::map::testingReference_1().getMap());
  list.insert(TestingObjects::map::testingReference_2().getMap());

  object.insertKey(HasDataSpecification::Path::DataSpecification, list);

  HasDataSpecification hasDataSpecification(object);

  auto & dataSpecRefs = hasDataSpecification.getDataSpecificationReference();
  ASSERT_EQ(dataSpecRefs.size(), 2);
  ASSERT_EQ(dataSpecRefs.at(0), TestingObjects::map::testingReference_1());
  ASSERT_EQ(dataSpecRefs.at(1), TestingObjects::map::testingReference_2());
}

TEST_F(HasDataSpecificationTest, TestObjectCopy)
{
  HasDataSpecification hasDataSpecification;
  hasDataSpecification.addDataSpecification(TestingObjects::map::testingReference_1());
  hasDataSpecification.addDataSpecification(TestingObjects::map::testingReference_2());

    hasDataSpecification.getDataSpecificationReference();

  auto map = hasDataSpecification.getMap();

  HasDataSpecification copied(map);

  auto & dataSpecRefs = copied.getDataSpecificationReference();
  ASSERT_EQ(dataSpecRefs.size(), 2);
  ASSERT_EQ(dataSpecRefs.at(0), TestingObjects::map::testingReference_1());
  ASSERT_EQ(dataSpecRefs.at(1), TestingObjects::map::testingReference_2());
}