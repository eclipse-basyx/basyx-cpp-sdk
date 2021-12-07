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

#include <BaSyx/aas/map_v2/Submodel.h>
#include "support/TestingObjects.h"

using namespace basyx::aas;
using namespace basyx::aas::map;

class SubmodelTest : public ::testing::Test {};

TEST_F(SubmodelTest, TestObjectConstructor)
{
  object obj = basyx::object::make_map();

  obj.insertKey(Referable::Path::IdShort, "testing id");

  obj.insert(TestingObjects::map::testingHasDataSpecification().getMap());
  obj.insert(TestingObjects::map::testingQualifiable().getMap());

  basyx::object identifierMap = basyx::object::make_map();
  identifierMap.insertKey(Identifiable::Path::Id, "identifier");
  identifierMap.insertKey(Identifiable::Path::IdType, IdentifierType_::to_string(IdentifierType::Unknown));
  obj.insertKey(Identifiable::Path::Identifier, identifierMap);

  obj.insertKey(Referable::Path::Category, "cat");

  ElementContainer<SubmodelElement> submodelelements;
  submodelelements.addElement(util::make_unique<File>(TestingObjects::map::testingFile(1)));
  submodelelements.addElement(util::make_unique<File>(TestingObjects::map::testingFile(2)));
  obj.insertKey(Submodel::Path::SubmodelElements, submodelelements.getMap());

  obj.insertKey(Submodel::Path::SemanticId, TestingObjects::map::testingReference_1().getMap());

  AdministrativeInformation administrativeInformation("v1", "r4");
  obj.insertKey(Identifiable::Path::AdministrativeInformation, administrativeInformation.getMap());

  Submodel submodel{obj};

  ASSERT_EQ(submodel.getIdShort(), "testing id");

  ASSERT_TRUE(TestingObjects::map::testingHasDataSpecification(submodel));
  ASSERT_TRUE(TestingObjects::map::testingQualifiable(submodel));

  ASSERT_EQ(submodel.getIdentification().getId(), "identifier");
  ASSERT_EQ(submodel.getIdentification().getIdType(), IdentifierType::Unknown);

  ASSERT_EQ(*submodel.getCategory(), "cat");

  auto & subModelElements = submodel.submodelElements();
  ASSERT_TRUE(TestingObjects::map::testingFile(*subModelElements.getElement(0), 1));
  ASSERT_TRUE(TestingObjects::map::testingFile(*subModelElements.getElement(1), 2));

  ASSERT_EQ(TestingObjects::map::testingReference_1(), *submodel.getSemanticId());

  ASSERT_EQ(*submodel.getAdministrativeInformation().getVersion(), "v1");
  ASSERT_EQ(*submodel.getAdministrativeInformation().getRevision(), "r4");
}

TEST_F(SubmodelTest, TestObjectCopy)
{
  Submodel submodel{"id short", TestingObjects::simple::testingIdentifier()};

  submodel.addFormula(TestingObjects::map::testingFormula());

  submodel.addQualifier(TestingObjects::map::testingQualifier());

  submodel.addDataSpecification(TestingObjects::map::testingReference_1());

  submodel.setSemanticId(util::make_unique<Reference>(TestingObjects::map::testingReference_2()));

  submodel.setAdministrativeInformation(AdministrativeInformation("v2", "r34"));

  submodel.setDescription(TestingObjects::map::testingLangString());

  submodel.setCategory("testing cat");

  auto map = submodel.getMap();
  Submodel copied{map};

  ASSERT_EQ(copied.getIdShort(), "id short");

  ASSERT_TRUE(TestingObjects::map::testingFormula(copied.getFormulas().at(0)));

  ASSERT_TRUE(TestingObjects::map::testingQualifier(copied.getQualifiers().at(0)));

  ASSERT_EQ(TestingObjects::map::testingReference_1(), copied.getDataSpecificationReference().at(0));

  ASSERT_EQ(TestingObjects::map::testingReference_2(), *copied.getSemanticId());

  ASSERT_EQ( *copied.getAdministrativeInformation().getVersion(), "v2");
  ASSERT_EQ( *copied.getAdministrativeInformation().getRevision(), "r34");

  ASSERT_EQ(copied.getDescription().get("DE"), TestingObjects::map::testingLangString().get("DE"));
  ASSERT_EQ(copied.getDescription().get("EN"), TestingObjects::map::testingLangString().get("EN"));

  ASSERT_EQ(*copied.getCategory(), "testing cat");
}