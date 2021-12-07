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

#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"
#include <BaSyx/submodel/connected/submodelelement/property/ConnectedPropertyFactory.h>

using namespace basyx::vab::core::proxy;
//
//class ConnectedPropertyFactory : public ::testing::Test
//{
//public:
//  std::shared_ptr<IVABElementProxy> proxy;
//  std::shared_ptr<mockups::VABProxyMockMap> mock;
//protected:
//  void SetUp() override
//  {
//    mock = std::make_shared<mockups::VABProxyMockMap>();
//    proxy = mock;
//  }
//};
//
//TEST_F(ConnectedPropertyFactory, TestConstructor)
//{
//  createProperty(proxy);
//  
//  ASSERT_EQ(0, mock->overallMockCalls());
//}
//
//TEST_F(ConnectedPropertyFactory, TestConstructor)
//{
//  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);
//  map->emplace("object", basyx::object(std::string("object")));
//
//  createProperty();
//
//  ASSERT_EQ(1, map->size());
//  ASSERT_EQ("object", map->at("object").Get<std::string>());
//  ASSERT_EQ(0, mock->overallMockCalls());
//}

