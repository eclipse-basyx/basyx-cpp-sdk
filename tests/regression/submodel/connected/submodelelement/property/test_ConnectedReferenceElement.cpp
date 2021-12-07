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
 * test_ConnectedReferenceElement.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/submodelelement/property/ConnectedReferenceElement.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp" 
#include <BaSyx/shared/anyTypeChecker.h>

using namespace basyx::vab::core::proxy;
using namespace basyx;
using namespace basyx::submodel;

class ConnectedReferenceElementTest : public ::testing::Test
{
public:
  std::shared_ptr<IVABElementProxy> proxy;
  std::shared_ptr<mockups::VABProxyMock> mock;
protected:
  void SetUp() override
  {
    mock = std::make_shared<mockups::VABProxyMock>();
    proxy = mock;
  }
};

TEST_F(ConnectedReferenceElementTest, TestGetPropertyType)
{
  auto element = ConnectedReferenceElement(proxy);

  auto value = element.getValue();
  
  ASSERT_EQ(std::string(IProperty::Path::Value), mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedReferenceElementTest, TestSetPropertyType)
{
  auto element = ConnectedReferenceElement(proxy);

  basyx::object value("value");

  //todo
  //element.setValue(value);

  ASSERT_EQ(std::string(IProperty::Path::Value), mock->updateElementCallValues.at(0).first);
  ASSERT_EQ("value", mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(1, mock->overallMockCalls());
}
