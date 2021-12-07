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
 * test_HasSemantics.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/HasSemantics.h"

#include "support/ReferenceMock.hpp"

using namespace basyx::submodel;


class HasSemanticsTest : public ::testing::Test
{
protected:
  HasSemantics has_semantics;

  void SetUp() override
  {}

  void TearDown() override
  {
    auto map = has_semantics.getMap();
    ASSERT_NO_THROW(map.getProperty(IHasSemantics::Path::SemanticId));
  }
};

TEST_F(HasSemanticsTest, TestSimpleConstructor)
{}

TEST_F(HasSemanticsTest, TestConstructorFromObj)
{
  basyx::object obj = basyx::object::make_map();
  obj.insertKey(IHasSemantics::Path::SemanticId, "test");

  has_semantics = HasSemantics{obj};

  auto map = has_semantics.getMap();
  basyx::object test_obj;
  ASSERT_NO_THROW(test_obj = map.getProperty(IHasSemantics::Path::SemanticId));
  ASSERT_EQ(test_obj.GetStringContent(), "test");
}

TEST_F(HasSemanticsTest, TestConstructorPassReferenceSharedPtr)
{
  std::shared_ptr<IReference> ref = std::make_shared<basyx::testing::ReferenceMock>();

  has_semantics = HasSemantics{ref};

  auto map = has_semantics.getMap();
  basyx::object test_obj;
  ASSERT_NO_THROW(test_obj = map.getProperty(IHasSemantics::Path::SemanticId));
  ASSERT_TRUE(basyx::testing::referenceObjectContainsKeyMock(test_obj));
}

TEST_F(HasSemanticsTest, TestSetSemanticID)
{
  std::shared_ptr<IReference> ref = std::make_shared<basyx::testing::ReferenceMock>();

  has_semantics.setSemanticId(ref);

  auto map = has_semantics.getMap();
  basyx::object test_obj;
  ASSERT_NO_THROW(test_obj = map.getProperty(IHasSemantics::Path::SemanticId));
  ASSERT_TRUE(basyx::testing::referenceObjectContainsKeyMock(test_obj));
}

TEST_F(HasSemanticsTest, TestGetSemanticID)
{
  basyx::object obj = basyx::object::make_map();
  obj.insertKey(IHasSemantics::Path::SemanticId, basyx::testing::ReferenceMock{}.getMap());

  has_semantics = HasSemantics{obj};

  auto ref = has_semantics.getSemanticId();
  basyx::testing::assertContainsKeyMock(ref);
}
