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

#include <BaSyx/shared/object.h>

#include <string>
#include <cstdint>

class TestBaSyxObject : public ::testing::Test
{

};

namespace objectTest
{
	class TestClass {
	public:
		bool testFunc() {
			return true;
		};
	};

	int FuncAdd(int a, int b) { return a + b; };
	int FuncInc(int a) { return a + 1; };
	int FuncConst() { return 42; };
}

TEST_F(TestBaSyxObject, TypeTest)
{
	//// This shouldn't compile:
	//	basyx::type::basyx_type<TestBaSyxObject>::object_type;

	//// Test primitives

	// Integers
	ASSERT_EQ(basyx::type::basyx_type<int>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<int>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<unsigned int>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<unsigned int>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<short>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<short>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<unsigned short>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<unsigned short>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<char>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<char>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<unsigned char>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<unsigned char>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<int8_t>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<int8_t>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<uint8_t>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<uint8_t>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<int32_t>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<int32_t>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<uint32_t>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<uint32_t>::value_type, basyx::type::valueType::Int);
	
	ASSERT_EQ(basyx::type::basyx_type<int64_t>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<int64_t>::value_type, basyx::type::valueType::Int);
	
	ASSERT_EQ(basyx::type::basyx_type<uint64_t>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<uint64_t>::value_type, basyx::type::valueType::Int);

	// Floats
	ASSERT_EQ(basyx::type::basyx_type<float>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<float>::value_type, basyx::type::valueType::Float);

	ASSERT_EQ(basyx::type::basyx_type<double>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<double>::value_type, basyx::type::valueType::Float);

	// Bool
	ASSERT_EQ(basyx::type::basyx_type<bool>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<bool>::value_type, basyx::type::valueType::Bool);

	// std::string
	ASSERT_EQ(basyx::type::basyx_type<std::string>::object_type, basyx::type::objectType::Primitive);
	ASSERT_EQ(basyx::type::basyx_type<std::string>::value_type, basyx::type::valueType::String);

	//// Test complex

	// lists
	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<int>>::object_type, basyx::type::objectType::List);
	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<int>>::value_type, basyx::type::valueType::Int);

	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<uint64_t>>::object_type, basyx::type::objectType::List);
	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<uint64_t>>::value_type, basyx::type::valueType::Int);
	
	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<std::string>>::object_type, basyx::type::objectType::List);
	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<std::string>>::value_type, basyx::type::valueType::String);

	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<double>>::object_type, basyx::type::objectType::List);
	ASSERT_EQ(basyx::type::basyx_type<basyx::object::list_t<double>>::value_type, basyx::type::valueType::Float);

	// functions
	ASSERT_EQ(basyx::type::basyx_type<basyx::detail::functionWrapper>::object_type, basyx::type::objectType::Function);
	ASSERT_EQ(basyx::type::basyx_type<basyx::detail::functionWrapper>::value_type, basyx::type::valueType::Object);
}

TEST_F(TestBaSyxObject, RefTest)
{

	int a = 5;
	basyx::object ref = basyx::object::make_object_ref(&a);

	ASSERT_FALSE(ref.IsNull());
	ASSERT_FALSE(ref.IsError());
	ASSERT_TRUE(ref.InstanceOf<int>());
	ASSERT_EQ(ref.GetPtr<int>(), &a);
	ASSERT_EQ(ref.Get<int>(), 5);

	// Test destruction of object_ref
	std::string str = "TEST";
	{
		auto stringRef = basyx::object::make_object_ref(&str);

		ASSERT_FALSE(stringRef.IsNull());
		ASSERT_TRUE(stringRef.InstanceOf<std::string>());
		ASSERT_EQ(stringRef.GetPtr<std::string>(), &str);
	};

	ASSERT_EQ(str, "TEST");
}

TEST_F(TestBaSyxObject, IntTest)
{
	basyx::object anyInt = 2;

	ASSERT_FALSE(anyInt.IsError());
	ASSERT_TRUE(anyInt.InstanceOf<int>());
	ASSERT_FALSE(anyInt.InstanceOf<float>());
	ASSERT_FALSE(anyInt.InstanceOf<double>());
	ASSERT_FALSE(anyInt.InstanceOf<std::string>());

	ASSERT_EQ(anyInt.Get<int>(), 2);

	int int_val = anyInt.Get<int>();
	int_val = 10;
	ASSERT_EQ(anyInt.Get<int>(), 2);

	int & int_ref = anyInt.Get<int&>();
	int_ref = 5;
	ASSERT_EQ(int_ref, anyInt.Get<int>());

	int & int_ref2 = anyInt.Get<int&>();
	int_ref2 = 15;

	ASSERT_EQ(anyInt.Get<int>(), 15);
	ASSERT_EQ(int_ref, 15);
	ASSERT_EQ(int_ref2, 15);

	EXPECT_THROW(anyInt.Get<float>(), basyx::bad_object_cast);
}

