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

#include <BaSyx/aas/api_v2/submodelelement/IAnnotatedRelationshipElement.h>
#include <BaSyx/aas/simple/submodelelement/AnnotatedRelationshipElement.h>
#include <BaSyx/aas/map_v2/submodelelement/AnnotatedRelationshipElement.h>

#include <BaSyx/aas/simple/submodelelement/property/ReferenceElement.h>
#include <BaSyx/aas/map_v2/submodelelement/property/ReferenceElement.h>

using namespace basyx::aas;

// Implementations to run tests for
using ImplTypes = ::testing::Types<
	std::tuple<simple::AnnotatedRelationshipElement, simple::Reference, simple::ReferenceElement>,
	std::tuple<map::AnnotatedRelationshipElement, map::Reference, map::ReferenceElement>
>;

template<class Impl>
class AnnotatedRelationshipElementTest :public ::testing::Test {
public:
  using impl_t = typename std::tuple_element<0, Impl>::type;
  using reference_t = typename std::tuple_element<1, Impl>::type;
  using referenceElement_t = typename std::tuple_element<2, Impl>::type;

protected:
	std::unique_ptr<impl_t> annotatedRelationshipElement;
  std::unique_ptr<simple::Key> firstKey;
  std::unique_ptr<simple::Key> secondKey;

protected:
  void SetUp() override
  {
    this->firstKey = util::make_unique<simple::Key>(basyx::aas::KeyElements::SubmodelElement, true, KeyType::IdShort, "first value");
    this->secondKey = util::make_unique<simple::Key>(KeyElements::RelationshipElement, false, KeyType::IdShort, "first value");

    reference_t first(*firstKey);
    reference_t second(*secondKey);
		this->annotatedRelationshipElement = util::make_unique<impl_t>(first, second, "test annotatedRelationshipElement");
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(AnnotatedRelationshipElementTest, ImplTypes);

TYPED_TEST(AnnotatedRelationshipElementTest, TestConstructor)
{
  ASSERT_EQ(this->annotatedRelationshipElement->getIdShort(), "test annotatedRelationshipElement");
}

TYPED_TEST(AnnotatedRelationshipElementTest, TestAddAnnotation)
{
  using referenceElement_t = typename TestFixture::referenceElement_t;

  auto annotation = util::make_unique<referenceElement_t>(std::string{"test reference element"});
  this->annotatedRelationshipElement->addAnnotation(std::move(annotation));

  ASSERT_EQ(this->annotatedRelationshipElement->getAnnotation().getElement(0)->getIdShort(), "test reference element");
}
