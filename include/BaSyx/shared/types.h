/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/* ************************************************************************************************
 * BaSys Type System
 *
 * Define type IDs
 * ************************************************************************************************/

#ifndef BASYX_SHARED_TYPES_H
#define BASYX_SHARED_TYPES_H

#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

namespace basyx {

  template<typename T>
    using specificCollection_t = std::vector<std::shared_ptr<T>>;

  template<typename T>
   using specificMap_t = std::unordered_map<std::string, std::shared_ptr<T >> ;

	enum class BaseType
	{
		Primitive,
		HashMap,
		Set,
		List
	};

	enum class ValueType
	{
		Bool,
		Int,
		Float,
		String
	};
};

enum class BaSyxCommand : uint8_t {
	None = 0x0,
	Get = 0x1,
	Set = 0x2,
	Create = 0x3,
	Delete = 0x4,
	Invoke = 0x5,
	Invalid = 0xFF,
};

#define BASYX_FRAMESIZE_SIZE 4
#define BASYX_STRINGSIZE_SIZE 4

#endif /* BASYX_SHARED_TYPES_H */