TEST_F(TestBaSyxObject, FactoryTest)
{
	// Test null object
	basyx::object nullObject = basyx::object::make_null();
	ASSERT_TRUE(nullObject.IsNull());
	ASSERT_FALSE(nullObject.IsError());

	// Test with empty constructor
	basyx::object anyVec = basyx::object::make_list<int>();

	ASSERT_FALSE(anyVec.IsNull());
	ASSERT_FALSE(anyVec.IsError());
	ASSERT_TRUE(anyVec.InstanceOf<basyx::object::list_t<int>>());

	auto & vec = anyVec.Get<basyx::object::list_t<int>&>();

	ASSERT_EQ(vec.size(), 0);

	// Test with count constructor
	basyx::object anyVec2 = basyx::object::make_list<int>(2, 5);

	ASSERT_FALSE(anyVec2.IsNull());
	ASSERT_FALSE(anyVec2.IsError());
	ASSERT_TRUE(anyVec2.InstanceOf<basyx::object::list_t<int>>());

	auto & vec2 = anyVec2.Get<basyx::object::list_t<int>&>();

	ASSERT_EQ(vec2.size(), 2);
	ASSERT_EQ(vec2[0], 5);
	ASSERT_EQ(vec2[1], 5);

	// Test with initializer-list
	basyx::object anyVec3 = basyx::object::make_list<int, std::initializer_list<int>>({ 1,2,3 });

	ASSERT_FALSE(anyVec3.IsNull());
	ASSERT_FALSE(anyVec3.IsError());
	ASSERT_TRUE(anyVec3.InstanceOf<basyx::object::list_t<int>>());

	auto & vec3 = anyVec3.Get<basyx::object::list_t<int>&>();

	ASSERT_EQ(vec3.size(), 3);
	ASSERT_EQ(vec3[0], 1);
	ASSERT_EQ(vec3[1], 2);
	ASSERT_EQ(vec3[2], 3);

	// Test make_function
	basyx::object func1 = basyx::object::make_function(objectTest::FuncAdd);
	ASSERT_FALSE(func1.IsError());
	ASSERT_EQ(func1.GetObjectType(), basyx::type::objectType::Function);
	ASSERT_EQ(func1.GetValueType(), basyx::type::valueType::Object);

	// Test make_error
	basyx::object error = basyx::object::make_error(basyx::object::error::PropertyNotFound);
	ASSERT_TRUE(error.IsError());
	ASSERT_EQ(error.getError(), basyx::object::error::PropertyNotFound);
}

TEST_F(TestBaSyxObject, InsertTest)
{
	basyx::object anyVec = basyx::object::list_t<int>{ 1,2 };
	auto & vec = anyVec.Get<basyx::object::list_t<int>&>();

	ASSERT_EQ(vec.size(), 2);
	ASSERT_TRUE(anyVec.insert(3));
	ASSERT_EQ(vec.size(), 3);
}

TEST_F(TestBaSyxObject, InsertTestObject)
{
	basyx::object anyVec = basyx::object::list_t<uint64_t>{ 1,2 };
	auto & vec = anyVec.Get<basyx::object::list_t<uint64_t>&>();

	uint64_t i = 5;

	// Insert new elements
	ASSERT_EQ(vec.size(), 2);
	ASSERT_TRUE(anyVec.insert(basyx::object::make_object_ref(&i)));
	ASSERT_EQ(vec.size(), 3);
	ASSERT_TRUE(anyVec.insert(basyx::object(uint64_t{ 10 })));
	ASSERT_EQ(vec.size(), 4);

	// Insert new element, but with wrong type, shouldn't do anything
	ASSERT_FALSE(anyVec.insert(basyx::object(5.0f)));
	ASSERT_EQ(vec.size(), 4);
}

TEST_F(TestBaSyxObject, RemoveTest)
{

}

