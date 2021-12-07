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
 * test_Qualifiable.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/qualifiable/Qualifiable.h"
#include "BaSyx/submodel/map/qualifier/qualifiable/Constraint.h"

using namespace basyx::submodel;

class QualifiableTest : public ::testing::Test
{
protected:
  Qualifiable qualifiable;
  void SetUp() override
  {}

  void TearDown() override
  {
    auto map = qualifiable.getMap();
    ASSERT_NO_THROW(map.getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>());
  }
};

TEST_F(QualifiableTest, TestConstructor)
{}

TEST_F(QualifiableTest, TestConstructorFromObject)
{
  auto object = basyx::object::make_map();
  object.insertKey("test", "test");

  qualifiable = Qualifiable{object};

  auto map = qualifiable.getMap();
  ASSERT_EQ(map.getProperty("test").GetStringContent(), "test");
}

TEST_F(QualifiableTest, TestConstructionWithConstraint)
{
  Constraint constraint;

  qualifiable = Qualifiable{std::make_shared<IConstraint>(constraint)};

  // the list of constraints in the map
  auto constraints = qualifiable.getMap().getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>();
  // should only consist of one element
  ASSERT_EQ(constraints.size(), 1);
}

TEST_F(QualifiableTest, TestConstructionWithConstraints)
{
  Constraint c1;
  Constraint c2;
  basyx::specificCollection_t<IConstraint> constraints;
  constraints.push_back(std::make_shared<IConstraint>(c1));
  constraints.push_back(std::make_shared<IConstraint>(c2));

  qualifiable = Qualifiable{constraints};

  // the list of constraints in the map
  auto constraints_from_map = qualifiable.getMap().getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>();
  // should consist of two elements
  ASSERT_EQ(constraints_from_map.size(), 2);
}

TEST_F(QualifiableTest, TestConstructionFromOther)
{
  Constraint c1;
  Constraint c2;
  basyx::specificCollection_t<IConstraint> constraints;
  constraints.push_back(std::make_shared<IConstraint>(c1));
  constraints.push_back(std::make_shared<IConstraint>(c2));

  qualifiable = Qualifiable{constraints};

  Qualifiable q2{qualifiable};

  // the list of constraints in the map of the original Qualifiable
  auto constraints_from_map = qualifiable.getMap().getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>();
  // should consist of two elements
  ASSERT_EQ(constraints_from_map.size(), 2);

  // as well as the list of constraints in the map from the retrieved Qualifiable
  auto constraints_from_q2 = q2.getMap().getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>();
  // should consist of two elements
  ASSERT_EQ(constraints_from_q2.size(), 2);
}

TEST_F(QualifiableTest, TestSetQualifier)
{
  Constraint c1;
  Constraint c2;
  basyx::specificCollection_t<IConstraint> constraints;
  constraints.push_back(std::make_shared<IConstraint>(c1));
  constraints.push_back(std::make_shared<IConstraint>(c2));

  qualifiable = Qualifiable{constraints};

  // the list of constraints in the map
  auto constraints_from_map = qualifiable.getMap().getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>();
  // should consist of two elements
  ASSERT_EQ(constraints_from_map.size(), 2);

  // and after pop out one element
  constraints.pop_back();
  qualifiable.setQualifier(constraints);
  // the list of constraints in the map
  constraints_from_map = qualifiable.getMap().getProperty(IQualifiable::Path::Constraints).Get<basyx::object::object_list_t>();
  // should only consist of one element
  ASSERT_EQ(constraints_from_map.size(), 1);
}

TEST_F(QualifiableTest, TestGetQualifier)
{
  Constraint constr;

  // construct Qualifiable from object containing constraint
  auto map = basyx::object::make_map();
  auto constr_list = basyx::object::make_list<basyx::object>();
  constr_list.insert(constr.getMap());
  map.insertKey(IQualifiable::Path::Constraints, constr_list);
  qualifiable = Qualifiable{map};

  // get list of qualifiers
  auto constraints = qualifiable.getQualifier();
  // there should be one qualifier in list
  ASSERT_EQ(constraints.size(), 1);
}
