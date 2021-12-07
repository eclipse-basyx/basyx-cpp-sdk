/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef _MAPINVOKE_H
#define _MAPINVOKE_H

#include <gtest/gtest.h>

#include <BaSyx/shared/types.h>

#include <BaSyx/vab/core/IModelProvider.h>

#define ASSERT_ANY_EQ(a,t) 	ASSERT_TRUE(a.template InstanceOf<decltype(t)>());		ASSERT_EQ(t, a.template Get<decltype(t)&>());



namespace basyx {
namespace tests {
namespace regression {
namespace vab {
namespace snippet {


class MapInvoke {
public:

    static void test(basyx::vab::core::IModelProvider * modelProvider) {
		auto complex = modelProvider->invokeOperation("operations/complex", basyx::object::make_list<object>({ uint64_t{ 12 } , uint64_t{ 34 } }));
		ASSERT_ANY_EQ(complex, uint64_t{ 46 });

		// Invoke unsupported functional interface
		auto supplier = modelProvider->invokeOperation("operations/supplier", basyx::object::make_null());

		// Invoke non-existing operation
		auto nonExisting = modelProvider->invokeOperation("operations/unknown", basyx::object::make_null());
		ASSERT_TRUE(nonExisting.IsNull());

		// Invoke invalid operation -> not a function, but a primitive data type
		auto invalid = modelProvider->invokeOperation("operations/invalid", basyx::object::make_null());
		ASSERT_TRUE(invalid.IsNull());

		/*
		// Invoke operations that throw Exceptions
		try {
			modelProvider->invokeOperation("operations/serverException");
			fail();
		}
		catch (ServerException e) {
			// exception type not implemented, yet
			// assertEquals(e.getType(), "testExceptionType");
		}

		try {
			modelProvider->invokeOperation("operations/nullException");
			fail();
		}
		catch (ServerException e) {
			// exception type not implemented, yet
			// assertEquals(e.getType(), "java.lang.NullPointerException");
		}*/

		// Empty paths - should execute, but has no effect
		auto empty = modelProvider->invokeOperation("", basyx::object::make_null());
		ASSERT_TRUE(empty.IsNull());
	}
};

}
}
}
}
}


#endif /* _MAPINVOKE_H */
