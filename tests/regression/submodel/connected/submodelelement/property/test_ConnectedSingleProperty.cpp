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
 * test_ConnectedSingleProperty.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/submodelelement/property/ConnectedSingleProperty.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp" 
#include <BaSyx/shared/anyTypeChecker.h>

using namespace basyx::vab::core::proxy;
using namespace basyx::submodel;
using namespace basyx;

class ConnectedSinglePropertyTest : public ::testing::Test
{
public:
  std::shared_ptr<IVABElementProxy> proxy;
  std::shared_ptr<mockups::VABProxyMockMap> mock;
protected:
  void SetUp() override
  {
    mock = std::make_shared<mockups::VABProxyMockMap>();
    proxy = mock;

    mock->map[IProperty::Path::ValueType] = basyx::object("str");
    mock->map[IProperty::Path::Value] = basyx::object("another str");
  }
};

TEST_F(ConnectedSinglePropertyTest, TestGet)
{
  ConnectedSingleProperty property(proxy);
  
  auto val = property.get();
  
  ASSERT_EQ(std::string("another str"), val.Get<std::string>());
  ASSERT_EQ(IProperty::Path::Value, mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedSinglePropertyTest, TestSet)
{
  ConnectedSingleProperty property(proxy);

  basyx::object val(2);

  property.set(val);

  ASSERT_EQ(IProperty::Path::Value, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(2, mock->updateElementCallValues.at(0).second.Get<int>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedSinglePropertyTest, TestGetValueType)
{
  ConnectedSingleProperty property(proxy);

  auto val = property.getValueType();

  ASSERT_EQ("str", val);
  ASSERT_EQ("", mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

