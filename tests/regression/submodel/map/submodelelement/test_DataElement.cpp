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
 * test_DataElement.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/submodelelement/DataElement.h"

#include "support/AdditionalAssertions.hpp"


using namespace basyx::submodel;

class DataElementTest : public ::testing::Test
{
protected:
  DataElement data_element;

  void SetUp() override
  {}

  void TearDown() override
  {
  }
};

TEST_F(DataElementTest, TestSimpleConstructor)
{}

TEST_F(DataElementTest, TestConstructFromObject)
{
  basyx::object obj = ModelType(IDataElement::Path::ModelType).getMap();
  obj.insertKey("testKey", "testValue");

  data_element = DataElement(obj);

  //tear down checks if ModelType is set
  basyx::assertions::AssertMapContainsValue<std::string>(data_element.getMap(), "testKey", "testValue");
}


