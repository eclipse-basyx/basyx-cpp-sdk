/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef _MAPCREATEDELETE_H
#define _MAPCREATEDELETE_H

#include <gtest/gtest.h>

#include <BaSyx/shared/types.h>

#include <BaSyx/vab/core/IModelProvider.h>

#include "macros.h"


namespace basyx {
namespace tests {
namespace regression {
namespace vab {
namespace snippet {

class MapCreateDelete {
public:
	static void test(basyx::vab::core::IModelProvider * modelProvider)
	{
		testCreateElements(modelProvider);
		testDeleteElements(modelProvider);
	}
private:
	static void testCreateElements(basyx::vab::core::IModelProvider * modelProvider)
	{
		// Create property directly in root element
		modelProvider->createValue("inRoot", 1.2);
		basyx::object toTest = modelProvider->getModelPropertyValue("inRoot");
		ASSERT_ANY_EQ(toTest, 1.2);

		// Create element in Map (with new key contained in the path)
		modelProvider->createValue("/structure/map/inMap", std::string{ "34" });
		toTest = modelProvider->getModelPropertyValue("/structure/map/inMap");
		ASSERT_ANY_EQ(toTest, std::string{ "34" });

		// Create map element
		basyx::object::object_map_t newMap;
		newMap.emplace("entryA", uint64_t{ 3 });
		newMap.emplace("entryB", uint64_t{ 4 });
		modelProvider->createValue("mapInRoot", newMap);
		toTest = modelProvider->getModelPropertyValue("mapInRoot");

		ASSERT_TRUE(toTest.InstanceOf<basyx::object::object_map_t>());
		ASSERT_EQ(toTest.Get<basyx::object::object_map_t&>().size(), 2);
		ASSERT_ANY_EQ(toTest.Get<basyx::object::object_map_t&>().at("entryA"), uint64_t{ 3 });

		// Try to overwrite existing element (should throw Exception, already exists)
		auto overwriteError = modelProvider->createValue("inRoot", 0);
		ASSERT_EQ(overwriteError, basyx::object::error::ObjectAlreadyExists);
		toTest = modelProvider->getModelPropertyValue("inRoot");
		ASSERT_ANY_EQ(toTest, 1.2);

		// Check case-sensitivity
		modelProvider->createValue("inroot", uint64_t{ 78 });
		toTest = modelProvider->getModelPropertyValue("inRoot");
		ASSERT_ANY_EQ(toTest, 1.2);
		toTest = modelProvider->getModelPropertyValue("inroot");
		ASSERT_ANY_EQ(toTest, uint64_t{ 78 });

		// Non-existing parent element
		modelProvider->createValue("unkown/x", 5);
		toTest = modelProvider->getModelPropertyValue("unknown/x");
		ASSERT_TRUE(toTest.IsNull());
		ASSERT_TRUE(toTest.IsError());
		ASSERT_EQ(toTest.getError(), basyx::object::error::PropertyNotFound);

		// Empty paths - should execute, but has no effect
		auto emptyPathError = modelProvider->createValue("", std::string(""));
		ASSERT_EQ(emptyPathError, basyx::object::error::ObjectAlreadyExists);
	}

	static void testDeleteElements(basyx::vab::core::IModelProvider * modelProvider)
	{
		// Delete at Root
		// - by basyx::object - should not work, root is a map
		auto deleteResult = modelProvider->deleteValue("inRoot", 1.2);
		ASSERT_EQ(deleteResult, basyx::object::error::MalformedRequest);
		basyx::object toTest = modelProvider->getModelPropertyValue("inRoot");
		ASSERT_ANY_EQ(toTest, 1.2);
		// - by index
		modelProvider->deleteValue("inRoot");
		toTest = modelProvider->getModelPropertyValue("inRoot");
		ASSERT_TRUE(toTest.IsNull());

		// Check case-sensitivity
		toTest = modelProvider->getModelPropertyValue("inroot");
		ASSERT_ANY_EQ(toTest, uint64_t{ 78 });
		modelProvider->deleteValue("inroot");
		toTest = modelProvider->getModelPropertyValue("inroot");
		ASSERT_TRUE(toTest.IsNull());

		// Delete empty path
		auto deleteError = modelProvider->deleteValue("", "");
		ASSERT_EQ(deleteError, basyx::object::error::MalformedRequest);

		// Delete at Map
		// - by basyx::object - should not work in maps, because basyx::object refers to a contained basyx::object, not the index
		modelProvider->deleteValue("/structure/map/", "inMap");
		toTest = modelProvider->getModelPropertyValue("/structure/map/inMap");
		ASSERT_ANY_EQ(toTest, std::string("34"));
		// - by index
		modelProvider->deleteValue("/structure/map/inMap");
		toTest = modelProvider->getModelPropertyValue("/structure/map");
		ASSERT_TRUE(toTest.InstanceOf<basyx::object::object_map_t>());
		ASSERT_EQ(toTest.Get<basyx::object::object_map_t&>().size(), 0);

		// Delete remaining complete Map
		modelProvider->deleteValue("mapInRoot");
		toTest = modelProvider->getModelPropertyValue("mapInRoot");
		ASSERT_TRUE(toTest.IsNull());

		// Empty paths - should not delete anything
		modelProvider->deleteValue("", "");
		toTest = modelProvider->getModelPropertyValue("/primitives/integer");
		ASSERT_ANY_EQ(toTest, uint64_t{ 123 });
	}

};

}
}
}
}
}

#endif /* _MAPCREATEDELETE_H */
