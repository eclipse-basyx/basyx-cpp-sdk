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
 * test_ConnectedMapProperty.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/submodelelement/property/ConnectedCollectionProperty.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"
#include <BaSyx/submodel/api/submodelelement/property/IProperty.h>

using namespace basyx;
using namespace basyx::submodel;
using namespace basyx::vab::core::proxy;


class ConnectedCollectionPropertyTest : public ::testing::Test
{
public:
  std::shared_ptr<IVABElementProxy> proxy;
  std::shared_ptr<mockups::VABProxyMockMap> mock;
protected:
  void SetUp() override
  {
    mock = std::make_shared<mockups::VABProxyMockMap>();
    proxy = mock;
  }
};


TEST_F(ConnectedCollectionPropertyTest, TestSet)
{
  ConnectedCollectionProperty property(proxy);

  basyx::object::object_list_t collection;
  collection.push_back(123);

  property.set(collection);
  
  ASSERT_EQ(IProperty::Path::Value, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(123, mock->updateElementCallValues.at(0).second.Get<basyx::object::object_list_t>().at(0).Get<int>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedCollectionPropertyTest, TestAdd)
{
  ConnectedCollectionProperty property(proxy);

  basyx::object value(2);

  property.add(value);

  ASSERT_EQ(IProperty::Path::Value, mock->createElementCallValues.at(0).first);
  ASSERT_EQ(2, mock->createElementCallValues.at(0).second.Get<int>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedCollectionPropertyTest, TestRemove)
{
  ConnectedCollectionProperty property(proxy);

  basyx::object value(2);

  property.remove(value);

  ASSERT_EQ(IProperty::Path::Value, mock->deleteElementCallValues.at(0).first);
  ASSERT_EQ(2, mock->deleteElementCallValues.at(0).second.Get<int>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedCollectionPropertyTest, TestGetElementsAndCount)
{
  ConnectedCollectionProperty property(proxy);

  basyx::object::object_list_t collection;
  collection.push_back(2);
  collection.push_back("str");

  mock->map[IProperty::Path::Value] = collection;

  auto elements = property.getElements();

  ASSERT_EQ(IProperty::Path::Value, mock->getElementCallValues.at(0));
  ASSERT_EQ("str", collection.at(1).Get<std::string>());
  ASSERT_EQ(2, property.getElementCount());
  ASSERT_EQ(2, mock->overallMockCalls());
}

