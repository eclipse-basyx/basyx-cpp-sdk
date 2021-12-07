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

#include <BaSyx/submodel/connected/submodelelement/property/ConnectedMapProperty.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"

using namespace basyx::vab::core::proxy;
using namespace basyx;
using namespace basyx::submodel;

class ConnectedMapPropertyTest : public ::testing::Test
{
public:
  std::shared_ptr<IVABElementProxy> proxy;
  std::shared_ptr<mockups::VABProxyMockUp<mockups::ProxyType::Map>> mock;
protected:
  void SetUp() override
  {
    mock = std::make_shared<mockups::VABProxyMockUp<mockups::ProxyType::Map>>();
    proxy = mock;
  }
};


TEST_F(ConnectedMapPropertyTest, TestGetValueNotPresent)
{
  ConnectedMapProperty connected_map_property(proxy);
  
  ASSERT_THROW(connected_map_property.getValue("asdf"), std::out_of_range);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedMapPropertyTest, TestGetValue)
{
  ConnectedMapProperty connected_map_property(proxy);

  mock->map["asdf"] = basyx::object("value");

  auto value = connected_map_property.getValue("asdf");

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ("value", value.Get<std::string>());
}

TEST_F(ConnectedMapPropertyTest, TestPutNotPresent)
{
  ConnectedMapProperty connected_map_property(proxy);

  basyx::object value("value");

  connected_map_property.put("path", value);

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ(std::string(IProperty::Path::Value) + "//path", mock->updateElementCallValues.at(0).first);
  ASSERT_EQ("value", mock->updateElementCallValues.at(0).second.Get<std::string>());
}

TEST_F(ConnectedMapPropertyTest, TestSetMap)
{
  ConnectedMapProperty connected_map_property(proxy);

  basyx::object::object_map_t map;

  connected_map_property.set(map);

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ(std::string(IProperty::Path::Value), mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(map, mock->updateElementCallValues.at(0).second.Get<basyx::object::object_map_t>());
}

TEST_F(ConnectedMapPropertyTest, TestGetKeys)
{
  ConnectedMapProperty connected_map_property(proxy);

  basyx::object value1(std::string("value"));
  basyx::object value2(std::string("value"));

  mock->map.emplace("path1", value1);
  mock->map.emplace("path2", value2);

  auto keys = connected_map_property.getKeys();

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ(std::string(IProperty::Path::Value), mock->getElementCallValues.at(0));

  ASSERT_TRUE(keys.at(0).Get<std::string>() == "path1" or keys.at(0).Get<std::string>() == "path2");
  ASSERT_TRUE(keys.at(1).Get<std::string>() == "path1" or keys.at(1).Get<std::string>() == "path2");
}

TEST_F(ConnectedMapPropertyTest, TestGetEntryCount)
{
  ConnectedMapProperty connected_map_property(proxy);

  basyx::object value1(std::string("value"));
  basyx::object value2(std::string("value"));

  mock->map.emplace("path1", value1);
  mock->map.emplace("path2", value2);

  auto key_count = connected_map_property.getEntryCount();

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ(std::string(IProperty::Path::Value), mock->getElementCallValues.at(0));
  ASSERT_EQ(2, key_count);
}

TEST_F(ConnectedMapPropertyTest, TestRemove)
{
  ConnectedMapProperty connected_map_property(proxy);

  connected_map_property.remove("path");

  ASSERT_EQ(1, mock->overallMockCalls());
  ASSERT_EQ(std::string(IProperty::Path::Value) + "//path", mock->removeElementCallValues.at(0));
}

