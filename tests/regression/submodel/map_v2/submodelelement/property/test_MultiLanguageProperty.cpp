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

#include <BaSyx/aas/map_v2/submodelelement/property/MultiLanguageProperty.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class MultiLanguagePropertyTest : public ::testing::Test {};

TEST_F(MultiLanguagePropertyTest, TestObjectConstructor)
{
  // compose parent classes
  object object = TestingObjects::object::testingSubmodelElement();
  object.insertKey(MultiLanguageProperty::Path::Value, TestingObjects::map::testingLangString().getMap());
  object.insertKey(MultiLanguageProperty::Path::ValueId, TestingObjects::map::testingReference_1().getMap());

  // build from object
  MultiLanguageProperty multiLanguageProperty{object};

  ASSERT_TRUE(TestingObjects::object::testingSubmodelElement(multiLanguageProperty));
  ASSERT_EQ(TestingObjects::map::testingLangString(), *multiLanguageProperty.getValue());
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *multiLanguageProperty.getValueId());
}

TEST_F(MultiLanguagePropertyTest, TestObjectCopy)
{
  MultiLanguageProperty multiLanguageProperty{std::string{"test id"}};

  ASSERT_EQ(nullptr, multiLanguageProperty.getValue());
  ASSERT_EQ(nullptr, multiLanguageProperty.getValueId());

  multiLanguageProperty.setValue(util::make_unique<LangStringSet>(TestingObjects::map::testingLangString()));
  multiLanguageProperty.setValueId(util::make_unique<Reference>(TestingObjects::map::testingReference_1()));

  auto map = multiLanguageProperty.getMap();
  MultiLanguageProperty copied{map};

  ASSERT_EQ(TestingObjects::map::testingLangString(), *copied.getValue());
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *copied.getValueId());
}