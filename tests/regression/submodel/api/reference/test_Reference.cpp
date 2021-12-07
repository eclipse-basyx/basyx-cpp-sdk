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

#include <BaSyx/aas/api_v2/reference/IReference.h>
#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::Reference,
	map::Reference
>;

template<class Impl>
class ReferenceTest :public ::testing::Test {
public:
  using impl_t = Impl;

protected:
	std::unique_ptr<api::IReference> reference;

protected:
	void SetUp() override
	{
		this->reference = util::make_unique<Impl>();
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(ReferenceTest, ImplTypes);

TYPED_TEST(ReferenceTest, TestConstructor)
{
	auto keys = this->reference->getKeys();
	ASSERT_EQ(keys.size(), 0);
}

TYPED_TEST(ReferenceTest, TestAddKey)
{
	simple::Key key{ KeyElements::Asset, true, KeyType::Custom, "key" };
	this->reference->addKey(key);

	auto keys = this->reference->getKeys();
	ASSERT_EQ(keys.size(), 1);
	ASSERT_EQ(keys[0], key);
}

TYPED_TEST(ReferenceTest, TestEqualsOperator)
{
  using impl_t = typename TestFixture::impl_t;

  simple::Key key_1{ KeyElements::Asset, true, KeyType::Custom, "key" };
  impl_t ref_1{key_1};

  simple::Reference ref_map{key_1};
  map::Reference ref_simple{key_1};

  ASSERT_EQ(ref_1, ref_simple);
  ASSERT_EQ(ref_1, ref_map);

  simple::Key key_2{ KeyElements::SubmodelElementCollection, false, KeyType::FragementId, "other key" };
  ref_1.addKey(key_2);
  ASSERT_NE(ref_1, ref_simple);
  ASSERT_NE(ref_1, ref_map);

  ref_simple.addKey(key_2);
  ref_map.addKey(key_2);
  ASSERT_EQ(ref_1, ref_simple);
  ASSERT_EQ(ref_1, ref_map);
}