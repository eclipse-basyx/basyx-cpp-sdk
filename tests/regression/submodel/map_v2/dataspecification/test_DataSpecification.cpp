/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <gtest/gtest.h>

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationContent.h>
#include "BaSyx/aas/map_v2/dataspecification/DataSpecification.h"

using namespace basyx::aas::map;
using namespace basyx::aas;

class DataSpecificationTest : public ::testing::Test
{
protected:
  void SetUp() override
  {}

class DataSpecificationContentMock
  : public virtual api::IDataSpecificationContent
  , public basyx::vab::ElementMap
  {
  public:
    DataSpecificationContentMock()
      : basyx::vab::ElementMap{}
    {}

    bool isMock()
    {
      return true;
    }
  };

class DataSpecificationContentMock2
  : public virtual api::IDataSpecificationContent
  , public basyx::vab::ElementMap
  {
  public:
    DataSpecificationContentMock2()
      : basyx::vab::ElementMap{}
    {}

    bool isMock2()
    {
      return true;
    }
  };
};

TEST_F(DataSpecificationTest, TestConstructor)
{
//  simple::Identifier id;
//  std::unique_ptr<api::IDataSpecificationContent> content = util::make_unique<DataSpecificationContentMock>();
//  DataSpecification dataSpecification("id", id, std::move(content));
//
//  ASSERT_EQ(dataSpecification.getIdShort(), "id");
//  ASSERT_TRUE(dataSpecification.getIdentification() == id);
//  ASSERT_TRUE((dynamic_cast<DataSpecificationContentMock&>(dataSpecification.getContent())).isMock());
}

TEST_F(DataSpecificationTest, TestContent)
{
//  simple::Identifier id;
//  std::unique_ptr<api::IDataSpecificationContent> content = util::make_unique<DataSpecificationContentMock>();
//  DataSpecification dataSpecification("id", id, std::move(content));
//
//  ASSERT_TRUE((dynamic_cast<DataSpecificationContentMock&>(dataSpecification.getContent())).isMock());
//
//  std::unique_ptr<api::IDataSpecificationContent> content2 = util::make_unique<DataSpecificationContentMock2>();
//  dataSpecification.setContent(std::move(content2));
//  ASSERT_TRUE((dynamic_cast<DataSpecificationContentMock2&>(dataSpecification.getContent())).isMock2());
}
