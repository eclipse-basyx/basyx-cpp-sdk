/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_SERIALIZATION_JSON_JSON_SERIALIZER_H
#define BASYX_SHARED_SERIALIZATION_JSON_JSON_SERIALIZER_H

#include <nlohmann/json.hpp>

#include <BaSyx/shared/object/object_header.h>
#include <BaSyx/shared/types.h>


namespace basyx {
namespace serialization {
namespace json {
    using json_t = nlohmann::json;
    // Unknown type serializer
    // Throw static assertion at compile time
    // signaling that no basyx serializer for this type exists
    //template<typename T>
    //void serialize_helper(json_t & json, const T &, typename std::enable_if<!std::is_fundamental<T>::value, T>::type = 0) {
    //	static_assert(false, "No basyx serialization for type exists!");
    //};

    // Fundamental type serializer
    // int, float, double, char, etc.
    template <typename T>
    //		inline void serialize_helper(json_t & json, const T & value, typename std::enable_if<std::is_fundamental<T>::value, T>::type = 0) {
    inline void serialize_helper(json_t& json, const T& value)
    {
        json = value;
    };

    // std::string serializer
    inline void serialize_helper(json_t& json, const std::string& string)
    {
        json = string;
    };

    // basyx::object serializer
	inline void serialize_helper(json_t& json, const basyx::object& object)
	{
        json = object;
    };

	template<typename T>
	inline void serialize_helper(json_t & json, const basyx::object::list_t<T> & list)
	{
		json = list ;
	};

    // basyx::object::object_map_t serializer
    inline void serialize_helper(json_t& json, const basyx::object::object_map_t & objectMap)
    {
		// Initialize as valid json object, even if map is empty
		json = objectMap;
    }
};
};
};

#endif /* BASYX_SHARED_SERIALIZATION_JSON_JSON_SERIALIZER_H */
