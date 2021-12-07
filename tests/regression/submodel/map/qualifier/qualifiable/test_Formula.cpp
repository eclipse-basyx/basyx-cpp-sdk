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
 * test_Formula.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/qualifiable/Formula.h"
#include "BaSyx/submodel/map/modeltype/ModelType.h"
#include "BaSyx/submodel/map/reference/Reference.h"

using namespace basyx::submodel;

class FormulaTest : public ::testing::Test
{
protected:
  Formula formula;
  void SetUp() override
  {}

  void TearDown() override
  {
  }
};

TEST_F(FormulaTest, TestSimpleConstructor)
{}

TEST_F(FormulaTest, TestDependsOnConstructor)
{
  basyx::specificCollection_t<IReference> depends_on;
  depends_on.push_back(std::make_shared<Reference>());

  formula = Formula{depends_on};

  auto map = formula.getMap().Get<basyx::object::object_map_t>();
  ASSERT_EQ(map.at(IFormula::Path::Dependson).Get<basyx::object::object_list_t>().size(), 1);
}

TEST_F(FormulaTest, TestGetDependsOnEmpty)
{
  auto depends_on = formula.getDependsOn();
  ASSERT_EQ(depends_on.size(), 0);
}

TEST_F(FormulaTest, TestSetDependsOn)
{
  basyx::specificCollection_t<IReference> depends_on;
  depends_on.push_back(std::make_shared<Reference>());

  formula.setDependsOn(depends_on);

  auto map = formula.getMap().Get<basyx::object::object_map_t>();
  ASSERT_EQ(map.at(IFormula::Path::Dependson).Get<basyx::object::object_list_t>().size(), 1);
}

