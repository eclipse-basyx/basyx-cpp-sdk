/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <gtest/gtest.h>

#include <BaSyx/vab/core/proxy/VABElementProxy.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>

#include "support/MockupModelProvider.h"

#include <memory>

using namespace basyx;

class BasyxVABElementProxy : public ::testing::Test
{
protected:
  void SetUp() override
  {
    proxy_address = "basyx://127.0.0.1";
    provider_mockup = std::make_shared<MockupModelProvider>();
  }

  std::shared_ptr<MockupModelProvider> provider_mockup;
  std::string proxy_address;
};

TEST_F(BasyxVABElementProxy, TestReadElementValueTest)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

  // Initially no method should have been called
  ASSERT_EQ(MockupModelProvider::CalledFunction::NONE, provider_mockup->called);

  auto value = proxy->readElementValue(std::string("/some/path/"));

  //get function of model provider should have been called
  ASSERT_EQ(MockupModelProvider::CalledFunction::GET, provider_mockup->called);
  //Mockup returns value 2
  ASSERT_EQ(2, value.Get<int>());
  //mockup should have been called with combined address
  ASSERT_EQ(proxy_address + "//some/path", provider_mockup->path);
}

TEST_F(BasyxVABElementProxy, TestUpdateElementValue)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));
  
  basyx::object new_value(1);
  proxy->updateElementValue(std::string("some/path/clock"), new_value);

  // Function marker should not be set
  ASSERT_EQ(MockupModelProvider::CalledFunction::NONE, provider_mockup->called);
  //Mockup clock should be set to new_value
  ASSERT_EQ(new_value.Get<int>(), provider_mockup->clock.Get<int>());
}

TEST_F(BasyxVABElementProxy, TestUpdateElementValueOnUnvalidPath)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

  basyx::object new_value(3);
  proxy->updateElementValue(std::string("/frozen/path"), new_value);

  // Function marker should not be set
  ASSERT_EQ(MockupModelProvider::CalledFunction::NONE, provider_mockup->called);
}

TEST_F(BasyxVABElementProxy, TestUpdateElementValueOnValidPath)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

  basyx::object new_value(12);
  proxy->updateElementValue(std::string("/some/valid/path"), new_value);

  // Function marker should not be set
  ASSERT_EQ(MockupModelProvider::CalledFunction::SET, provider_mockup->called);
  // Set path should be same as called one
  ASSERT_EQ(proxy_address + "//some/valid/path", provider_mockup->path);
  // Set value should be set
  ASSERT_EQ(new_value.Get<int>(), provider_mockup->val.Get<int>());
}

TEST_F(BasyxVABElementProxy, TestCreateElement)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

  basyx::object new_value(18);
  proxy->createElement(std::string("/some/path"), new_value);

  // Function marker should not be set
  ASSERT_EQ(MockupModelProvider::CalledFunction::CREATE, provider_mockup->called);
  // Set path should be same as called one
  ASSERT_EQ(proxy_address + "//some/path", provider_mockup->path);
  // Set value should be set
  ASSERT_EQ(new_value.Get<int>(), provider_mockup->val.Get<int>());
}

TEST_F(BasyxVABElementProxy, TestDeleteElement)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

  basyx::object deleted_value(18);
  proxy->deleteElement(std::string("some/path"), deleted_value);

  // Function marker should be set
  ASSERT_EQ(MockupModelProvider::CalledFunction::DELETE_COMPLEX, provider_mockup->called);
  // Set path should be same as called one
  ASSERT_EQ(proxy_address + "//some/path", provider_mockup->path);
  // Set value should be set
  ASSERT_EQ(deleted_value.Get<int>(), provider_mockup->val.Get<int>());
}

TEST_F(BasyxVABElementProxy, TestDeleteElementSimple)
{
  std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

  proxy->deleteElement(std::string("some/other/path"));

  // Function marker should be set
  ASSERT_EQ(MockupModelProvider::CalledFunction::DELETE_SIMPLE, provider_mockup->called);
  // Set path should be same as called one
  ASSERT_EQ(proxy_address + "//some/other/path", provider_mockup->path);
}

TEST_F(BasyxVABElementProxy, TestInvokeOperation)
{
	std::shared_ptr<vab::core::proxy::IVABElementProxy> proxy(new vab::core::proxy::VABElementProxy(proxy_address, provider_mockup));

	auto objCollection = basyx::object::make_list<int>();
	auto & collection = objCollection.Get<object::list_t<int>&>();

	objCollection.insert(2);
	auto return_value = proxy->invoke("//some/path/to/invoke", objCollection);

	// Since mockup returns always value three, this should be returned here as well
	ASSERT_EQ(3, return_value.Get<int>());
	// Function marker should be set
	ASSERT_EQ(MockupModelProvider::CalledFunction::INVOKE, provider_mockup->called);
	// Set path should be same as called one
	ASSERT_EQ(proxy_address + "//some/path/to/invoke", provider_mockup->path);
	// and the function should have been called with the collection
	ASSERT_EQ(collection.size(), provider_mockup->val.Get<basyx::object::list_t<int>&>().size());
	ASSERT_EQ(2, provider_mockup->val.Get<basyx::object::list_t<int>&>().at(0));
}
