/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
 * test_ConnectedDataElement  .cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/api/submodelelement/operation/IOperation.h>
#include <BaSyx/submodel/connected/submodelelement/operation/ConnectedOperation.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"

using namespace basyx::submodel;
using namespace basyx;
using namespace basyx::vab::core::proxy;

class ConnectedOperationTest : public ::testing::Test
{
public:
  std::shared_ptr<IVABElementProxy> proxy;
  std::shared_ptr<mockups::VABProxyMockCollection> mock;
protected:
  void SetUp() override
  {
    mock = std::make_shared<mockups::VABProxyMockCollection>();
    proxy = mock;
  }
};

TEST_F(ConnectedOperationTest, TestGetParameterTypes)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedOperation connected_operation(proxy);

  auto types = connected_operation.getParameterTypes();

  ASSERT_EQ(IOperation::Path::Input, mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedOperationTest, TestGetReturnTypes)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedOperation connected_operation(proxy);

  auto types = connected_operation.getReturnType();

  ASSERT_EQ(IOperation::Path::Output, mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedOperationTest, TestInvoke)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedOperation connected_operation(proxy);

  basyx::object param{2};
  auto invoked = connected_operation.invoke(param);

  ASSERT_EQ("called with ", invoked.Get<std::string>());
  ASSERT_FALSE(mock->invokeCallParameter.IsNull());
  ASSERT_TRUE(mock->invokeCallParameter.InstanceOf<int>());
  ASSERT_EQ(mock->invokeCallParameter.Get<int>(), 2);
  ASSERT_EQ(1, mock->overallMockCalls());
}


