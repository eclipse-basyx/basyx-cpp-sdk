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
 * test_ConnectedElement  .cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/ConnectedElement.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"
#include <BaSyx/submodel/api/qualifier/IReferable.h>

using namespace basyx::vab::core::proxy;
using namespace basyx;
using namespace basyx::submodel;

class ConnectedElementTest : public ::testing::Test
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

TEST_F(ConnectedElementTest, TestConstructor)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);
  map->emplace("object", basyx::object(std::string("object")));

  ConnectedElement connected_element(proxy, map);
  
  ASSERT_EQ(1, map->size());
  ASSERT_EQ("object", map->at("object").Get<std::string>());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestSetLocalValueNotPresent)
{
   std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);
   map->emplace("object", basyx::object(std::string("object")));

  ConnectedElement connected_element(proxy, map);

  connected_element.setLocalValue("another object", 3);

  ASSERT_EQ(2, map->size());
  ASSERT_EQ(3, map->at("another object").Get<int>());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestSetLocalValueAllreadyPresent)
{
   std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);
   map->emplace("object", basyx::object(std::string("object")));

  ConnectedElement connected_element(proxy, map);

  connected_element.setLocalValue("object", 3);

  ASSERT_EQ(1, map->size());
  //With set the already set value should remain
  ASSERT_EQ("object", map->at("object").Get<std::string>());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestGetLocalValuePresent)
{
   std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);
   map->emplace("object", basyx::object(std::string("object")));

  ConnectedElement connected_element(proxy, map);

  auto object = connected_element.getLocalValue("object");

  ASSERT_EQ(1, map->size());
  ASSERT_EQ(object.Get<std::string>(), map->at("object").Get<std::string>());
  ASSERT_EQ("object", object.Get<std::string>());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestGetLocalValueNotPresent)
{
   std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedElement connected_element(proxy, map);

  auto object = connected_element.getLocalValue("object");

  ASSERT_EQ(0, map->size());
  ASSERT_TRUE(object.IsNull());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestUpdateLocalValueNotPresent)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedElement connected_element(proxy, map);

  basyx::object any(3);

  connected_element.updateLocalValue("object", any);

  ASSERT_EQ(1, map->size());
  ASSERT_EQ(3, map->at("object").Get<int>());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestUpdateLocalValue)
{
  basyx::object any(3);
  
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);
  map->emplace("object", any);

  ConnectedElement connected_element(proxy, map);

  basyx::object other(std::string("new any"));

  connected_element.updateLocalValue("object", other);

  ASSERT_EQ(1, map->size());
  ASSERT_EQ("new any", map->at("object").Get<std::string>());
  ASSERT_EQ(0, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestGetID)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedElement connected_element(proxy, map);

  auto id = connected_element.getId();

  ASSERT_EQ(std::string("called with ") + IReferable::Path::IdShort, id);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedElementTest, TestSetID)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedElement connected_element(proxy, map);

  connected_element.setId("identifier");

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ(IReferable::Path::IdShort, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(std::string("identifier"), mock->updateElementCallValues.at(0).second.Get<std::string>());
}

