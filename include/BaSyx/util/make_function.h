/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef UTILITY_UTIL_MAKE_FUNCTION_H
#define UTILITY_UTIL_MAKE_FUNCTION_H

#include <functional>

// make_function:
// --------------
// utility function creating std::function objects, by automatically deducing type signatures

namespace util {

// function pointers
template <typename RetType, typename... Args>
auto make_function(RetType (*f)(Args...)) -> std::function<RetType(Args...)>
{
    return { f };
};

// member functions
template <typename Class, typename RetType, typename... Args>
auto make_function(RetType (Class::*f)(Args...)) -> std::function<RetType(Args...)>
{
    return { f };
};

// bound member function, 0 arguments
template <typename Object, typename RetType>
auto make_function(RetType (Object::*f)(void), Object* o) -> std::function<RetType(void)>
{
    return std::function<RetType(void)>( std::bind(f, o) );
};

// bound member function, 1 arguments
template <typename Object, typename RetType, typename Arg>
auto make_function(RetType(Object::*f)(Arg), Object* o) -> std::function<RetType(Arg)>
{
	return std::function<RetType(Arg)>(std::bind(f, o, std::placeholders::_1));
};

// bound member function, 2 arguments
template <typename Object, typename RetType, typename... Args>
auto make_function(RetType(Object::*f)(Args...), Object* o) -> std::function<RetType(Args...)>
{
	return std::function<RetType(Args...)>(std::bind(f, o, std::placeholders::_1, std::placeholders::_2));
};


template <typename Class, typename RetType, typename... Args>
auto make_function(RetType (Class::*f)(Args...) const) -> std::function<RetType(Args...)>
{
    return { f };
}

// lambda functions
template <typename T, typename Arg, typename... Args>
auto make_function(T && t) -> std::function<decltype(t(std::declval<Arg>(), std::declval<Args>()...))(Arg, Args...)>
{
    return { std::forward<T>(t) };
}

template <typename T>
auto make_function(T && t) -> decltype(make_function(&std::remove_reference<T>::type::operator()))
{
    return { std::forward<T>(t) };
}


};

#endif /* UTILITY_UTIL_MAKE_FUNCTION_H */
