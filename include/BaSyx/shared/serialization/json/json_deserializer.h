/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_SERIALIZATION_JSON_JSON_DESERIALIZER_H
#define BASYX_SHARED_SERIALIZATION_JSON_JSON_DESERIALIZER_H

#include <nlohmann/json.hpp>

#include <BaSyx/shared/object/object_header.h>
#include <BaSyx/shared/types.h>

#include "typeid.h"

namespace basyx {
namespace serialization {
namespace json {
    using json_t = nlohmann::json;

    // This class handles the actual deserialization of the BaSyx JSON format
    // Assumes that every JSON is well formed and adheres to the VAB serialization standard
    class deserialize_helper {
    public:
        static basyx::object deserialize(const json_t& json)
        {
            // Get the basystype
            // auto basysType = json[basyx::serialization::typeSpecifier].get<std::string>();

            if (json.is_primitive()) {
                return deserialize_helper::fundamental(json);
            } 
			// deserialize list
			else if( json.is_array()) 
			{
				return deserialize_helper::list(json);
			}
			// deserialize objectMap
			else if (json.is_object()) 
			{
				return basyx::object{ std::forward<basyx::object::object_map_t>(deserialize_helper::objectMap(json)) };
            } 

			return basyx::object::make_null();
        }

    private:
        // Deserialize a fundamental type (and std::string) from JSON and return a basyx::object object holding the deserialized value
        static basyx::object fundamental(const json_t& json)
        {
			if (json.is_number_float())
				return basyx::object{ json.get<double>() };
			else if (json.is_number_integer())
				return basyx::object{ json.get<uint64_t>() };
			else if (json.is_boolean())
				return basyx::object{ json.get<bool>() };
            else if (json.is_string())
                return basyx::object { json.get<std::string>() };

            return basyx::object::make_null();
        }

		static basyx::type::valueType check_array_type(const json_t & json)
		{
			basyx::type::valueType last_type = basyx::type::valueType::Null;
			basyx::type::valueType current_type = basyx::type::valueType::Null;

			for (const auto& val : json) {
				if (val.is_boolean()) {
					current_type = basyx::type::valueType::Bool;
				}
				else if (val.is_number_integer()) {
					current_type = basyx::type::valueType::Int;
				}
				else if (val.is_number_float()) {
					current_type = basyx::type::valueType::Float;
				}
				else if (val.is_string()) {
					current_type = basyx::type::valueType::String;
				};

				if ( last_type != basyx::type::valueType::Null && current_type != last_type)
					return basyx::type::valueType::Object;

				last_type = current_type;
			}

			return last_type;
		};

		static basyx::object list(const json_t & json_array)
		{
			if (json_array.empty())
				return basyx::object::object_list_t();

			if (json_array.is_array())
			{
				auto value_type = check_array_type(json_array);

				switch (value_type)
				{
				case basyx::type::valueType::Bool:
					return deserialize_helper::list_t<bool>(json_array);
				case basyx::type::valueType::Int:
					return deserialize_helper::list_t<uint64_t>(json_array);
				case basyx::type::valueType::String:
					return deserialize_helper::list_t<std::string>(json_array);
				case basyx::type::valueType::Float:
					return deserialize_helper::list_t<double>(json_array);
				case basyx::type::valueType::Object:
					return deserialize_helper::object_list(json_array);
                default:
                    break;
				};
			}

			return basyx::object::make_null();
		};

        static basyx::object object_list(const json_t& json)
        {
            basyx::object::object_list_t objectList;

            for (const auto& val : json) {
                objectList.push_back(deserialize(val));
            }

            return objectList;
		}

		template<typename T>
		static basyx::object list_t(const json_t & json)
		{
			basyx::object list = basyx::object::make_list<T>();

			for (const auto& val : json) {
				list.insert(deserialize(val));
			}

			return list;
		};

        // Deserializes an objectMap from the given JSON
        static basyx::object::object_map_t objectMap(const json_t& json)
        {
            //auto size = json[basyx::serialization::sizeSpecifier].get<std::size_t>();
            auto size = json.size();

            basyx::object::object_map_t objectMap { size };

            for (const auto& element : json.items()) {
                objectMap.emplace(element.key(), deserialize(element.value()));
            };

            return objectMap;
        }
    };
};
};
};

#endif /* BASYX_SHARED_SERIALIZATION_JSON_JSON_DESERIALIZER_H */
