/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <string>

// util::make_unique
// Based on official std::make_unique proposal https://isocpp.org/files/papers/N3656.txt
// by Stephan T. Lavavej <stl@microsoft.com>

namespace util {
	namespace detail {
		template<typename T> 
		struct unique_if
		{
			using single_object = std::unique_ptr<T>;
		};

		template<typename T> 
		struct unique_if<T[]> 
		{
			using unbounded_array = std::unique_ptr<T[]>;
		};

		template<typename T, std::size_t N> 
		struct unique_if<T[N]> 
		{
			using bounded_array = void;
		};
	}

	template<typename T, typename... Args>
	typename detail::unique_if<T>::single_object make_unique(Args && ... args) 
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	};

	template<typename T>
	typename detail::unique_if<T>::unbounded_array make_unique(std::size_t n)
	{
		using ArrayType = typename std::remove_extent<T>::type;
		return std::unique_ptr<T>(new ArrayType[n]());
	};

	template<typename T, typename... Args>
	typename detail::unique_if<T>::bounded_array make_unique(Args && ...) = delete;

	template<class Int, Int... Ints>
	struct integer_sequence
	{
		static_assert(std::is_integral<Int>::value, "util::integer_sequence<Int, Ints...>: 'Int' must be integral type!");

		static constexpr size_t size() noexcept
		{	
			return (sizeof...(Ints));
		}
	};

	template<class N> 
	struct next_integer_sequence;

	template<typename Int, Int... Ints> 
	struct next_integer_sequence<integer_sequence<Int, Ints...>>
	{
		using type = integer_sequence<Int, Ints..., sizeof...(Ints)>;
	};
	
	template<class T, T I, T N>
	struct make_int_seq_impl;

	template<class T, T N>
	using make_integer_sequence = typename make_int_seq_impl<T, 0, N>::type;

	template<class T, T I, T N> struct make_int_seq_impl
	{
		using type = typename next_integer_sequence<
			typename make_int_seq_impl<T, I + 1, N>::type>::type;
	};

	template<class T, T N> struct make_int_seq_impl<T, N, N>
	{
		using type = integer_sequence<T>;
	};


	template<std::size_t... Ints>
	using index_sequence = util::integer_sequence<std::size_t, Ints...>;

	template<size_t Size>
	using make_index_sequence = util::make_integer_sequence<size_t, Size>;
}

namespace util {
	//template<typename T>
	//const std::string & to_string(const T && t) = delete;

	template<typename T>
	T from_string(const std::string & str) = delete;
}

namespace util {


#ifdef USE_STD_DECAY_T
	template<typename T>
	using decay_t = std::decay_t<T>;
#else
	template<typename T>
	using decay_t = typename std::decay<T>::type;
#endif
}


#endif