TEST_F(TestBaSyxObject, HashMapTest_Object)
{
	basyx::object anyMap = basyx::object::make_map();
	auto & map = anyMap.Get<basyx::object::object_map_t&>();
	
	int i = 1;

	ASSERT_EQ(map.size(), 0);
	ASSERT_TRUE(anyMap.insertKey("test", basyx::object::make_object_ref(&i)));
	ASSERT_EQ(map.size(), 1);
	
	// Insert element with same key again, with overwrite = false, shouldn't do anything
	ASSERT_FALSE(anyMap.insertKey("test", basyx::object::make_object_ref(&i), false));
	ASSERT_EQ(map.size(), 1);

	// Insert element with another key
	ASSERT_TRUE(anyMap.insertKey("test2", basyx::object(5.0f)));
	ASSERT_EQ(map.size(), 2);

	// Insert element with another key, set overwrite = true
	ASSERT_TRUE(anyMap.insertKey("test2", basyx::object::make_object_ref(&i), true));
	ASSERT_EQ(map.size(), 2);
	ASSERT_TRUE(map["test2"].InstanceOf<int>());
	ASSERT_EQ(map["test2"].Get<int>(), i);

	auto obj = anyMap.getProperty("test2");
	ASSERT_FALSE(obj.IsNull());
	ASSERT_TRUE(obj.InstanceOf<int>());
	ASSERT_EQ(obj.Get<int>(), i);
}

TEST_F(TestBaSyxObject, ObjectFunctionTest)
{
	basyx::object argSingle = 2;
	basyx::object argFloat = 4.0f;
	basyx::object argList1 = basyx::object::make_list<basyx::object>(std::initializer_list<basyx::object>{ 2, 3 });
	basyx::object argList2 = basyx::object::make_list<basyx::object>(std::initializer_list<basyx::object>{ 3, 4, 5 });

	basyx::object func1 = basyx::object::make_function(objectTest::FuncInc);
	basyx::object func2 = basyx::object::make_function(objectTest::FuncAdd);

	// Invoke non-function object
	ASSERT_TRUE(argSingle.invoke().IsNull());
	ASSERT_TRUE(argSingle.invoke(argFloat).IsNull());

	// Call func1 with no arguments, should return object::null
	ASSERT_TRUE(func1.invoke().IsNull());

	// Call func1 with non-primitive object, wrong value type, should return object:null
	ASSERT_TRUE(func1.invoke(argList1).IsNull());

	// Call func1 with primitive object, wrong value type, should return object:null
	ASSERT_TRUE(func1.invoke(argFloat).IsNull());

	// Call func2 with list, right parameter count
	auto ret1 = func1.invoke(argSingle);
	ASSERT_FALSE(ret1.IsNull());
	ASSERT_TRUE(ret1.InstanceOf<int>());
	ASSERT_EQ(ret1.Get<int>(), 3);


	// Call func2 with no arguments, should return object::null
	ASSERT_TRUE(func2.invoke().IsNull());
	
	// Call func2 with primitive object, should return object:null
	ASSERT_TRUE(func2.invoke(argSingle).IsNull());

	// Call func2 with list, but wrong parameter count, should return object:null
	ASSERT_TRUE(func2.invoke(argList2).IsNull());

	// Call func2 with list, right parameter count
	auto ret2 = func2.invoke(argList1);
	ASSERT_FALSE(ret2.IsNull());
	ASSERT_TRUE(ret2.InstanceOf<int>());
	ASSERT_EQ(ret2.Get<int>(), 5);

	// Test with bound member function
	objectTest::TestClass testClass;
	auto func3 = basyx::object::make_function(&objectTest::TestClass::testFunc, &testClass);
	
	auto ret3 = func3.invoke(argList1);
	ASSERT_FALSE(ret3.IsNull());
	ASSERT_TRUE(ret3.InstanceOf<bool>());
	ASSERT_EQ(ret3.Get<bool>(), true);
}


TEST_F(TestBaSyxObject, ObjectHashTest)
{
	auto map1 = basyx::object::make_map();
	auto map2 = basyx::object::make_map();
	basyx::object objInt = 5;


	std::hash<basyx::object> hash;
	ASSERT_EQ(hash(map1), hash(map1));
	ASSERT_EQ(hash(map2), hash(map2));
	ASSERT_EQ(hash(objInt), hash(objInt));

	ASSERT_NE(hash(map1), hash(map2));
	ASSERT_NE(hash(map1), hash(objInt));
}