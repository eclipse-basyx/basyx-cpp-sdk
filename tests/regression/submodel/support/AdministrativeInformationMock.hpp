/*
 * AdministrativeInformationMock.h
 *
 *      Author: wendel
 */

#ifndef BASYX_TESTING_ADMINISTRATIVEINFORMATIONMOCK_H_
#define BASYX_TESTING_ADMINISTRATIVEINFORMATIONMOCK_H_

#include "BaSyx/submodel/api/qualifier/IAdministrativeInformation.h"
#include "BaSyx/submodel/map/qualifier/AdministrativeInformation.h"

#include "ReferenceMock.hpp"
#include "support/AdditionalAssertions.hpp"

namespace basyx {
namespace testing {

class AdministrativeInformationMock : public submodel::IAdministrativeInformation
{
public:
  struct Path
  {
    static constexpr char version[] = "testVersion";
    static constexpr char revision[] = "testRevision";
  };
public:
  AdministrativeInformationMock()
  {
    this->map = basyx::object::make_map();
    this->map.insertKey(submodel::IAdministrativeInformation::Path::Version, Path::version);
    this->map.insertKey(submodel::IAdministrativeInformation::Path::Revision, Path::revision);
  }

  ~AdministrativeInformationMock() = default;

  // Inherited via IAdministrativeInformation
  virtual basyx::specificCollection_t<submodel::IReference> getDataSpecificationReferences() const override
  {
    auto collection = basyx::specificCollection_t<submodel::IReference>();
    collection.push_back(std::make_shared<ReferenceMock>());
    return collection;
  }

  virtual std::string getVersion() const override
  {
    return Path::version;
  }

  virtual std::string getRevision() const override
  {
    return Path::revision;
  }

  basyx::object getMap()
  {
    return this->map;
  }

  basyx::object map;
};

static void assertTestingAdministrativeInformation(basyx::object obj)
{
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IAdministrativeInformation::Path::Version, AdministrativeInformationMock::Path::version);
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IAdministrativeInformation::Path::Revision, AdministrativeInformationMock::Path::revision);
}

static void assertTestingAdministrativeInformationInterface(std::shared_ptr<basyx::submodel::IAdministrativeInformation> adminInfo)
{
  ASSERT_EQ(adminInfo->getRevision(), AdministrativeInformationMock::Path::revision);
  ASSERT_EQ(adminInfo->getVersion(), AdministrativeInformationMock::Path::version);
}

}
}

#endif
