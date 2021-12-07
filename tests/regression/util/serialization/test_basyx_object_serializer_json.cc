/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include "gtest/gtest.h"

#include <BaSyx/shared/serialization/json.h>

#include <BaSyx/shared/object.h>

#include <string>
#include <cstdint>

class TestBaSyxObjectSerializerJson : public ::testing::Test
{
public:
	using json_t = basyx::serialization::json::json_t;
public:
};

TEST_F(TestBaSyxObjectSerializerJson, FullTest)
{
	auto innerMap = basyx::object::make_map();
	innerMap.insertKey("a", uint64_t{ 1 });
	innerMap.insertKey("b", uint64_t{ 2 });

	auto intList = basyx::object::make_list<uint64_t>({ 1,2,3 });
	auto objList = basyx::object::make_object_list();
	objList.insert(false);
	objList.insert(uint64_t{ 4 });
	objList.insert(5.0);
	objList.insert(std::string("6,0"));
	objList.insert(innerMap);

	auto emptyList = basyx::object::make_object_list();
	auto emptyMap = basyx::object::make_map();

	auto objectMap = basyx::object::make_map();
	objectMap.insertKey("bool", true);
	objectMap.insertKey("int", 1);
	objectMap.insertKey("double", 2.0);
	objectMap.insertKey("string", std::string("test"));
	objectMap.insertKey("innerMap", innerMap);
	objectMap.insertKey("intList", intList);
	objectMap.insertKey("objList", objList);
	objectMap.insertKey("emptyList", emptyList);
	objectMap.insertKey("emptyMap", emptyMap);

	json_t jsonMap = basyx::serialization::json::serialize(objectMap);
	auto dumped = jsonMap.dump(4);

	auto deserialized = basyx::serialization::json::deserialize(dumped);

	ASSERT_TRUE(deserialized.InstanceOf<basyx::object::object_map_t>());
	ASSERT_EQ(deserialized.size(), objectMap.size());

	// Test primitives
	auto dBool = deserialized.getProperty("bool");
	ASSERT_TRUE(dBool.InstanceOf<bool>());
	ASSERT_EQ(dBool.Get<bool>(), true);

	auto dInt = deserialized.getProperty("int");
	ASSERT_TRUE(dInt.InstanceOf<uint64_t>());
	ASSERT_EQ(dInt.Get<uint64_t>(), 1);

	auto dFloat = deserialized.getProperty("double");
	ASSERT_TRUE(dFloat.InstanceOf<double>());
	ASSERT_EQ(dFloat.Get<double>(), 2.0);

	auto dString = deserialized.getProperty("string");
	ASSERT_TRUE(dString.InstanceOf<std::string>());
	ASSERT_EQ(dString.Get<std::string&>(), "test");

	// Test empty containers

	auto dEmptyList = deserialized.getProperty("emptyList");
	ASSERT_TRUE(dEmptyList.InstanceOf<basyx::object::object_list_t>());
	ASSERT_EQ(dEmptyList.size(), 0);

	auto dEmptyMap = deserialized.getProperty("emptyMap");
	ASSERT_TRUE(dEmptyMap.InstanceOf<basyx::object::object_map_t>());
	ASSERT_EQ(dEmptyMap.size(), 0);

	// Test inner map

	auto dInnerMap = deserialized.getProperty("innerMap");
	ASSERT_TRUE(dInnerMap.InstanceOf<basyx::object::object_map_t>());
	ASSERT_EQ(dInnerMap.size(), 2);
	auto & aInnerMap = dInnerMap.Get<basyx::object::object_map_t&>();
	auto & bInnerMap = innerMap.Get<basyx::object::object_map_t&>();
	ASSERT_EQ(aInnerMap, bInnerMap);

	// Test lists

	auto dIntList = deserialized.getProperty("intList");
	ASSERT_TRUE(dIntList.InstanceOf<basyx::object::list_t<uint64_t>>());
	ASSERT_EQ(dIntList.size(), 3);
	auto & aIntList = dIntList.Get<basyx::object::list_t<uint64_t>&>();
	auto & bIntList = intList.Get<basyx::object::list_t<uint64_t>&>();
	ASSERT_EQ(aIntList, bIntList);

	auto dObjList = deserialized.getProperty("objList");
	ASSERT_TRUE(dObjList.InstanceOf<basyx::object::object_list_t>());
	ASSERT_EQ(dObjList.size(), 5);
	auto & aObjList = dObjList.Get<basyx::object::object_list_t&>();
	auto & bObjList = objList.Get<basyx::object::object_list_t&>();
	ASSERT_EQ(aObjList, bObjList);

	return;
}