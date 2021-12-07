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

#include <BaSyx/aas/map_v2/parts/View.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class ViewTest : public ::testing::Test {};

TEST_F(ViewTest, TestObjectConstructor)
{
  // compose parent classes
  basyx::object object = TestingObjects::map::testingReferable_1().getMap();
  basyx::object hasDataSpecObj = TestingObjects::map::testingHasDataSpecification().getMap();
  object.insert(hasDataSpecObj);

  // add contained elements
  ElementContainer<Referable> contained_elements;
  contained_elements.addElement(util::make_unique<Referable>(TestingObjects::map::testingReferable_2()));
  contained_elements.addElement(util::make_unique<Referable>(TestingObjects::map::testingReferable_1()));
  object.insertKey(View::Path::ContainedElements, contained_elements.getMap());

  object.insertKey(View::Path::SemanticId, TestingObjects::map::testingReference_1().getMap());

  // build from object
  View view{object};

  // Test if testingReferable_1 is set correctly
  ASSERT_TRUE(TestingObjects::map::testingReferable_1(view));
  // is HasDataSpecification set correctly?
  ASSERT_TRUE(TestingObjects::map::testingHasDataSpecification(view));

  //test semanticId
  ASSERT_EQ(TestingObjects::map::testingReference_1(), *view.getSemanticId());

  // check if contained elements are correct
  ASSERT_TRUE( TestingObjects::map::testingReferable_2(*view.getContainedElements().getElement(0)));
  ASSERT_TRUE( TestingObjects::map::testingReferable_1(*view.getContainedElements().getElement(1)));
}

TEST_F(ViewTest, TestObjectCopy)
{
  View view(std::string("test id"));
  view.setCategory("testing view");
  view.setDescription(TestingObjects::map::testingLangString());
  view.setSemanticId(util::make_unique<Reference>(TestingObjects::map::testingReference_1()));

  view.addContainedElement(util::make_unique<Referable>(TestingObjects::map::testingReferable_1()));
  view.addContainedElement(util::make_unique<Referable>(TestingObjects::map::testingReferable_2()));

  view.addDataSpecification(simple::Reference(TestingObjects::map::testingReference_1()));
  view.addDataSpecification(simple::Reference(TestingObjects::map::testingReference_2()));

  auto map = view.getMap();
  View copied{map};

  ASSERT_EQ( "test id", copied.getIdShort());
  ASSERT_EQ( "testing view", *copied.getCategory());
  ASSERT_EQ( TestingObjects::map::testingLangString(), copied.getDescription());
  ASSERT_EQ( TestingObjects::map::testingReference_1(), *copied.getSemanticId());

  auto & ce = copied.getContainedElements();
  ASSERT_TRUE(TestingObjects::map::testingReferable_1(*ce.getElement(0)));
  ASSERT_TRUE(TestingObjects::map::testingReferable_2(*ce.getElement(1)));

  auto & ds = copied.getDataSpecificationReference();
  ASSERT_EQ( ds.at(0), TestingObjects::map::testingReference_1());
  ASSERT_EQ( ds.at(1), TestingObjects::map::testingReference_2());
}