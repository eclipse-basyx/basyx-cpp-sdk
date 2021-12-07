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

#include <BaSyx/aas/map_v2/common/LangStringSet.h>

using namespace basyx::aas;
using namespace basyx::aas::map;

class LangStringSetTest : public ::testing::Test {
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

TEST_F(LangStringSetTest, TestFrom_object)
{
	basyx::object object = basyx::object::make_list<basyx::object>();

	auto de = basyx::object::make_map();
  de.insertKey(LangStringSet::Path::Language, "DE");
  de.insertKey(LangStringSet::Path::Text, "Deutscher Text");
  object.insert(de);

  auto en = basyx::object::make_map();
  en.insertKey(LangStringSet::Path::Language, "EN");
  en.insertKey(LangStringSet::Path::Text, "English text");
  object.insert(en);

  auto langStringSet = LangStringSet::from_object(object);

  ASSERT_EQ(langStringSet.get("DE"), "Deutscher Text");
  ASSERT_EQ(langStringSet.get("EN"), "English text");
}

TEST_F(LangStringSetTest, DirectObjectTest)
{
  LangStringSet langStringSet;

  langStringSet.add("NL", "Nederlandse tekst");
  langStringSet.add("ES", "Texto en español");

  auto obj = langStringSet.getMap();

  auto from_object = LangStringSet::from_object(obj);

  ASSERT_EQ(from_object.get("NL"), "Nederlandse tekst");
  ASSERT_EQ(from_object.get("ES"), "Texto en español");
}