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

#include <BaSyx/submodel/connected/submodelelement/ConnectedSubmodelElement.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include "support/VABProxyMock.cpp"

using namespace basyx::submodel;
using namespace basyx;
using namespace basyx::vab::core::proxy;

class ConnectedSubmodelElementTest : public ::testing::Test
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

TEST_F(ConnectedSubmodelElementTest, TestGetDataSpecificationReferences)
{
  auto mock_collection = std::make_shared<mockups::VABProxyMockCollection>();
  std::shared_ptr<IVABElementProxy> proxy_collection = mock_collection;

  auto data_element = ConnectedSubmodelElement(proxy_collection);

  auto category = data_element.getDataSpecificationReferences();

  ASSERT_EQ(std::string(IReference::Path::DataSpecifications), mock_collection->getElementCallValues.at(0));
  ASSERT_EQ(1, mock_collection->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementTest, TestIDShort)
{
  auto data_element = ConnectedSubmodelElement(proxy);

  auto category = data_element.getIdShort();

  ASSERT_EQ(std::string(IReferable::Path::IdShort), mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedSubmodelElementTest, TestGetCategory)
{
  auto data_element = ConnectedSubmodelElement(proxy);

  auto category = data_element.getCategory();

  ASSERT_EQ(std::string(IReferable::Path::Category), mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}

// Todo: Adapt to new structure
//TEST_F(ConnectedSubmodelElementTest, TestGetDescription)
//{
//  auto data_element = ConnectedSubmodelElement(proxy);
//
//  auto desc = data_element.getDescription();
//
//  ASSERT_EQ(std::string(ReferablePaths::DESCRIPTION), mock->getElementCallValues.at(0));
//  ASSERT_EQ(1, mock->overallMockCalls());
//}

// Todo: Adapt to new structure
//TEST_F(ConnectedSubmodelElementTest, TestGetParent)
//{
//  auto mock_collection = std::make_shared<mockups::VABProxyMockCollection>();
//  std::shared_ptr<IVABElementProxy> proxy_collection = mock_collection;
//
//  auto data_element = ConnectedSubmodelElement(proxy_collection);
//
//  auto desc = data_element.getParent();
//
//  ASSERT_EQ(std::string(reference::paths::PARENTS), mock_collection->getElementCallValues.at(0));
//  ASSERT_EQ(1, mock_collection->overallMockCalls());
//}

TEST_F(ConnectedSubmodelElementTest, TestGetQualifier)
{
  auto mock_collection = std::make_shared<mockups::VABProxyMockCollection>();
  std::shared_ptr<mockups::VABProxyMockCollection> proxy_collection = mock_collection;

  auto data_element = ConnectedSubmodelElement(proxy_collection);

  auto desc = data_element.getQualifier();

  ASSERT_EQ(std::string(IReference::Path::Qualifiers), mock_collection->getElementCallValues.at(0));
  ASSERT_EQ(1, mock_collection->overallMockCalls());
}

// Todo: Adapt to new structure
//TEST_F(ConnectedSubmodelElementTest, TestGetSemanticId)
//{
//  auto data_element = ConnectedSubmodelElement(proxy);
//
//  auto desc = data_element.getSemanticId();
//
//  ASSERT_EQ(std::string(reference::paths::SEMANTICIDS), mock->getElementCallValues.at(0));
//  ASSERT_EQ(1, mock->overallMockCalls());
//}

TEST_F(ConnectedSubmodelElementTest, TestGetHasKindRefernce)
{
  auto data_element = ConnectedSubmodelElement(proxy);

  auto desc = data_element.getHasKindReference();

  ASSERT_EQ(std::string(IHasKind::Path::Kind), mock->getElementCallValues.at(0));
  ASSERT_EQ(1, mock->overallMockCalls());
}



