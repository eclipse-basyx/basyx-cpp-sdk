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

#include <string>
#include <cstdint>

#include <BaSyx/util/function_traits.h>
#include <BaSyx/util/make_function.h>

// anonymous namespace for local test function definitions
namespace
{
	int add(int a, int b)
	{
		return a + b;
	};

	float addFloat(int a, float f, char dummy)
	{
		return a + f;
	};

	std::string const_func()
	{
		return "42";
	};

	class testClass
	{
	public:
		int a, b;
		testClass(int _a, int _b) : a(_a), b(_b) {};

		int process() { return a + b; };
		int add(int c) { return a + b + c; };
		static int inc(int a) { return a + 1; };
	};
}

class TestBaSyxMakeFunction : public ::testing::Test
{

};


TEST_F(TestBaSyxMakeFunction, SimpleFunctionTest)
{
	// test: add
	auto funcAdd = util::make_function(add);

	static_assert(util::function_traits<decltype(funcAdd)>::args_n == 2, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(funcAdd)>::result_type, int>::value, "Return types differ:");
	static_assert(std::is_same<util::function_traits<decltype(funcAdd)>::arg_at<0>::type, int>::value, "Argument types differ:");
	static_assert(std::is_same<util::function_traits<decltype(funcAdd)>::arg_at<1>::type, int>::value, "Argument types differ:");

	ASSERT_EQ(funcAdd(0, 0), 0);
	ASSERT_EQ(funcAdd(1, 2), 3);

	// test: addFloat
	auto funcAddF = util::make_function(addFloat);

	static_assert(util::function_traits<decltype(funcAddF)>::args_n == 3, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(funcAddF)>::result_type, float>::value, "Return types differ:");
	static_assert(std::is_same<util::function_traits<decltype(funcAddF)>::arg_at<0>::type, int>::value, "Argument types differ:");
	static_assert(std::is_same<util::function_traits<decltype(funcAddF)>::arg_at<1>::type, float>::value, "Argument types differ:");
	static_assert(std::is_same<util::function_traits<decltype(funcAddF)>::arg_at<2>::type, char>::value, "Argument types differ:");

	ASSERT_EQ(funcAdd(0, 0), 0);
	ASSERT_EQ(funcAdd(1, 2), 3);

	// test: const_func
	auto funcConst = util::make_function(const_func);

	static_assert(util::function_traits<decltype(funcConst)>::args_n == 0, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(funcConst)>::result_type, std::string>::value, "Return types differ:");

	ASSERT_EQ(funcConst() , "42" );

	// test static member function
	auto funcStatic = util::make_function(testClass::inc);

	static_assert(util::function_traits<decltype(funcStatic)>::args_n == 1, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(funcStatic)>::result_type, int>::value, "Return types differ:");
	static_assert(std::is_same<util::function_traits<decltype(funcStatic)>::arg_at<0>::type, int>::value, "Argument types differ:");

	ASSERT_EQ(funcStatic(3), 4);
}

TEST_F(TestBaSyxMakeFunction, LambdaTest)
{
	// no arguments
	auto lambda_1 = util::make_function([]() { return 1; });

	static_assert(util::function_traits<decltype(lambda_1)>::args_n == 0, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(lambda_1)>::result_type, int>::value, "Return types differ:");

	ASSERT_EQ(lambda_1(), 1);	

	// multiple arguments
	auto lambda_2 = util::make_function([](int a, float b, char c) { return a; });

	static_assert(util::function_traits<decltype(lambda_2)>::args_n == 3, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(lambda_2)>::result_type, int>::value, "Return types differ:");
	static_assert(std::is_same<util::function_traits<decltype(lambda_2)>::arg_at<0>::type, int>::value, "Argument types differ:");
	static_assert(std::is_same<util::function_traits<decltype(lambda_2)>::arg_at<1>::type, float>::value, "Argument types differ:");
	static_assert(std::is_same<util::function_traits<decltype(lambda_2)>::arg_at<2>::type, char>::value, "Argument types differ:");

	ASSERT_EQ(lambda_2(2, 3.0f, 'C'), 2);

	// test with lambda capture
	int test_int = 2;
	auto lambda_3 = util::make_function([test_int](int a) { return a + test_int; });

	static_assert(util::function_traits<decltype(lambda_3)>::args_n == 1, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(lambda_3)>::result_type, int>::value, "Return types differ:");
	static_assert(std::is_same<util::function_traits<decltype(lambda_3)>::arg_at<0>::type, int>::value, "Argument types differ:");

	ASSERT_EQ(lambda_3(1), 3);

	// test with lambda closure, capturing by-ref
	auto lambda_4 = util::make_function([&test_int](int a) { test_int = a; });

	static_assert(util::function_traits<decltype(lambda_3)>::args_n == 1, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(lambda_4)>::result_type, void>::value, "Return types differ:");
	static_assert(std::is_same<util::function_traits<decltype(lambda_4)>::arg_at<0>::type, int>::value, "Argument types differ:");

	// call func
	lambda_4(5);
	ASSERT_EQ(test_int, 5);
}


TEST_F(TestBaSyxMakeFunction, MemberFunctionTest)
{
	testClass obj(2,3);

	auto func = util::make_function(&testClass::process, &obj);

	static_assert(util::function_traits<decltype(func)>::args_n == 0, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(func)>::result_type, int>::value, "Return types differ:");

	// call func
	ASSERT_EQ(func(), 5);
}

TEST_F(TestBaSyxMakeFunction, MemberFunctionTest2)
{
	testClass obj(2, 3);

	auto func = util::make_function(&testClass::add, &obj);

	static_assert(util::function_traits<decltype(func)>::args_n == 1, "Parameter count differs");
	static_assert(std::is_same<util::function_traits<decltype(func)>::result_type, int>::value, "Return types differ:");

	// call func
	ASSERT_EQ(func(4), 9 );
}
