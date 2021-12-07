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

#include <BaSyx/aas/api_v2/constraint/IFormula.h>
#include <BaSyx/aas/simple/constraint/Formula.h>
#include <BaSyx/aas/map_v2/constraint/Formula.h>

#include "support/TestingObjects.h"

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::Formula,
	map::Formula
>;

template<class Impl>
class FormulaTest :public ::testing::Test {
protected:
	using impl_t = Impl;
	std::unique_ptr<api::IFormula> formula;
protected:
	void SetUp() override
	{
		this->formula = util::make_unique<Impl>();
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(FormulaTest, ImplTypes);

TYPED_TEST(FormulaTest, TestConstructor)
{
	ASSERT_TRUE(this->formula->getDependencies().empty());
}

TYPED_TEST(FormulaTest, TestListConstructor)
{
  using impl_t = typename TestFixture::impl_t;

  std::vector<simple::Reference> dependencies;
  dependencies.push_back(TestingObjects::map::testingReference_1());
  dependencies.push_back(TestingObjects::map::testingReference_2());

  impl_t formula(dependencies);

  auto deps = formula.getDependencies();
  ASSERT_EQ(dependencies, deps);
}

TYPED_TEST(FormulaTest, TestAdd)
{
	this->formula->addDependency(
		simple::Reference(simple::Key{ KeyElements::Asset, true, KeyType::Custom, "test" })
		);

	const auto & dependencies = this->formula->getDependencies();

	ASSERT_EQ(dependencies.size(), 1);
	const auto & ref = dependencies.at(0);

	const auto & keys = ref.getKeys();
	ASSERT_EQ(keys.size(), 1);
	ASSERT_EQ(keys[0].isLocal(), true);
	ASSERT_EQ(keys[0].getIdType(), KeyType::Custom);
	ASSERT_EQ(keys[0].getType(), KeyElements::Asset);
	ASSERT_EQ(keys[0].getValue(), "test");
}
