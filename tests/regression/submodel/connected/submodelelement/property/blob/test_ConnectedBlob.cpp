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
 * test_ConnectedProperty.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/submodel/connected/submodelelement/property/blob/ConnectedBlob.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include <BaSyx/submodel/api/ISubModel.h>
#include <BaSyx/submodel/api/submodelelement/property/blob/IBlob.h>
#include "support/VABProxyMock.cpp" 
#include <BaSyx/shared/anyTypeChecker.h>

using namespace basyx::vab::core::proxy;
using namespace basyx;
using namespace basyx::submodel;

class ConnectedBlobTest : public ::testing::Test
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

TEST_F(ConnectedBlobTest, TestSetValue)
{
  ConnectedBlob blob(proxy);

  std::string value = {'a','b','c'};

  blob.setValue(value);

  ASSERT_EQ(value, mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(IProperty::Path::Value, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedBlobTest, TestGetValue)
{
  std::shared_ptr<IVABElementProxy> proxy_byte_array;
  std::shared_ptr<mockups::VABProxyMockByteArray> mock_byte_array;

  mock_byte_array = std::make_shared<mockups::VABProxyMockByteArray>();
  proxy_byte_array = mock_byte_array;

  ConnectedBlob blob(proxy_byte_array);

  auto val = blob.getValue();

  ASSERT_EQ(std::string(""), val);
  ASSERT_EQ(1, mock_byte_array->overallMockCalls());
}

TEST_F(ConnectedBlobTest, TestSetMimeType)
{
  ConnectedBlob blob(proxy);

  blob.setMimeType("value");

  ASSERT_EQ("value", mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(submodelelement::BlobPath::MIMETYPE, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedBlobTest, TestGetMimeType)
{
  ConnectedBlob blob(proxy);

  auto val = blob.getMimeType();

  ASSERT_EQ(std::string("called with ") + submodelelement::BlobPath::MIMETYPE, val);
  ASSERT_EQ(1, mock->overallMockCalls());
}


