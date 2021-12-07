/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJECT_TYPE_H
#define BASYX_SHARED_OBJECT_OBJECT_TYPE_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

template<typename T>
struct dataTypeMapper
{

};

template<>
struct dataTypeMapper<float>
{
	static constexpr char datatype_string[] = "float";
};

template<>
struct dataTypeMapper<int>
{
	static constexpr char datatype_string[] = "integer";
};

namespace basyx {

// Forward declarations
class object;

namespace detail {
	class functionWrapper;
};

namespace type {

	enum class objectType {
		Primitive,
		List,
		Map,
		Function,
		Error
	};

	enum class valueType {
		Bool,
		Int,
		Float,
		String,
		Object,
		Null
	};

	template<typename T, typename Enable = void>
	struct basyx_type
	{
		static constexpr int fail_vab_type_not_supported() { static_assert(std::is_fundamental<T>::value && !std::is_fundamental<T>::value, "Type not supported by VAB!"); return 0; };
		static constexpr basyx::type::objectType object_type = static_cast<basyx::type::objectType>(fail_vab_type_not_supported());
		static constexpr basyx::type::valueType value_type = static_cast<basyx::type::valueType>(fail_vab_type_not_supported());
	};

	// Specialization for nullptr_t
	template <>
	struct basyx_type<std::nullptr_t>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Primitive;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::Null;
	};

	// Specialization for bool
	template <>
	struct basyx_type<bool>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Primitive;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::Bool;
	};

	// Specialization for std::string
	template <>
	struct basyx_type<std::string>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Primitive;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::String;
	};

	// Specialization for integer types
	template <typename Integer>
	struct basyx_type<Integer, typename std::enable_if<std::is_integral<Integer>::value>::type>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Primitive;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::Int;
	};	
	
	// Specialization for float types
	template <typename Float>
	struct basyx_type<Float, typename std::enable_if<std::is_floating_point<Float>::value>::type>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Primitive;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::Float;
	};

	// Specialization for bool
	template <>
	struct basyx_type<basyx::object>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Primitive;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::Object;
	};

	// Specialization for std::vector
	template <typename T>
	struct basyx_type<std::vector<T>>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::List;
		static constexpr basyx::type::valueType value_type = basyx::type::basyx_type<T>::value_type;
	};

	// Specialization for std::unordered_map
	template <typename T>
	struct basyx_type<std::unordered_map<std::string, T>>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Map;
		static constexpr basyx::type::valueType value_type = basyx::type::basyx_type<T>::value_type;
	};

	// Specialization for function
	template <>
	struct basyx_type<basyx::detail::functionWrapper>
	{
		static constexpr basyx::type::objectType object_type = basyx::type::objectType::Function;
		static constexpr basyx::type::valueType value_type = basyx::type::valueType::Object;
	};	
	
	// Definitions
	template<typename T, typename Enable>
	constexpr basyx::type::objectType basyx_type<T, Enable>::object_type;

	template<typename T, typename Enable>
	constexpr basyx::type::valueType basyx_type<T, Enable>::value_type;

	template <typename Integer>
	constexpr basyx::type::objectType basyx_type<Integer, typename std::enable_if<std::is_integral<Integer>::value>::type>::object_type;

	template <typename Integer>
	constexpr basyx::type::valueType basyx_type<Integer, typename std::enable_if<std::is_integral<Integer>::value>::type>::value_type;

	template <typename Float>
	constexpr basyx::type::objectType basyx_type<Float, typename std::enable_if<std::is_floating_point<Float>::value>::type>::object_type;

	template <typename Float>
	constexpr basyx::type::valueType basyx_type<Float, typename std::enable_if<std::is_floating_point<Float>::value>::type>::value_type;

	template <typename T>
	constexpr basyx::type::valueType basyx_type<std::unordered_map<std::string, T>>::value_type;

	template <typename T>
	constexpr basyx::type::objectType basyx_type<std::unordered_map<std::string, T>>::object_type;

	template <typename T>
	constexpr basyx::type::valueType basyx_type<std::vector<T>>::value_type;

	template <typename T>
	constexpr basyx::type::objectType basyx_type<std::vector<T>>::object_type;
};
};

namespace util {
	// to_string function for basyx::type::valueType
	template<basyx::type::valueType ValueType>
	std::string to_string();

	template<> inline std::string to_string<basyx::type::valueType::Null>()   { return "Null"; };
	template<> inline std::string to_string<basyx::type::valueType::Bool>()   { return "Boolean"; };
	template<> inline std::string to_string<basyx::type::valueType::Int>()    { return "Integer"; };
	template<> inline std::string to_string<basyx::type::valueType::Float>()  { return "Float"; };
	template<> inline std::string to_string<basyx::type::valueType::String>() { return "String"; };
	template<> inline std::string to_string<basyx::type::valueType::Object>() { return "Object"; };
}

#endif /* BASYX_SHARED_OBJECT_OBJECT_TYPE_H */
