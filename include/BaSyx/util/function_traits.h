/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef UTILITY_UTIL_FUNCTION_TRAITS_H
#define UTILITY_UTIL_FUNCTION_TRAITS_H

#include <functional>

namespace util
{

template<typename T>
struct function_traits;

template<typename RetType, typename... Args>
struct function_traits<std::function<RetType(Args...)>>
{
	static const std::size_t args_n = sizeof...(Args);

	using result_type = RetType;
	using argument_type = std::tuple<Args...>;

	template <std::size_t n>
	struct arg_at
	{
		using type = typename std::tuple_element<n, std::tuple<Args...>>::type;
	};
};

}

#endif /* UTILITY_UTIL_FUNCTION_TRAITS_H */
