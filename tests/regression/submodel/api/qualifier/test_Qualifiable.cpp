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

#include <BaSyx/aas/api_v2/qualifier/IQualifiable.h>
#include <BaSyx/aas/simple/qualifier/Qualifiable.h>
#include <BaSyx/aas/map_v2/qualifier/Qualifiable.h>

#include "support/TestingObjects.h"

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::Qualifiable,
	map::Qualifiable
>;

template<class Impl>
class QualifiableTest :public ::testing::Test {
protected:
	using impl_t = Impl;
	std::unique_ptr<api::IQualifiable> qualifiable;
protected:
	void SetUp() override
	{
		this->qualifiable = util::make_unique<simple::Qualifiable>();
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(QualifiableTest, ImplTypes);

TYPED_TEST(QualifiableTest, TestConstructor)
{
	ASSERT_EQ(this->qualifiable->getFormulas().size(), 0);
	ASSERT_EQ(this->qualifiable->getQualifiers().size(), 0);
}

TYPED_TEST(QualifiableTest, TestListConstructor)
{
  using impl_t = typename TestFixture::impl_t;

  std::vector<simple::Formula> formulas;
  formulas.push_back(TestingObjects::map::testingFormula());

  std::vector<simple::Qualifier> qualifiers;
  qualifiers.push_back(TestingObjects::map::testingQualifier());
  qualifiers.push_back(TestingObjects::map::testingQualifier(2));

  impl_t qualifiable{formulas, qualifiers};

  ASSERT_TRUE(TestingObjects::map::testingFormula(qualifiable.getFormulas().at(0)));

  ASSERT_TRUE(TestingObjects::map::testingQualifier(qualifiable.getQualifiers().at(0)));
  ASSERT_TRUE(TestingObjects::map::testingQualifier(qualifiable.getQualifiers().at(1), 2));
}

TYPED_TEST(QualifiableTest, TestAddFormula)
{
	simple::Key key{ KeyElements::Asset, true, KeyType::Custom, "test" };
	auto formula_in = simple::Formula();
	formula_in.addDependency(
		simple::Reference(key)
	);

	this->qualifiable->addFormula(formula_in);

	ASSERT_EQ(this->qualifiable->getFormulas().size(), 1);
	ASSERT_EQ(this->qualifiable->getQualifiers().size(), 0);

	const auto formulas = this->qualifiable->getFormulas();
	const auto & formula_out = formulas.at(0);

	const auto & dependencies = formula_out.getDependencies();

	ASSERT_EQ(dependencies.size(), 1);
	const auto & ref = dependencies.at(0);

	const auto & keys = ref.getKeys();
	ASSERT_EQ(keys.size(), 1);
	ASSERT_EQ(key, keys[0]);
}


TYPED_TEST(QualifiableTest, TestAddQualifier)
{
	simple::Key key{ KeyElements::Asset, true, KeyType::Custom, "test" };
	simple::Qualifier qualifier_in{ "qType", "vType", "vdType", simple::Reference{key} };

	this->qualifiable->addQualifier(qualifier_in);

	ASSERT_EQ(this->qualifiable->getFormulas().size(), 0);
	ASSERT_EQ(this->qualifiable->getQualifiers().size(), 1);

	const auto qualifiers = this->qualifiable->getQualifiers();
	ASSERT_EQ(qualifiers.size(), 1);
	const auto & qualifier_out = qualifiers.at(0);

	ASSERT_EQ(qualifier_in, qualifier_out);
}
