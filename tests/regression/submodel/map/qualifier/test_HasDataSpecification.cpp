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
 * test_HasDataSpecification.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/HasDataSpecification.h"

#include "support/ReferenceMock.hpp"

using namespace basyx::submodel;
using basyx::testing::ReferenceMock;

class HasDataSpecificationTest : public ::testing::Test
{
protected:
  HasDataSpecification data_spec;
  void SetUp() override
  {}

  void TearDown() override
  {}
};

TEST_F(HasDataSpecificationTest, TestConstructFromObject)
{
  auto refs = basyx::object::make_list<basyx::object>();
  refs.insert(ReferenceMock().getMap());

  auto obj = basyx::object::make_map();
  obj.insertKey(IHasDataSpecification::Path::HasDataSpecification, refs);

  data_spec = HasDataSpecification{obj};

  auto map = data_spec.getMap();
  // data specification should be present in map
  basyx::object object_map;
  ASSERT_NO_THROW(object_map = map.getProperty(IHasDataSpecification::Path::HasDataSpecification));
  
  // data specification should be a list
  basyx::object::object_list_t list;
  ASSERT_NO_THROW(list = object_map.Get<basyx::object::object_list_t>());
  // unchanged with size 1
  ASSERT_EQ(list.size(), 1);
  // And the element should be a testing element
  ASSERT_TRUE(basyx::testing::isTestingReference(list.at(0)));
}

TEST_F(HasDataSpecificationTest, TestSimpleConstructor)
{
  auto map = data_spec.getMap();
  // data specification should be present in map
  basyx::object object_map;
  ASSERT_NO_THROW(object_map = map.getProperty(IHasDataSpecification::Path::HasDataSpecification));

  // data specification should be a list
  basyx::object::object_list_t list;
  ASSERT_NO_THROW(list = object_map.Get<basyx::object::object_list_t>());
  // ... with no element
  ASSERT_EQ(list.size(), 0);
}

TEST_F(HasDataSpecificationTest, TestConstructFromReferenceList)
{
  basyx::specificCollection_t<IReference> refs;
  refs.push_back(std::make_shared<ReferenceMock>());

  data_spec = HasDataSpecification{refs};

  auto map = data_spec.getMap();
  // data specification should be present in map
  basyx::object object_map;
  ASSERT_NO_THROW(object_map = map.getProperty(IHasDataSpecification::Path::HasDataSpecification));

  // data specification should be a list
  basyx::object::object_list_t ref_list;
  ASSERT_NO_THROW(ref_list = object_map.Get<basyx::object::object_list_t>());
  // ... with one element
  ASSERT_EQ(ref_list.size(), 1);
  // since the first is a reference element it should be represented as map
  basyx::object ref;
  auto first_obj = ref_list.at(0);
  basyx::testing::assertTestingReference(first_obj);
}

TEST_F(HasDataSpecificationTest, TestGetDataSpecificationReferencesEmpty)
{
  auto refs = data_spec.getDataSpecificationReferences();

  // The list of references should be empty
  ASSERT_EQ(refs.size(), 0);
}

TEST_F(HasDataSpecificationTest, TestGetDataSpecificationReferencesNonEmpty)
{
  auto refs = basyx::object::make_list<basyx::object>();
  refs.insert(ReferenceMock().getMap());

  auto obj = basyx::object::make_map();
  obj.insertKey(IHasDataSpecification::Path::HasDataSpecification, refs);

  // construct data spec with list
  data_spec = HasDataSpecification{obj};

  // get the references
  auto references = data_spec.getDataSpecificationReferences();

  // the list of references should be unchanged with size 1
  ASSERT_EQ(references.size(), 1);
}

TEST_F(HasDataSpecificationTest, TestSetDataSpecificationReferences)
{
  basyx::specificCollection_t<IReference> refs;
  refs.push_back(std::make_shared<ReferenceMock>());

  data_spec.setDataSpecificationReferences(refs);  

  auto map = data_spec.getMap();
  // data specification should be present in map
  basyx::object object_map;
  ASSERT_NO_THROW(object_map = map.getProperty(IHasDataSpecification::Path::HasDataSpecification));

  // data specification should be a list
  basyx::object::object_list_t ref_list;
  ASSERT_NO_THROW(ref_list = object_map.Get<basyx::object::object_list_t>());
  // ... with one element
  ASSERT_EQ(ref_list.size(), 1);
  // since the first is a reference element it should be represented as map
  basyx::object ref = ref_list.at(0);
  basyx::testing::assertTestingReference(ref);
}


