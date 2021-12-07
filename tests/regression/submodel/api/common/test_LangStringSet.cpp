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

#include <BaSyx/aas/api_v2/common/ILangStringSet.h>
#include <BaSyx/aas/map_v2/common/LangStringSet.h>
#include <BaSyx/aas/simple/common/LangStringSet.h>

#include <BaSyx/util/util.h>

using namespace basyx::aas;

using ImplTypes = ::testing::Types<map::LangStringSet, simple::LangStringSet>;

template<class Impl>
class LangStringTest :public ::testing::Test {
protected:
	using impl_t = Impl;

  std::unique_ptr<api::ILangStringSet> langStringSet;
  std::unique_ptr<api::ILangStringSet> ref_langStringSet;
protected:
	void SetUp() override
	{
    langStringSet = util::make_unique<Impl>();
    ref_langStringSet = util::make_unique<Impl>();
	}

	void TearDown() override
	{	}
};

TYPED_TEST_CASE(LangStringTest, ImplTypes);

TYPED_TEST(LangStringTest, TestUnknownLangCode)
{
  const auto string = this->langStringSet->get("UN");

  ASSERT_TRUE(string.empty());
}

TYPED_TEST(LangStringTest, Test)
{
  constexpr char stringValDe[] = "Das ist ein Test!";
  constexpr char stringValEn[] = "This is a test!";

  this->langStringSet->add("DE", stringValDe);
  this->langStringSet->add("EN", stringValEn);

  const auto & deString = this->langStringSet->get("DE");
  const auto & enString = this->langStringSet->get("EN");

  ASSERT_EQ(deString, stringValDe);
  ASSERT_EQ(enString, stringValEn);
};

TYPED_TEST(LangStringTest, TestGetLangCodes)
{
  constexpr char stringValDe[] = "Das ist ein Test!";
  constexpr char stringValEn[] = "This is a test!";
  constexpr char stringValFr[] = "C'est un test!";

  this->langStringSet->add("DE", stringValDe);
  this->langStringSet->add("EN", stringValEn);
  this->langStringSet->add("FR", stringValFr);

  auto lang_codes = this->langStringSet->getLanguageCodes();
  auto reference_codes = api::ILangStringSet::langCodeSet_t{"DE", "EN", "FR"};

  ASSERT_EQ(lang_codes, reference_codes);
}

TYPED_TEST(LangStringTest, TestEqualityOperatorEmpty)
{
  ASSERT_TRUE(*this->langStringSet == *this->ref_langStringSet);
}

TYPED_TEST(LangStringTest, TestEqualityOperatorEqual)
{
  constexpr char stringValDe[] = "Das ist ein Test!";
  constexpr char stringValEn[] = "This is a test!";

  this->langStringSet->add("DE", stringValDe);
  this->langStringSet->add("EN", stringValEn);

  this->ref_langStringSet->add("DE", stringValDe);
  this->ref_langStringSet->add("EN", stringValEn);

  ASSERT_TRUE(*this->langStringSet == *this->ref_langStringSet);
}

TYPED_TEST(LangStringTest, TestEqualityOperatorNotEqual)
{
  constexpr char stringValDe[] = "Das ist ein Test!";
  constexpr char stringValEn[] = "This is a test!";

  this->langStringSet->add("DE", stringValDe);
  this->langStringSet->add("EN", stringValEn);

  this->ref_langStringSet->add("DE", stringValDe);

  ASSERT_FALSE(*this->langStringSet == *this->ref_langStringSet);
}
