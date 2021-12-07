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

#include <BaSyx/submodel/connected/submodelelement/property/file/ConnectedFile.h>
#include <BaSyx/vab/core/proxy/IVABElementProxy.h>
#include <BaSyx/submodel/api/submodelelement/property/IProperty.h>
#include <BaSyx/submodel/api/submodelelement/property/blob/IBlob.h>
#include "support/VABProxyMock.cpp" 
#include <BaSyx/shared/anyTypeChecker.h>

using namespace basyx::vab::core::proxy;
using namespace basyx;
using namespace basyx::submodel;

class ConnectedFileTest : public ::testing::Test
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

TEST_F(ConnectedFileTest, TestSetValue)
{
  ConnectedFile file(proxy);

  file.setValue("value");

  ASSERT_EQ("value", mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(IProperty::Path::Value, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedFileTest, TestGetValue)
{
  ConnectedFile file(proxy);

  auto val = file.getValue();

  ASSERT_EQ(std::string("called with ") + IProperty::Path::Value, val);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedFileTest, TestSetMimeType)
{
  ConnectedFile file(proxy);

  file.setMimeType("value");

  ASSERT_EQ("value", mock->updateElementCallValues.at(0).second.Get<std::string>());
  ASSERT_EQ(submodelelement::BlobPath::MIMETYPE, mock->updateElementCallValues.at(0).first);
  ASSERT_EQ(1, mock->overallMockCalls());
}

TEST_F(ConnectedFileTest, TestGetMimeType)
{
  ConnectedFile file(proxy);

  auto val = file.getMimeType();

  ASSERT_EQ(std::string("called with ") + submodelelement::BlobPath::MIMETYPE, val);
  ASSERT_EQ(1, mock->overallMockCalls());
}


