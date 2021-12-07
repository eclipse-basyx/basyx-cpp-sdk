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

#include "BaSyx/aas/map_v2/dataspecification/DataSpecificationIEC61360.h"

using namespace basyx::aas::map;
using namespace basyx::aas;

class DataSpecificationIEC61360Test : public ::testing::Test
{
protected:
  std::unique_ptr<DataSpecificationIEC61360> data_spec;
  map::LangStringSet preferred_name;
  void SetUp() override
  {
    preferred_name.add("EN", "TestDataSpecification");
    this->data_spec = util::make_unique<DataSpecificationIEC61360>(preferred_name);
  }
};

TEST_F(DataSpecificationIEC61360Test, TestPreferredName)
{
  ASSERT_TRUE(this->data_spec->PreferredName() == this->preferred_name);

  map::LangStringSet new_preferred_name;
  new_preferred_name.add("EN", "NewTestDataSpecification");

  this->data_spec->setPreferredName(new_preferred_name);

  ASSERT_TRUE(data_spec->PreferredName() == new_preferred_name);
}

TEST_F(DataSpecificationIEC61360Test, TestShortName)
{
  ASSERT_TRUE(this->data_spec->ShortName().empty());

  map::LangStringSet shortName;
  shortName.add("EN", "TestDataSpec");
  this->data_spec->setShortName(shortName);

  ASSERT_TRUE(this->data_spec->ShortName() == shortName);
}

TEST_F(DataSpecificationIEC61360Test, TestDefinition)
{
  ASSERT_TRUE(this->data_spec->Definition().empty());

  map::LangStringSet definition;
  definition.add("EN", "Definition");
  definition.add("DE", "Definition");

  this->data_spec->setDefinition(definition);
  ASSERT_TRUE(this->data_spec->Definition() == definition);
}

TEST_F(DataSpecificationIEC61360Test, TestUnit)
 {
  ASSERT_EQ(this->data_spec->getUnit(), nullptr);

  this->data_spec->setUnit("testUnit");
  ASSERT_EQ(*this->data_spec->getUnit(), std::string("testUnit"));
}

TEST_F(DataSpecificationIEC61360Test, TestSourceOfDefinition)
 {
  ASSERT_EQ(this->data_spec->getSourceOfDefinition(), nullptr);

  this->data_spec->setSourceOfDefinition("testSourceOfDefinition");
  ASSERT_EQ(*this->data_spec->getSourceOfDefinition(), std::string("testSourceOfDefinition"));
}

TEST_F(DataSpecificationIEC61360Test, TestSymbol)
 {
  ASSERT_EQ(this->data_spec->getSymbol(), nullptr);

  this->data_spec->setSymbol("testSymbol");
  ASSERT_EQ(*this->data_spec->getSymbol(), std::string("testSymbol"));
}

TEST_F(DataSpecificationIEC61360Test, TestValueFormat)
 {
  ASSERT_EQ(this->data_spec->getValueFormat(), nullptr);

  this->data_spec->setValueFormat("testValueFormat");
  ASSERT_EQ(*this->data_spec->getValueFormat(), std::string("testValueFormat"));
}

TEST_F(DataSpecificationIEC61360Test, TestDataType)
{
  ASSERT_EQ(this->data_spec->getDataType(), DataTypeIEC61360::Undefined);

  this->data_spec->setDataType(DataTypeIEC61360::Rational);
  ASSERT_EQ(this->data_spec->getDataType(), DataTypeIEC61360::Rational);
}

TEST_F(DataSpecificationIEC61360Test, TestLevelType)
{
  ASSERT_EQ(this->data_spec->getLevelType(), LevelType::Undefined);

  this->data_spec->setLevelType(LevelType::Min);
  ASSERT_EQ(this->data_spec->getLevelType(), LevelType::Min);
}

TEST_F(DataSpecificationIEC61360Test, TestUnitId)
{
  ASSERT_EQ(this->data_spec->getUnitId(), nullptr);

  std::unique_ptr<api::IReference> reference = util::make_unique<map::Reference>();
  this->data_spec->setUnitId(std::move(reference));
  ASSERT_NE(this->data_spec->getUnitId(), nullptr);
}

TEST_F(DataSpecificationIEC61360Test, TestValueId)
{
  ASSERT_EQ(this->data_spec->getValueId(), nullptr);

  std::unique_ptr<api::IReference> valueId = util::make_unique<map::Reference>();
  this->data_spec->setValueId(std::move(valueId));
  ASSERT_NE(this->data_spec->getValueId(), nullptr);
}