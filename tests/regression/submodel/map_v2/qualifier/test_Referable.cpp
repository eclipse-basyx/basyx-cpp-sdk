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

#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class ReferableTest : public ::testing::Test {
protected:
  void SetUp() override
  {
  }

  void TearDown() override
  {
  }
};

TEST_F(ReferableTest, TestObjectConstructor)
{
  basyx::object object = basyx::object::make_map();
  object.insertKey(Referable::Path::IdShort, "test id");
  object.insertKey(Referable::Path::Category, "testing category");
  object.insertKey(Referable::Path::Description, TestingObjects::map::testingLangString().getMap());

  Referable referable{object};

  ASSERT_EQ(referable.getIdShort(), "test id");
  ASSERT_EQ(*referable.getCategory(), "testing category");
  ASSERT_EQ(referable.getDescription(), TestingObjects::map::testingLangString());
}

TEST_F(ReferableTest, TestObjectCopy)
{
  Referable referable(std::string("test id"));
  referable.setCategory("testing category");
  referable.setDescription(TestingObjects::map::testingLangString());

  auto map = referable.getMap();
  Referable copied(map);

  ASSERT_EQ(copied.getIdShort(), "test id");
  ASSERT_EQ(*copied.getCategory(), "testing category");
  ASSERT_EQ(copied.getDescription(), TestingObjects::map::testingLangString());
}