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

#include <BaSyx/vab/provider/hashmap/VABHashmapProvider.h>

#include <vab/stub/elements/SimpleVABElement.h>

#include "snippet/MapRead.h"
#include "snippet/MapCreateDelete.h"
#include "snippet/MapUpdate.h"
#include "snippet/MapInvoke.h"
#include "snippet/TestCollectionProperty.h"

#include <BaSyx/shared/serialization/json.h>

#include <memory>
#include <unordered_map>
#include <vector>

using namespace basyx;

class TestBaSyxHashmapProvider : public ::testing::Test {
public:
	vab::provider::VABModelProvider hashMapProvider;

	virtual void SetUp()
	{
		basyx::object::list_t<uint64_t> collection;
		collection.emplace_back(1);
		collection.emplace_back(2);

		basyx::object::object_map_t outerMap, innerMap, propertyMap;

		propertyMap.emplace("Test", 321);
		propertyMap.emplace("test", 123);

		innerMap.emplace("property1.1", 7);
		innerMap.emplace("property1.2", std::move(collection));
		innerMap.emplace("propertyMap", std::move(propertyMap));

		outerMap.emplace("property1", std::move(innerMap));

		hashMapProvider = vab::provider::VABModelProvider{ std::move(outerMap) };
	}

	virtual void TearDown()
	{
	}
};

TEST_F(TestBaSyxHashmapProvider, GetPropertyValue)
{
	// Get property value
	basyx::object  property1 = hashMapProvider.getModelPropertyValue("property1");

	basyx::object  value1 = hashMapProvider.getModelPropertyValue("property1/property1.1");
	basyx::object  value2 = hashMapProvider.getModelPropertyValue("/property1/property1.1");
	basyx::object  value3 = hashMapProvider.getModelPropertyValue("property1/property1.1/");
	basyx::object  value4 = hashMapProvider.getModelPropertyValue("/property1/property1.1/");

	basyx::object  mapTest1 = hashMapProvider.getModelPropertyValue("property1/propertyMap/Test");
	basyx::object  mapTest2 = hashMapProvider.getModelPropertyValue("property1/propertyMap/test");

	// Check test case results
	ASSERT_TRUE(property1.InstanceOf<basyx::object::object_map_t>());
	ASSERT_EQ(property1.Get<basyx::object::object_map_t&>().size(), 3);

	ASSERT_TRUE(value1.InstanceOf<int>());
	ASSERT_TRUE(value2.InstanceOf<int>());
	ASSERT_TRUE(value3.InstanceOf<int>());
	ASSERT_TRUE(value4.InstanceOf<int>());
	ASSERT_TRUE(mapTest1.InstanceOf<int>());
	ASSERT_TRUE(mapTest2.InstanceOf<int>());

	ASSERT_EQ(value1.Get<int>(), 7);
	ASSERT_EQ(value2.Get<int>(), 7);
	ASSERT_EQ(value3.Get<int>(), 7);
	ASSERT_EQ(value4.Get<int>(), 7);
	ASSERT_EQ(mapTest1.Get<int>(), 321);
	ASSERT_EQ(mapTest2.Get<int>(), 123);

	// Get non-existing property
	basyx::object unknown = hashMapProvider.getModelPropertyValue("property1/unknown");

	ASSERT_TRUE(unknown.IsError());
	ASSERT_EQ(unknown.getError(), basyx::object::error::PropertyNotFound);
}

int testFunc(int a, int b)
{
	return a + b;
}

TEST_F(TestBaSyxHashmapProvider, TestInvoke)
{
	hashMapProvider.createValue("function", basyx::object::make_function(testFunc));

	auto args = basyx::object::make_list<basyx::object>({ 1,2 });

	auto val = hashMapProvider.invokeOperation("function", args);

	ASSERT_ANY_EQ(val, 3);
}

TEST_F(TestBaSyxHashmapProvider, SetPropertyValue)
{
	// Set and reread property value
	hashMapProvider.setModelPropertyValue("property1/property1.1", 12);
	basyx::object  property1_1 = hashMapProvider.getModelPropertyValue("property1/property1.1");

	// Check test case results
	ASSERT_TRUE(property1_1.InstanceOf<int>());
	ASSERT_EQ(property1_1.Get<int>(), 12);

	// Change value back
	hashMapProvider.setModelPropertyValue("property1/property1.1", 7);
	basyx::object  property1_1b = hashMapProvider.getModelPropertyValue("property1/property1.1");

	// Check test case results
	ASSERT_TRUE(property1_1b.InstanceOf<int>());
	ASSERT_EQ(property1_1b.Get<int>(), 7);
}

