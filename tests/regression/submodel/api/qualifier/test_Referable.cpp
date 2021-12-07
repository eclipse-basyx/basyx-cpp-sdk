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

#include <BaSyx/aas/api_v2/qualifier/IReferable.h>
#include <BaSyx/aas/simple/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>

using namespace basyx::aas;

// Constants
std::string idShort = "testId";

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::Referable, 
	map::Referable
>;

template<class Impl>
class ReferableTest :public ::testing::Test {
protected:
	using impl_t = Impl;
	std::unique_ptr<api::IReferable> referable;
protected:
	void SetUp() override
	{
		this->referable = util::make_unique<Impl>(idShort, nullptr);
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(ReferableTest, ImplTypes);

TYPED_TEST(ReferableTest, TestConstructor)
{
	ASSERT_EQ(this->referable->getIdShort(), idShort);
	ASSERT_EQ(this->referable->getCategory(), nullptr);
}

TYPED_TEST(ReferableTest, TestSetCategory)
{
	ASSERT_EQ(this->referable->getCategory(), nullptr);
	this->referable->setCategory("category");
	ASSERT_TRUE(this->referable->getCategory() != nullptr);
	ASSERT_EQ(*this->referable->getCategory() , "category");
}
