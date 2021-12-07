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
 * test_Qualifier.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/qualifiable/Qualifier.h"
#include "BaSyx/submodel/map/reference/Reference.h"
#include "BaSyx/submodel/map/modeltype/ModelType.h"

using namespace basyx::submodel;

class QualifierTest : public ::testing::Test
{
protected:
  Qualifier qualifier;
  void SetUp() override
  {}

  void TearDown() override
  {
  }
};

TEST_F(QualifierTest, TestConstructor)
{}

TEST_F(QualifierTest, TestConstructor2)
{
	Reference ref;
  qualifier = Qualifier{"testType", basyx::object{1}, ref};

  auto map = qualifier.getMap();
  ASSERT_EQ(map.getProperty(IQualifier::Path::QualifierType).GetStringContent(), "testType");
  ASSERT_EQ(map.getProperty(IQualifier::Path::QualifierValue).Get<int>(), 1);
  // A reference should be set
  ASSERT_NO_THROW(map.getProperty(IQualifier::Path::QualifierValueID).Get<basyx::object::object_map_t>().at(IReference::Path::Key).Get<basyx::object::object_list_t>());
}

TEST_F(QualifierTest, TestGetQualifierType)
{
  ASSERT_EQ(qualifier.getQualifierType(), "Type not specified");
}

TEST_F(QualifierTest, TestGetQualifierValue)
{
  ASSERT_TRUE(qualifier.getQualifierValue().IsNull());
}

TEST_F(QualifierTest, TestGetQualifierValueId)
{
  //Reference ref(qualifier.getQualifierValueId());
  //ASSERT_TRUE(ref.getMap().IsNull());
}

TEST_F(QualifierTest, TestSetQualifierType)
{
  qualifier.setQualifierType("testType");

  auto map = qualifier.getMap();
  ASSERT_EQ(map.getProperty(IQualifier::Path::QualifierType).GetStringContent(), "testType");
}

TEST_F(QualifierTest, TestSetQualifierValue)
{
  qualifier.setQualifierValue(basyx::object{1});

  auto map = qualifier.getMap();
  ASSERT_EQ(map.getProperty(IQualifier::Path::QualifierValue).Get<int>(), 1);
}

TEST_F(QualifierTest, TestSetQualifierValueId)
{
	Reference ref;
	qualifier.setQualifierValueId(ref);

  auto map = qualifier.getMap();
  // A reference should be set
  ASSERT_NO_THROW(map.getProperty(IQualifier::Path::QualifierValueID).Get<basyx::object::object_map_t>().at(IReference::Path::Key).Get<basyx::object::object_list_t>());
}
