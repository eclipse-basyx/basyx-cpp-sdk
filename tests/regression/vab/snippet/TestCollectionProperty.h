/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef _TESTCOLLECTIONPROPERTY_H
#define _TESTCOLLECTIONPROPERTY_H

#include <gtest/gtest.h>

#include <BaSyx/shared/types.h>

#include <BaSyx/vab/core/IModelProvider.h>

#include "macros.h"


namespace basyx {
namespace tests {
namespace regression {
namespace vab {
namespace snippet {

class TestCollectionProperty {
public:
	static void test(basyx::vab::core::IModelProvider * modelProvider)
	{
		testRead(modelProvider);
		testCreateDelete(modelProvider);
	}
private:
	static void testRead(basyx::vab::core::IModelProvider * modelProvider)
	{
		// Adding elements to tested list
		modelProvider->createValue("/structure/list/", uint64_t{ 5 });
		modelProvider->createValue("/structure/list/", uint64_t{ 12 });

		// Test reading whole lists
    	auto collection = modelProvider->getModelPropertyValue("/structure/list/");
    	ASSERT_TRUE(collection.InstanceOf<basyx::object::list_t<uint64_t>>());
    	ASSERT_EQ(collection.Get<basyx::object::list_t<uint64_t>&>().size(), 2);

		// Test invalid list access - single list elements cannot be accessed directly
		auto singleAccess = modelProvider->getModelPropertyValue("/structure/list/0");
		ASSERT_TRUE(singleAccess.IsError());
		ASSERT_EQ(singleAccess.getError(), basyx::object::error::PropertyNotFound);

		// Test invalid list access
		auto invalid = modelProvider->getModelPropertyValue("/structure/list/invalid");
		ASSERT_TRUE(invalid.IsNull());

		// Delete remaining entries
		modelProvider->deleteValue("/structure/list",  uint64_t{ 5 });
		modelProvider->deleteValue("/structure/list", uint64_t{ 12 });

		auto collection2 = modelProvider->getModelPropertyValue("/structure/list/");
		ASSERT_TRUE(collection2.empty());
	}


	static void testCreateDelete(basyx::vab::core::IModelProvider * modelProvider)
	{
		// Create elements in List (no key provided)
		auto insertResult = modelProvider->createValue("/structure/list/", uint64_t{ 56 });
		ASSERT_EQ(insertResult, basyx::object::error::None);
		auto toTest = modelProvider->getModelPropertyValue("/structure/list/");
		ASSERT_TRUE(toTest.InstanceOf<basyx::object::list_t<uint64_t>>());
		auto & objectCollection = toTest.Get<basyx::object::list_t<uint64_t>&>();
		ASSERT_EQ(objectCollection.back(), uint64_t{ 56 });
		
		// Delete at List
		// by object
		modelProvider->deleteValue("/structure/list/", uint64_t{ 56 });
		toTest = modelProvider->getModelPropertyValue("/structure/list/");
		ASSERT_EQ(toTest.GetObjectType(), basyx::type::objectType::List);
		ASSERT_TRUE(toTest.empty());

		// Create a list element
		modelProvider->createValue("listInRoot", basyx::object::list_t<uint64_t>{ 1, 1, 2, 3, 5 });

		// Test whole list
		auto listInRoot = modelProvider->getModelPropertyValue("listInRoot");
		ASSERT_TRUE(listInRoot.InstanceOf<basyx::object::list_t<uint64_t>>());
		ASSERT_EQ(listInRoot.Get<basyx::object::list_t<uint64_t>&>().size(), 5);

		ASSERT_EQ(listInRoot.Get<basyx::object::list_t<uint64_t>&>()[0], 1);
		ASSERT_EQ(listInRoot.Get<basyx::object::list_t<uint64_t>&>()[1], 1);
		ASSERT_EQ(listInRoot.Get<basyx::object::list_t<uint64_t>&>()[2], 2);
		ASSERT_EQ(listInRoot.Get<basyx::object::list_t<uint64_t>&>()[3], 3);
		ASSERT_EQ(listInRoot.Get<basyx::object::list_t<uint64_t>&>()[4], 5);

		// Delete whole list
		modelProvider->deleteValue("listInRoot");
		toTest = modelProvider->getModelPropertyValue("listInRoot");
		ASSERT_TRUE(toTest.IsNull());

		return;
	}

};

}
}
}
}
}

#endif /* _TESTCOLLECTIONPROPERTY_H */
