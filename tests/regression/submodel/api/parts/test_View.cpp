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
#include <tuple>

#include <BaSyx/aas/map_v2/parts/View.h>
#include <BaSyx/aas/simple/parts/View.h>

#include <BaSyx/util/util.h>

using namespace basyx::aas;

using ImplTypes = ::testing::Types
<
  std::tuple<map::View, map::Referable, map::Reference>,
  std::tuple<simple::View, simple::Referable, simple::Reference>
>;

template<class Impl>
class ViewTest :public ::testing::Test {
protected:
  using impl_t = typename std::tuple_element<0, Impl>::type;
  using impl_referable_t = typename std::tuple_element<1, Impl>::type;
  using impl_reference_t = typename std::tuple_element<2, Impl>::type;

  std::unique_ptr<impl_t> view;
  std::unique_ptr<impl_referable_t> referable;
protected:
	void SetUp() override
	{
	    view = util::make_unique<impl_t>("TestView");
      referable = util::make_unique<impl_referable_t>(std::string("TestReferable"));
	}

	void TearDown() override
	{}
};

TYPED_TEST_CASE(ViewTest, ImplTypes);

TYPED_TEST(ViewTest, TestConstructor)
{
  ASSERT_EQ(this->view->getIdShort(), std::string("TestView"));
}

TYPED_TEST(ViewTest, TestContainedElements)
{
  this->view->addContainedElement(std::move(this->referable));

  auto & contained_elements = this->view->getContainedElements();

  ASSERT_NE(contained_elements.getElement("TestReferable"), nullptr);
}

TYPED_TEST(ViewTest, TestSemanticId)
{
  using impl_reference_t = typename TestFixture::impl_reference_t;

  ASSERT_EQ(this->view->getSemanticId(), nullptr);

  std::unique_ptr<impl_reference_t> ref = util::make_unique<impl_reference_t>();

  simple::Key key(KeyElements::Submodel, false, KeyType::URI, "test");
  ref->addKey(key);

  this->view->setSemanticId(std::move(ref));

  ASSERT_EQ(this->view->getSemanticId()->getKeys().at(0).getValue(), std::string("test"));
}