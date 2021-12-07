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
 * test_Identifiable.cpp
 *
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include "BaSyx/submodel/map/qualifier/Identifiable.h"

#include "support/IdentifiableMock.hpp"

using namespace basyx::submodel;

class IdentifiableTest : public ::testing::Test
{
protected:
  Identifiable identifiable;

  void SetUp() override
  {}

  void TearDown() override
  {
    auto map = identifiable.getMap();
    ASSERT_NO_THROW(map.getProperty(IIdentifiable::Path::Administration));
    ASSERT_NO_THROW(map.getProperty(IIdentifiable::Path::Identification));
  }
};

TEST_F(IdentifiableTest, TestSimpleConstruction)
{}

TEST_F(IdentifiableTest, TestConstructorFromObject)
{
  basyx::object obj = basyx::object::make_map();
  obj.insertKey("test", "test");
  identifiable = Identifiable(obj);

  auto map = identifiable.getMap();
  //map should further contain test
  basyx::assertions::AssertMapContainsValue<std::string>(map, "test", "test");
}

TEST_F(IdentifiableTest, TestConstructorFromOther)
{
  basyx::testing::IdentifiableMock other;

  identifiable = Identifiable(other);
  
  auto map = identifiable.getMap();
  // must be map of IdentifiableMock (see IdentifiableMock)
  basyx::testing::assertTestingIdentifiable(map);
}

TEST_F(IdentifiableTest, TestConstructorWithIdentifiableAndAdministration)
{
  std::shared_ptr<IIdentifier> identifier = std::make_shared<basyx::testing::IdentifierMock>();
  std::shared_ptr<IAdministrativeInformation> administration = std::make_shared<basyx::testing::AdministrativeInformationMock>();

  identifiable = Identifiable{*identifier, *administration};

  auto map = identifiable.getMap();

  basyx::testing::assertTestingIdentifier(map.getProperty(Identifiable::Path::Identification));
  basyx::testing::assertTestingAdministrativeInformation(map.getProperty(Identifiable::Path::Administration));
}

TEST_F(IdentifiableTest, TestLongConstructor)
{
  std::shared_ptr<IIdentifier> identifier = std::make_shared<basyx::testing::IdentifierMock>();
  std::shared_ptr<IAdministrativeInformation> administration = std::make_shared<basyx::testing::AdministrativeInformationMock>();

  identifiable = Identifiable("testVersion", "testRevision", "testIdShort", "testCategory", Description{"testLang", "testText"}, "testIDType", "testID"); 

  auto map = identifiable.getMap();
  // the identifier must be testing identifier as defined above
  basyx::testing::assertTestingIdentifier(map.getProperty(IIdentifiable::Path::Identification));
  // administration must be testing
  basyx::testing::assertTestingAdministrativeInformation(map.getProperty(IIdentifiable::Path::Administration));
  // idShort must be test
  basyx::assertions::AssertMapContainsValue<std::string>(map, IReferable::Path::IdShort, "testIdShort");
  // category must be test
  basyx::assertions::AssertMapContainsValue<std::string>(map, IReferable::Path::Category, "testCategory");
  // description must be test
  ASSERT_EQ(Description(map.getProperty(IReferable::Path::Description)), Description("testLang", "testText"));
}

TEST_F(IdentifiableTest, TestGetAdministration)
{
  // make map with testing administrative information
  basyx::object obj = basyx::object::make_map();
  obj.insertKey(IIdentifiable::Path::Administration, basyx::testing::AdministrativeInformationMock().getMap(), true);

  identifiable = Identifiable{obj};
  auto administration = identifiable.getAdministration();

  //basyx::testing::assertTestingAdministrativeInformationInterface(administration);
}

TEST_F(IdentifiableTest, TestGetIdentification)
{
  // make map with testing identification
  basyx::object obj = basyx::object::make_map();
  obj.insertKey(IIdentifiable::Path::Identification, basyx::testing::IdentifierMock().getMap(), true);

  identifiable = Identifiable{obj};
  auto identification = identifiable.getIdentification();

  basyx::testing::assertTestingIdentifierInterface(identification);
}

TEST_F(IdentifiableTest, TestSetAdministration)
{
  identifiable.setAdministration(basyx::testing::AdministrativeInformationMock());

  basyx::object administration = identifiable.getMap().getProperty(IIdentifiable::Path::Administration);

  // since administrationMock was used, object in map should contain testing information
  basyx::testing::assertTestingAdministrativeInformation(administration);
}

TEST_F(IdentifiableTest, TestSetAdministrationSharedPtr)
{
	identifiable.setAdministration(basyx::testing::AdministrativeInformationMock{});

  basyx::object administration = identifiable.getMap().getProperty(IIdentifiable::Path::Administration);

  // since administrationMock was used, object in map should contain testing information
  basyx::testing::assertTestingAdministrativeInformation(administration);
}

TEST_F(IdentifiableTest, TestSetIdentification)
{
  identifiable.setIdentification(basyx::testing::IdentifierMock());

  basyx::object administration = identifiable.getMap().getProperty(IIdentifiable::Path::Identification);

  // since IdentifierMock was used, object in map should contain testing information
  basyx::testing::assertTestingIdentifier(administration);
}

TEST_F(IdentifiableTest, TestSetIdentificationSharedPtr)
{
  identifiable.setIdentification(basyx::testing::IdentifierMock());

  basyx::object administration = identifiable.getMap().getProperty(IIdentifiable::Path::Identification);

  // since IdentifierMock was used, object in map should contain testing information
  basyx::testing::assertTestingIdentifier(administration);
}
