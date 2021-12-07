/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include "SimpleVABElement.h"

#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>

#include <set>

namespace basyx {
namespace tests {
namespace support {

class testFuncs {
public:
	static uint64_t add(uint64_t a, uint64_t b) {
		return a + b;
	}
};

basyx::object make_simple_vab_element()
{
	basyx::object vabElement = basyx::object::make_map();

	// Add primivites
	vabElement.insertKey("primitives", basyx::object::make_map());
	vabElement.getProperty("primitives").insertKey("integer", uint64_t{ 123 });
	vabElement.getProperty("primitives").insertKey("double", 3.14);
	vabElement.getProperty("primitives").insertKey("string", std::string("TestValue"));

	// Add function types
	vabElement.insertKey("operations", basyx::object::make_map());
	vabElement.getProperty("operations").insertKey("supplier", basyx::object::make_function([]() {return true; }));
	vabElement.getProperty("operations").insertKey("complex", basyx::object::make_function(testFuncs::add));
	vabElement.getProperty("operations").insertKey("serializable", basyx::object::make_function(testFuncs::add));

	vabElement.getProperty("operations").insertKey("invalid", true);
	vabElement.getProperty("operations").insertKey("invokable", basyx::object::make_function([]() {return true; }));

	// Add structure types
	vabElement.insertKey("structure", basyx::object::make_map());
	vabElement.getProperty("structure").insertKey("map", basyx::object::make_map());
	//		vabElement.getProperty("structure").insertKey("set", basyx::object::make_set<bool>());
	vabElement.getProperty("structure").insertKey("list", basyx::object::make_list<uint64_t>());

	// Add corner cases
	vabElement.insertKey("special", basyx::object::make_map());
	vabElement.getProperty("special").insertKey("casesensitivity", true);
	vabElement.getProperty("special").insertKey("caseSensitivity", false);
	vabElement.getProperty("special").insertKey("nested", basyx::object::make_map());
	vabElement.getProperty("special").getProperty("nested").insertKey("nested", basyx::object::make_map());
	vabElement.getProperty("special").getProperty("nested").getProperty("nested").insertKey("value", uint64_t{ 100 });
	vabElement.getProperty("special").insertKey("null", basyx::object::make_null());

	return vabElement;
}

}
}
}
