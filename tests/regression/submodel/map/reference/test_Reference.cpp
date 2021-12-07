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
 * test_Reference.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/reference/Reference.h"
#include "BaSyx/submodel/map/reference/Key.h"

#include "support/AdditionalAssertions.hpp"
#include "support/ReferenceMock.hpp"

using namespace basyx::submodel;
using namespace basyx::testing;

class ReferenceTest : public ::testing::Test
{
protected:
  Reference reference;
  void SetUp() override
  {}

  void TearDown() override
  {
    // test if keys are set
    auto map = reference.getMap();
    basyx::assertions::AssertMapContains(map, IReference::Path::Key);
  }
};

TEST_F(ReferenceTest, TestConstructor)
{}

TEST_F(ReferenceTest, TestConstructFromObject)
{
  auto obj = basyx::object::make_map();
  obj.insertKey("test", "testvalue");
  obj.insertKey(IReference::Path::Key, basyx::object::make_object_list());
  
  reference = Reference(obj);

  auto map = reference.getMap();

  // Ensures that ElementMap constructor is called
  basyx::assertions::AssertMapContainsValue<std::string>(map, "test", "testvalue");
}

TEST_F(ReferenceTest, TestConstructFromKeyList)
{
  auto list = basyx::specificCollection_t<IKey>();
  list.push_back(std::make_shared<KeyMock>());
  list.push_back(std::make_shared<KeyMock>());

  reference = Reference(list);
  
  // presence of key list is checkec in teardown
  // assertContainsKeyMock checks is list contains only keymocks
  assertContainsKeyMock(reference);
}

TEST_F(ReferenceTest, TestConstructFromInitializerList)
{
  Key key1(KeyMock::Path::type, true, KeyMock::Path::value, KeyMock::Path::idType);
  Key key2(KeyMock::Path::type, true, KeyMock::Path::value, KeyMock::Path::idType);

  reference = Reference{key1, key2};

  // presence of key list is checkec in teardown
  // assertContainsKeyMock checks if list contains only keymocks
  assertContainsKeyMock(reference);
}

TEST_F(ReferenceTest, TestConstructFromInitializerList2)
{
  Key key1("key 1 type", true, "a Value", "anIdType");
  Key key2("type of key 2", true, "another Value", "a test id type");
  Key key3("some type", true, "some Value", "another IdType");

  reference = Reference{key1, key2, key3};

  auto keys = reference.getKeys();
  ASSERT_EQ(key1, *keys.at(0));
  ASSERT_EQ(key2, *keys.at(1));
  ASSERT_EQ(key3, *keys.at(2));
}

TEST_F(ReferenceTest, TestConstructionFromOther)
{
  ReferenceMock other;
  reference = Reference(other);

  // should have testing reference properties
  assertTestingReference(reference);
}

TEST_F(ReferenceTest, TestConstructionFromOtherSharedPtr)
{
  std::shared_ptr<IReference> other = std::make_shared<ReferenceMock>();
  reference = Reference(*other);

  // should have testing reference properties
  assertTestingReference(reference);
}

TEST_F(ReferenceTest, TestGetKeys)
{
  auto key_list = basyx::object::make_list<basyx::object>();
  Key key1("key 1 type", true, "a Value", "anIdType");
  key_list.insert(key1.getMap());
  
  Key key2("type of key 2", true, "another Value", "a test id type");
  key_list.insert(key2.getMap());

  auto obj = basyx::object::make_map();
  obj.insertKey(IReference::Path::Key, key_list);
  reference = Reference(obj);

  auto keys = reference.getKeys();
  // keys should be same as in object
  ASSERT_EQ(key1, *keys.at(0));
  ASSERT_EQ(key2, *keys.at(1));
}

TEST_F(ReferenceTest, TestSetKeys)
{
  basyx::specificCollection_t<IKey> key_list;
  std::shared_ptr<IKey> key1 = std::make_shared<Key>("key 1 type", true, "a Value", "anIdType");
  key_list.push_back(key1);
  
  std::shared_ptr<IKey> key2 = std::make_shared<Key>("type of key 2", false, "another Value", "a test id type");
  key_list.push_back(key2);

  reference.setKeys(key_list);

  // keys should be in map
  auto keys_prop = reference.getMap().getProperty(IReference::Path::Key);
  auto keys = keys_prop.Get<std::vector<basyx::object>>();
  ASSERT_EQ(*key1, Key(keys.at(0)));
  ASSERT_EQ(*key2, Key(keys.at(1)));
}
