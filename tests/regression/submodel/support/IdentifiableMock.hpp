/*
 * IdentifiableMock.cpp
 *
 *      Author: wendel
 */

#ifndef BASYX_TESTING_SUPPORT_IDENTIFIABLE_MOCK_H_
#define BASYX_TESTING_SUPPORT_IDENTIFIABLE_MOCK_H_

#include "BaSyx/submodel/map/qualifier/Identifiable.h"

#include "BaSyx/shared/object.h"

#include "IdentifierMock.hpp"
#include "ReferenceMock.hpp"
#include "AdministrativeInformationMock.hpp"

#include <memory>

namespace basyx {
namespace testing {

class IdentifiableMock : public submodel::IIdentifiable
{
public:
  IdentifiableMock()
  {}


  basyx::object getMap()
  {
    return this->map;
  }

  basyx::object map;

  // Inherited via IIdentifiable
  virtual std::string getIdShort() const override
  {
    return "testIdShort";
  }
  virtual std::string getCategory() const override
  {
    return "testCategory";
  }
  virtual submodel::Description getDescription() const override
  {
    return submodel::Description{"testLang", "testText"};
  }
  virtual std::shared_ptr<submodel::IReference> getParent() const override
  {
    return std::make_shared<ReferenceMock>();
  }
  virtual std::shared_ptr<submodel::IAdministrativeInformation> getAdministration() const override
  {
    return std::make_shared<AdministrativeInformationMock>();
  }
  virtual std::shared_ptr<submodel::IIdentifier> getIdentification() const override
  {
    return std::make_shared<IdentifierMock>();
  }
};

static void assertTestingIdentifiable(basyx::object map)
{
  // the identifier must be testing identifier as defined above
  basyx::testing::assertTestingIdentifier(map.getProperty(submodel::IIdentifiable::Path::Identification));
  // administration must be testing
  basyx::testing::assertTestingAdministrativeInformation(map.getProperty(submodel::IIdentifiable::Path::Administration));
  // parent must be testing
  basyx::testing::assertTestingReference(map.getProperty(submodel::IReferable::Path::Parent));
  // idShort must be test
  basyx::assertions::AssertMapContainsValue<std::string>(map, submodel::IReferable::Path::IdShort, "testIdShort");
  // category must be test
  basyx::assertions::AssertMapContainsValue<std::string>(map, submodel::IReferable::Path::Category, "testCategory");
  // description must be test
  ASSERT_EQ(submodel::Description(map.getProperty(submodel::IReferable::Path::Description)), submodel::Description("testLang", "testText"));
}

}
}

#endif