TEST_F(TestBaSyxHashmapProvider, CreateDelete)
{
	basyx::object  property1 = hashMapProvider.getModelPropertyValue("property1");
	basyx::object  property1_1 = hashMapProvider.getModelPropertyValue("property1/property1.1");

	ASSERT_TRUE(property1.InstanceOf<basyx::object::object_map_t>());
	ASSERT_TRUE(property1_1.InstanceOf<int>());
	ASSERT_EQ(property1_1.Get<int>(), 7);

	// - Create property directly in VAB element
	hashMapProvider.createValue("property2", 21);
	// - Create property in contained hashmap
	hashMapProvider.createValue("property1/property1.4", 22);
	// - Create property in collection in contained hashmap
	hashMapProvider.createValue("property1/property1.2", uint64_t{ 23 });

	// Read values back
	basyx::object  property2 = hashMapProvider.getModelPropertyValue("property2");
	// - Check test case results
	ASSERT_TRUE(property2.InstanceOf<int>());
	ASSERT_EQ(property2.Get<int>(), 21);

	// Read values back
	basyx::object  property1_4 = hashMapProvider.getModelPropertyValue("property1/property1.4");
	// - Check test case results
	ASSERT_TRUE(property1_4.InstanceOf<int>());
	ASSERT_EQ(property1_4.Get<int>(), 22);

	// Read values back
	basyx::object  property1_2 = hashMapProvider.getModelPropertyValue("property1/property1.2");
	// - Check test case results
	ASSERT_TRUE(property1_2.InstanceOf<basyx::object::list_t<uint64_t>>());
	ASSERT_EQ(property1_2.Get<basyx::object::list_t<uint64_t>&>().size(), 3);

	// Delete properties
	hashMapProvider.deleteValue("property2");
	hashMapProvider.deleteValue("property1/property1.4");
	//   	hashMapProvider.deleteValue("property1/property1.2", 23);

		// Read values back
		//basyx::object  property2_del = hashMapProvider.getModelPropertyValue("property2");	// - Check test case results
		//assertEquals(null, value6);

		// Read values back
		//basyx::object  property1_4del = hashMapProvider.getModelPropertyValue("property1/property1.4");	// - Check test case results
		// - Check test case results
		//assertEquals(null, value7);

		// Read values back
	basyx::object  property1_2b = hashMapProvider.getModelPropertyValue("property1/property1.2");
	// - Check test case results
	ASSERT_TRUE(property1_2b.InstanceOf<basyx::object::list_t<uint64_t>>());
	ASSERT_EQ(property1_2b.Get<basyx::object::list_t<uint64_t>&>().size(), 3);
}

TEST_F(TestBaSyxHashmapProvider, MapRead)
{
	vab::provider::VABModelProvider hashMapProvider{ tests::support::make_simple_vab_element() };

	tests::regression::vab::snippet::MapRead::test(&hashMapProvider);
}

TEST_F(TestBaSyxHashmapProvider, MapUpdate)
{
	vab::provider::VABModelProvider hashMapProvider{ tests::support::make_simple_vab_element() };

	tests::regression::vab::snippet::MapUpdate::test(&hashMapProvider);
}

TEST_F(TestBaSyxHashmapProvider, MapCreateDelete)
{
	vab::provider::VABModelProvider hashMapProvider{ tests::support::make_simple_vab_element() };

	tests::regression::vab::snippet::MapCreateDelete::test(&hashMapProvider);
}

TEST_F(TestBaSyxHashmapProvider, MapInvoke)
{
	vab::provider::VABModelProvider hashMapProvider{ tests::support::make_simple_vab_element() };

	tests::regression::vab::snippet::MapInvoke::test(&hashMapProvider);
}

TEST_F(TestBaSyxHashmapProvider, TestCollectionProperty)
{
	vab::provider::VABModelProvider hashMapProvider{ tests::support::make_simple_vab_element() };

	tests::regression::vab::snippet::TestCollectionProperty::test(&hashMapProvider);
}
