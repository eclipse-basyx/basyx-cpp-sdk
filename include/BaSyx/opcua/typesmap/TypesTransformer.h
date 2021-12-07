/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef TYPES_TRANSFORMER_H
#define TYPES_TRANSFORMER_H

#include <tuple>
#include <sstream>
#include <BaSyx/log/log.h>
#include <BaSyx/shared/object.h>
#include <BaSyx/opcua/typesmap/TypesMap.h>
#include <BaSyx/shared/serialization/json.h>

namespace basyx {
namespace opcua {

class TypesTransformer
{
public:
	static constexpr const int VALUE_KEY_IDX = 0;
	static constexpr const int VALUE_TYPE_KEY_IDX = 1;

	template<typename TYPE>
	static TYPE string_cast(const std::string& t_value);

	template<typename TYPE>
	static std::string numeral_cast(TYPE t_value);

	template<typename TYPE>
	static constexpr TypesMap::Type getTypeEnum(TYPE t_value)
	{
		static_assert(TypesMap::VABExtendedTypeInclusion<TYPE>::condition, "Type not supported ");

		return (typeid(t_value) == typeid(signed char)) ?
				TypesMap::Type::Int8 : (
				(typeid(t_value) == typeid(uint8_t) ?
				TypesMap::Type::UInt8 : (
				(typeid(t_value) == typeid(signed short) ?
				TypesMap::Type::Int16 : (
				(typeid(t_value) == typeid(uint16_t) ?
				TypesMap::Type::UInt16 : (
				(typeid(t_value) == typeid(signed int) ?
				TypesMap::Type::Int32 : (
				(typeid(t_value) == typeid(uint32_t) ?
				TypesMap::Type::UInt32 : (
				(typeid(t_value) == typeid(int64_t) ?
				TypesMap::Type::Int64 : (
				(typeid(t_value) == typeid(uint64_t) ?
				TypesMap::Type::UInt64 : (
				(typeid(t_value) == typeid(float) ?
				TypesMap::Type::Float : (
				(typeid(t_value) == typeid(double) ?
				TypesMap::Type::Double : (
				(typeid(t_value) == typeid(std::string) ?
				TypesMap::Type::String : TypesMap::Type::Unknown
			))))))))))))))))))));
	}

	template<typename TYPE>
	static std::string stringFloating(TYPE t_value)
	{
		std::ostringstream outValueStr;
		/* opts the best available precision */
		outValueStr.precision(std::numeric_limits<TYPE>::digits10);

		outValueStr << std::fixed << t_value;

		return outValueStr.str();
	}

	template<typename TYPE>
	static basyx::object objectWithMeta(TYPE t_value)
	{
		static_assert(TypesMap::VABExtendedTypeInclusion<TYPE>::condition, "Type not supported ");

		return packValuePair(numeral_cast(t_value), getTypeEnum(t_value));
	}

	static std::tuple<std::string, std::string> unpackValuePair(basyx::object t_object);

	static bool isTypeEncapsulated(basyx::object t_object);

	static basyx::object packValuePair(const std::string& t_value, TypesMap::Type t_type);

	static bool areTypeEmbeddedObjectsEqual(basyx::object t_object_1, basyx::object t_object_2);
};

template<>
	bool TypesTransformer::string_cast<bool>(const std::string& t_value);

	template<>
	int8_t TypesTransformer::string_cast<int8_t>(const std::string& t_value);

	template<>
	int16_t TypesTransformer::string_cast<int16_t>(const std::string& t_value);

	template<>
	int32_t TypesTransformer::string_cast<int32_t>(const std::string& t_value);

	template<>
	int64_t TypesTransformer::string_cast<int64_t>(const std::string& t_value);

	template<>
	uint8_t TypesTransformer::string_cast<uint8_t>(const std::string& t_value);

	template<>
	uint16_t TypesTransformer::string_cast<uint16_t>(const std::string& t_value);

	template<>
	uint32_t TypesTransformer::string_cast<uint32_t>(const std::string& t_value);

	template<>
	uint64_t TypesTransformer::string_cast<uint64_t>(const std::string& t_value);

	template<>
	float TypesTransformer::string_cast<float>(const std::string& t_value);

	template<>
	double TypesTransformer::string_cast<double>(const std::string& t_value);

	template<>
	std::string TypesTransformer::numeral_cast<bool>(bool t_value);

	template<>
	std::string TypesTransformer::numeral_cast<signed char>(signed char t_value);

	template<>
	std::string TypesTransformer::numeral_cast<uint8_t>(uint8_t t_value);

	template<>
	std::string TypesTransformer::numeral_cast<signed short>(signed short t_value);

	template<>
	std::string TypesTransformer::numeral_cast<uint16_t>(uint16_t t_value);

	template<>
	std::string TypesTransformer::numeral_cast<signed int>(signed int t_value);

	template<>
	std::string TypesTransformer::numeral_cast<uint32_t>(uint32_t t_value);

	template<>
	std::string TypesTransformer::numeral_cast<int64_t>(int64_t t_value);

	template<>
	std::string TypesTransformer::numeral_cast<uint64_t>(uint64_t t_value);

	template<>
	std::string TypesTransformer::numeral_cast<float>(float t_value);

	template<>
	std::string TypesTransformer::numeral_cast<double>(double t_value);

	template<>
	std::string TypesTransformer::numeral_cast<std::string>(std::string t_value);
  }
}

#endif