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

#include <BaSyx/aas/simple/reference/Key.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	simple::Key
>;

template<class Impl>
class KeyTest :public ::testing::Test {
public:
  using impl_t = Impl;

protected:

protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(KeyTest, ImplTypes);

TYPED_TEST(KeyTest, TestConstructor)
{
	using impl_t = typename TestFixture::impl_t;

	impl_t key{KeyElements::Submodel, false, KeyType::Unknown, "test"};

  ASSERT_EQ(key.getType(), KeyElements::Submodel);
  ASSERT_EQ(key.getIdType(), KeyType::Unknown);
  ASSERT_FALSE(key.isLocal());
  ASSERT_EQ(key.getValue(), "test");
}

TYPED_TEST(KeyTest, TestEqualsOperator)
{
  using impl_t = typename TestFixture::impl_t;

  impl_t key_1{KeyElements::Submodel, false, KeyType::Unknown, "test"};
  impl_t key_2{KeyElements::Submodel, false, KeyType::Unknown, "test"};

  ASSERT_EQ(key_1, key_2);

  key_2 = impl_t{KeyElements::Submodel, false, KeyType::Unknown, "test 2"};
  ASSERT_NE(key_1, key_2);

  key_2 = impl_t{KeyElements::Submodel, false, KeyType::FragementId, "test"};
  ASSERT_NE(key_1, key_2);

  key_2 = impl_t{KeyElements::Submodel, true, KeyType::Unknown, "test"};
  ASSERT_NE(key_1, key_2);

  key_2 = impl_t{KeyElements::SubmodelElementCollection, false, KeyType::Unknown, "test"};
  ASSERT_NE(key_1, key_2);

  key_2 = impl_t{KeyElements::RelationshipElement, true, KeyType::IRDI, "test 2"};
  ASSERT_NE(key_1, key_2);
}