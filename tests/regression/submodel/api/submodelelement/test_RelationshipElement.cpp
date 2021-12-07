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

#include <BaSyx/aas/api_v2/submodelelement/IRelationshipElement.h>
#include <BaSyx/aas/simple/submodelelement/RelationshipElement.h>
#include <BaSyx/aas/map_v2/submodelelement/RelationshipElement.h>
#include <BaSyx/aas/simple/reference/Key.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	std::tuple<simple::RelationshipElement, simple::Reference>,
	std::tuple<map::RelationshipElement, map::Reference>
>;

template<class Impl>
class RelationshipElementTest :public ::testing::Test {
public:
  using impl_t = typename std::tuple_element<0, Impl>::type;
  using reference_t = typename std::tuple_element<1, Impl>::type;

protected:
	std::unique_ptr<api::IRelationshipElement> relationshipElement;
  std::unique_ptr<simple::Key> firstKey;
  std::unique_ptr<simple::Key> secondKey;

protected:
	void SetUp() override
	{
	  this->firstKey = util::make_unique<simple::Key>(basyx::aas::KeyElements::SubmodelElement, true, KeyType::IdShort, "first value");
	  this->secondKey = util::make_unique<simple::Key>(KeyElements::RelationshipElement, false, KeyType::IdShort, "first value");

    reference_t first(*firstKey);
    reference_t second(*secondKey);

    this->relationshipElement = util::make_unique<impl_t>(first, second, "test relationshipElement");
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(RelationshipElementTest, ImplTypes);

TYPED_TEST(RelationshipElementTest, TestConstructor)
{
  ASSERT_EQ(this->relationshipElement->getIdShort(), "test relationshipElement");
	ASSERT_EQ(this->relationshipElement->getFirst().getKeys().at(0), *this->firstKey);
  ASSERT_EQ(this->relationshipElement->getSecond().getKeys().at(0), *this->secondKey);
}
