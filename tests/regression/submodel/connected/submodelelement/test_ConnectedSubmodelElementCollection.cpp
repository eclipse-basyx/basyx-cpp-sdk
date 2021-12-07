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
 * test_ConnectedSubmodelElement  .cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/submodelelement/ConnectedSubmodelElementCollection.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"
#include <BaSyx/submodel/api/submodelelement/property/IProperty.h>
#include <BaSyx/submodel/api/ISubModel.h>

using namespace basyx::vab::core::proxy;
using namespace basyx;
using namespace basyx::submodel;

class ConnectedSubmodelElementCollectionTest : public ::testing::Test
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

TEST_F(ConnectedSubmodelElementCollectionTest, TestSetValue)
{
  ConnectedSubmodelElementCollection elements(proxy);

  basyx::object::object_list_t value;
  value.push_back('a');

  //todo 
  //elements.setValue(value);

  ASSERT_EQ(IProperty::Path::Value, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(1, mock->updateElementCallValues.at(0).second.Get<basyx::object::object_list_t>().size());
  ASSERT_EQ('a', mock->updateElementCallValues.at(0).second.Get<basyx::object::object_list_t>().at(0).Get<char>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestGetValue)
{
  ConnectedSubmodelElementCollection elements(proxy);

  mock->collection.push_back(0);

  auto value = elements.getValue();

  ASSERT_EQ(IProperty::Path::Value, mock->getElementCallValues.at(0));
  ASSERT_EQ(1, value.size());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestSetOrdered)
{
  ConnectedSubmodelElementCollection elements(proxy);
  
  elements.setOrdered(true);
  elements.setOrdered(false);

  ASSERT_EQ(ISubmodelElementCollection::Path::Ordered, mock->updateElementCallValues.at(0).first);
  ASSERT_TRUE(mock->updateElementCallValues.at(0).second.Get<bool>());
  ASSERT_EQ(ISubmodelElementCollection::Path::Ordered, mock->updateElementCallValues.at(1).first);
  ASSERT_FALSE(mock->updateElementCallValues.at(1).second.Get<bool>());
  ASSERT_EQ(2, mock->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestIsOrdered)
{
  auto mock_bool = std::make_shared<mockups::VABProxyMockBool>();
  std::shared_ptr<IVABElementProxy> proxy_bool = mock_bool;

  ConnectedSubmodelElementCollection elements(proxy_bool);

  auto value = elements.isOrdered();

  ASSERT_EQ(ISubmodelElementCollection::Path::Ordered, mock_bool->getElementCallValues.at(0));
  ASSERT_TRUE(value);
  ASSERT_EQ(1, mock_bool->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestSetAllowDuplicates)
{
  ConnectedSubmodelElementCollection elements(proxy);

  elements.setAllowDuplicates(true);
  elements.setAllowDuplicates(false);

  ASSERT_EQ(ISubmodelElementCollection::Path::AllowDuplicates, mock->updateElementCallValues.at(0).first);
  ASSERT_TRUE(mock->updateElementCallValues.at(0).second.Get<bool>());
  ASSERT_EQ(ISubmodelElementCollection::Path::AllowDuplicates, mock->updateElementCallValues.at(1).first);
  ASSERT_FALSE(mock->updateElementCallValues.at(1).second.Get<bool>());
  ASSERT_EQ(2, mock->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestGetAllowDuplicates)
{
  auto mock_bool = std::make_shared<mockups::VABProxyMockBool>();
  std::shared_ptr<IVABElementProxy> proxy_bool = mock_bool;

  ConnectedSubmodelElementCollection elements(proxy_bool);

  auto value = elements.isAllowDuplicates();

  ASSERT_EQ(ISubmodelElementCollection::Path::AllowDuplicates, mock_bool->getElementCallValues.at(0));
  ASSERT_TRUE(value);
  ASSERT_EQ(1, mock_bool->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestSetElements)
{
  ConnectedSubmodelElementCollection elements(proxy);

  basyx::object::object_map_t map;

  //todo
  //elements.setElements(map);

  ASSERT_EQ(ISubModel::Path::Submodelelement, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(map, mock->updateElementCallValues.at(0).second.Get<basyx::object::object_map_t>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementCollectionTest, TestGetElements)
{
  auto mock_map = std::make_shared<mockups::VABProxyMockMap>();
  std::shared_ptr<IVABElementProxy> proxy_map = mock_map;

  mock_map->map["pos"] = basyx::object();

  ConnectedSubmodelElementCollection elements(proxy_map);

  auto value = elements.getElements();

  ASSERT_EQ(ISubModel::Path::Submodelelement, mock_map->getElementCallValues.at(0));
  ASSERT_EQ(1, value.size());
  ASSERT_EQ(1, mock_map->overallMockCalls());
}

