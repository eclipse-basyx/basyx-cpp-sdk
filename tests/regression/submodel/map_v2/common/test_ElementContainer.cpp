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
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/submodelelement/property/Property.h>

using namespace basyx::aas;
using namespace basyx::aas::map;
using namespace basyx::aas::api;

class ElementContainerTest : public ::testing::Test {
protected:
	ElementContainer<ISubmodelElement> elementContainer;
protected:
	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

TEST_F(ElementContainerTest, TestInit)
{
	ASSERT_EQ(this->elementContainer.size(), 0);
}


TEST_F(ElementContainerTest, TestCreateDeleteAfterwards)
{
	auto prop = this->elementContainer.createElement<Property<int>>("testProperty");
	ASSERT_EQ(this->elementContainer.size(), 1);
	prop->setValue(5);

	// Delete in map
	auto && objectMap = this->elementContainer.getMap();
	objectMap.removeProperty("testProperty");
	ASSERT_EQ(this->elementContainer.size(), 0);
	auto prop_b = this->elementContainer.getElement("testProperty");
	ASSERT_EQ(prop_b, nullptr);
};