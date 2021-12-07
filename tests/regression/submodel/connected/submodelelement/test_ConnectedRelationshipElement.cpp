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
 * test_ConnectedRelationshipElement  .cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/submodelelement/ConnectedRelationshipElement.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"

using namespace basyx::submodel;
using namespace basyx;
using namespace basyx::vab::core::proxy;

class ConnectedRelationshipElementTest : public ::testing::Test
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

TEST_F(ConnectedRelationshipElementTest, TestGetFirst)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedRelationshipElement connected_element(proxy);

  auto first = connected_element.getFirst();

  ASSERT_EQ(std::string(IRelationshipElement::Path::First), mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedRelationshipElementTest, TestSetFirst)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedRelationshipElement connected_element(proxy);

  basyx::object first("first");

  //todo
  //connected_element.setFirst(first);

  ASSERT_EQ(std::string(IRelationshipElement::Path::First), mock->updateElementCallValues.at(0).first);
  ASSERT_EQ("first", mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedRelationshipElementTest, TestGetSecond)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedRelationshipElement connected_element(proxy);

  auto second = connected_element.getSecond();

  ASSERT_EQ(std::string(IRelationshipElement::Path::Second), mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedRelationshipElementTest, TestSetSecond)
{
  std::shared_ptr<basyx::object::object_map_t> map(new basyx::object::object_map_t);

  ConnectedRelationshipElement connected_element(proxy);

  basyx::object second("second");


  //todo
  //connected_element.setSecond(second);

  ASSERT_EQ(std::string(IRelationshipElement::Path::Second), mock->updateElementCallValues.at(0).first);
  ASSERT_EQ("second", mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(1, mock->overallMockCalls());
}

