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
 * test_Key.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/reference/Key.h"

#include "support/KeyMock.hpp"

using namespace basyx::submodel;
using namespace basyx::testing;

class KeyTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}

  void TearDown() override
  {}
};

TEST_F(KeyTest, TestConstructor)
{
  Key key{KeyMock::Path::type, true, KeyMock::Path::value, KeyMock::Path::idType};

  assertTestingKey(key.getMap());
}

TEST_F(KeyTest, TestConstructionFromObject)
{
  KeyMock mock;
  Key key{mock.getMap()};

  assertTestingKey(key.getMap());
}

TEST_F(KeyTest, TestGetType)
{
  KeyMock mock;
  Key key{mock.getMap()};

  auto type = key.getType();

  ASSERT_EQ(type, KeyMock::Path::type);
}

TEST_F(KeyTest, TestGetValue)
{
  KeyMock mock;
  Key key{mock.getMap()};

  auto value = key.getValue();

  ASSERT_EQ(value, KeyMock::Path::value);
}

TEST_F(KeyTest, TestGetIdType)
{
  KeyMock mock;
  Key key{mock.getMap()};

  auto idType = key.getidType();

  ASSERT_EQ(idType, KeyMock::Path::idType);
}

TEST_F(KeyTest, TestGetIsLocal)
{
  KeyMock mock;
  Key key{mock.getMap()};

  auto local = key.isLocal();

  ASSERT_TRUE(local);
}

TEST_F(KeyTest, TestSetType)
{
  KeyMock mock;
  Key key{mock.getMap()};

  key.setType("anotherType");

  auto map = key.getMap();
  basyx::assertions::AssertMapContainsValue<std::string>(map, IKey::Path::Type, "anotherType");
}

TEST_F(KeyTest, TestSetValue)
{
  KeyMock mock;
  Key key{mock.getMap()};

  key.setValue("anotherValue");

  auto map = key.getMap();
  basyx::assertions::AssertMapContainsValue<std::string>(map, IKey::Path::Value, "anotherValue");
}

TEST_F(KeyTest, TestSetIdType)
{
  KeyMock mock;
  Key key{mock.getMap()};

  key.setIdType("anotherIdType");

  auto map = key.getMap();
  basyx::assertions::AssertMapContainsValue<std::string>(map, IKey::Path::IdType, "anotherIdType");
}

TEST_F(KeyTest, TestSetLocal)
{
  KeyMock mock;
  Key key{mock.getMap()};

  key.setLocal(false);

  auto map = key.getMap();
  basyx::assertions::AssertMapContainsValue<bool>(map, IKey::Path::Local, false);
}

