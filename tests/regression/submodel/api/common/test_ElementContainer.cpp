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

#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/simple/common/ElementContainer.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>
#include <BaSyx/aas/simple/qualifier/Referable.h>

using namespace basyx::aas;
using namespace basyx::aas::map;
using namespace basyx::aas::api;

using ImplTypes = ::testing::Types<map::ElementContainer<ISubmodelElement>, simple::ElementContainer<ISubmodelElement>>;

template<class Impl>
class ElementContainerTest : public ::testing::Test {
protected:
  using impl_t = Impl;

protected:
	std::unique_ptr<IElementContainer<ISubmodelElement>> elementContainer;
protected:
	void SetUp() override
	{
	  elementContainer = util::make_unique<Impl>();
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(ElementContainerTest, ImplTypes);

TYPED_TEST(ElementContainerTest, TestInit)
{
	ASSERT_EQ(this->elementContainer->size(), 0);
}


TYPED_TEST(ElementContainerTest, TestAdd)
{
	auto prop = util::make_unique<Property<int>>( "testProperty" );
	prop->setValue(5);

	this->elementContainer->addElement(std::move(prop));
	ASSERT_EQ(this->elementContainer->size(), 1);

	auto submodelElement = this->elementContainer->getElement("testProperty");
	auto propB = dynamic_cast<map::Property<int>*>(submodelElement);
	ASSERT_NE(propB, nullptr);
	ASSERT_EQ(propB->getValue(), 5);
};

TYPED_TEST(ElementContainerTest, TestGetByIndex)
{
	auto prop = util::make_unique<Property<int>>("prop1");
	prop->setValue(5);

	auto prop2 = util::make_unique<Property<float>>("prop2");
	prop2->setValue(10.0f);

	this->elementContainer->addElement(std::move(prop));
	this->elementContainer->addElement(std::move(prop2));
	ASSERT_EQ(this->elementContainer->size(), 2);

	auto submodelElement1 = this->elementContainer->getElement(0);
	ASSERT_TRUE(submodelElement1->getIdShort() == "prop1" || submodelElement1->getIdShort() == "prop2");

	auto submodelElement2 = this->elementContainer->getElement(0);
	ASSERT_TRUE(submodelElement2->getIdShort() == "prop1" || submodelElement2->getIdShort() == "prop2");
};

TYPED_TEST(ElementContainerTest, TestCreate)
{
	auto prop = this->elementContainer->template createElement<Property<int>>("testProperty");
	ASSERT_EQ(this->elementContainer->size(), 1);
	prop->setValue(5);

	auto submodelElement = this->elementContainer->getElement("testProperty");
	auto propB = dynamic_cast<map::Property<int>*>(submodelElement);
	ASSERT_NE(propB, nullptr);
	ASSERT_EQ(propB->getValue(), 5);
};

