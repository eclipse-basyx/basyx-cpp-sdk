/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/typesmap/TypesTransformer.h>

namespace basyx
{
	namespace opcua
	{
		std::tuple<std::string, std::string> TypesTransformer::unpackValuePair(basyx::object t_object)
		{
			if (t_object.InstanceOf<basyx::object::object_map_t>())
			{
				auto objMap = basyx::object::object_cast<basyx::object::object_map_t>(t_object);

				if ((objMap.size() > 1) && (objMap.size() <= 2))
				{
					if (objMap.count(TypesMap::TypeKeys::Value) &&
						objMap.count(TypesMap::TypeKeys::ValueType))
					{
						auto value = basyx::object::object_cast<std::string>(
							objMap.at(TypesMap::TypeKeys::Value)
							);

						auto valueType = basyx::object::object_cast<std::string>(
							objMap.at(TypesMap::TypeKeys::ValueType)
							);

						return std::make_tuple(value, valueType);
					}
				}
			}
			return std::make_tuple(std::string(), std::string());
		}

		bool TypesTransformer::isTypeEncapsulated(basyx::object t_object)
		{
			if (t_object.InstanceOf<basyx::object::object_map_t>())
			{
				auto objMap = basyx::object::object_cast<basyx::object::object_map_t>(t_object);

				if ((objMap.size() > 1) && (objMap.size() <= 2))
				{
					if (objMap.count(TypesMap::TypeKeys::Value) &&
						objMap.count(TypesMap::TypeKeys::ValueType))
					{
						auto valueType = basyx::object::object_cast<std::string>(
							objMap.at(TypesMap::TypeKeys::ValueType)
							);

						return TypesMap::Type::Unknown != TypesMap::fromString(valueType);
					}
				}
			}
			return false;
		}

		basyx::object TypesTransformer::packValuePair(const std::string& t_value, TypesMap::Type t_type)
		{
			auto retObj = basyx::object::make_map();

			retObj.insertKey(TypesMap::TypeKeys::Value, t_value);
			retObj.insertKey(TypesMap::TypeKeys::ValueType, TypesMap::toString(t_type));

			return retObj;
		}

		bool TypesTransformer::areTypeEmbeddedObjectsEqual(basyx::object t_object_1, basyx::object t_object_2)
		{
			if (isTypeEncapsulated(t_object_1) && isTypeEncapsulated(t_object_2))
			{
				return (t_object_1 == t_object_2);
			}
			return false;
		}

		template<>
        bool TypesTransformer::string_cast<bool>(const std::string& t_value)
        {
            return ((t_value == "true") || (t_value == "1"));
        }

		template<>
		int8_t TypesTransformer::string_cast<int8_t>(const std::string& t_value)
		{
			return  static_cast<int8_t>(std::stol(t_value));
		}

		template<>
		int16_t TypesTransformer::string_cast<int16_t>(const std::string& t_value)
		{
			return  static_cast<int16_t>(std::stol(t_value));
		}

		template<>
		int32_t TypesTransformer::string_cast<int32_t>(const std::string& t_value)
		{
			return  static_cast<int32_t>(std::stol(t_value));
		}

		template<>
		int64_t TypesTransformer::string_cast<int64_t>(const std::string& t_value)
		{
			return strtoll(t_value.c_str(), NULL, 10);
		}

		template<>
		uint8_t TypesTransformer::string_cast<uint8_t>(const std::string& t_value)
		{
			return  static_cast<uint8_t>(std::stoul(t_value));
		}

		template<>
		uint16_t TypesTransformer::string_cast<uint16_t>(const std::string& t_value)
		{
			return  static_cast<uint16_t>(std::stoul(t_value));
		}

		template<>
		uint32_t TypesTransformer::string_cast<uint32_t>(const std::string& t_value)
		{
			return  static_cast<uint32_t>(std::stoul(t_value));
		}

		template<>
		uint64_t TypesTransformer::string_cast<uint64_t>(const std::string& t_value)
		{
			return  strtoull(t_value.c_str(), NULL, 10);
		}

		template<>
		float TypesTransformer::string_cast<float>(const std::string& t_value)
		{
			return  static_cast<float>(std::stof(t_value));
		}

		template<>
		double TypesTransformer::string_cast<double>(const std::string& t_value)
		{
			return  static_cast<double>(std::stod(t_value));
		}

		template<>
		std::string TypesTransformer::numeral_cast<bool>(bool t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<int8_t>(int8_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<uint8_t>(uint8_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<int16_t>(int16_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<uint16_t>(uint16_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<int32_t>(int32_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<uint32_t>(uint32_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<int64_t>(int64_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<uint64_t>(uint64_t t_value)
		{
			return std::to_string(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<float>(float t_value)
		{
			return stringFloating(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<double>(double t_value)
		{
			return stringFloating(t_value);
		}

		template<>
		std::string TypesTransformer::numeral_cast<std::string>(std::string t_value)
		{
			return t_value;
		}
	}
}