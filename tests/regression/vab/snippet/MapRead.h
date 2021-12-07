/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef _MAPREAD_H
#define _MAPREAD_H

#include <gtest/gtest.h>

#include <BaSyx/shared/types.h>

#include <BaSyx/vab/core/IModelProvider.h>

#define ASSERT_ANY_EQ(a,t) 	ASSERT_TRUE(a.template InstanceOf<decltype(t)>());		ASSERT_EQ(t, a.template Get<decltype(t)&>());



namespace basyx {
namespace tests {
namespace regression {
namespace vab {
namespace snippet {


class MapRead {
public:

    static void test(basyx::vab::core::IModelProvider * modelProvider) {
		// Test path access
		auto slashA = modelProvider->getModelPropertyValue("/primitives/integer");
		auto slashB = modelProvider->getModelPropertyValue("primitives/integer/");
		auto slashC = modelProvider->getModelPropertyValue("/primitives/integer/");
		auto slashD = modelProvider->getModelPropertyValue("/primitives/integer/");

		ASSERT_ANY_EQ(slashA, uint64_t{ 123 });
		ASSERT_ANY_EQ(slashB, uint64_t{ 123 });
		ASSERT_ANY_EQ(slashC, uint64_t{ 123 });
		ASSERT_ANY_EQ(slashD, uint64_t{ 123 });

		// Test reading different data types
		auto mapValue = modelProvider->getModelPropertyValue("primitives");
		auto doubleValue = modelProvider->getModelPropertyValue("primitives/double");
		auto stringValue = modelProvider->getModelPropertyValue("primitives/string");

		ASSERT_TRUE(mapValue.InstanceOf<basyx::object::object_map_t>());
		ASSERT_TRUE(doubleValue.InstanceOf<double>());
		ASSERT_TRUE(stringValue.InstanceOf<std::string>());

		ASSERT_EQ(3, mapValue.Get<basyx::object::object_map_t&>().size());
		ASSERT_EQ(3.14, doubleValue.Get<double>());
		ASSERT_EQ("TestValue", stringValue.Get<std::string&>());

		// Test case sensitivity
		auto caseSensitiveA = modelProvider->getModelPropertyValue("special/casesensitivity");
		auto caseSensitiveB = modelProvider->getModelPropertyValue("special/caseSensitivity");

		ASSERT_TRUE(caseSensitiveA.InstanceOf<bool>());
		ASSERT_TRUE(caseSensitiveB.InstanceOf<bool>());
		ASSERT_EQ(true, caseSensitiveA.Get<bool>());
		ASSERT_EQ(false, caseSensitiveB.Get<bool>());

		// Test reading null value
		auto nullValue = modelProvider->getModelPropertyValue("special/null");
		ASSERT_TRUE(nullValue.IsNull());

		// Non-existing parent element
		auto errorParent = modelProvider->getModelPropertyValue("unknown/x");
		ASSERT_TRUE(errorParent.IsError());
		ASSERT_EQ(errorParent.getError(), basyx::object::error::PropertyNotFound);

		// Non-existing target element
		auto unknownError1 = modelProvider->getModelPropertyValue("primitives/unknown");
		ASSERT_TRUE(unknownError1.IsError());
		ASSERT_EQ(errorParent.getError(), basyx::object::error::PropertyNotFound);

		auto unknownError2 = modelProvider->getModelPropertyValue("unknown");
		ASSERT_TRUE(unknownError2.IsError());
		ASSERT_EQ(unknownError2.getError(), basyx::object::error::PropertyNotFound);

		// Nested access
		ASSERT_ANY_EQ(modelProvider->getModelPropertyValue("special/nested/nested/value"), uint64_t{ 100 });

		// Empty path
		auto rootValueA = modelProvider->getModelPropertyValue("");
		auto rootValueB = modelProvider->getModelPropertyValue("/");

		ASSERT_TRUE(rootValueA.InstanceOf<basyx::object::object_map_t>());
		ASSERT_TRUE(rootValueB.InstanceOf<basyx::object::object_map_t>());

		ASSERT_EQ(rootValueA.Get<basyx::object::object_map_t&>().size(), 4);
		ASSERT_EQ(rootValueB.Get<basyx::object::object_map_t&>().size(), 4);
	}
};

}
}
}
}
}


#endif /* _MAPREAD_H */
