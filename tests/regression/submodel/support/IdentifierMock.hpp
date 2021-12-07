/*
 * IdentifierMock.h
 *
 *      Author: wendel
 */

#ifndef BASYX_TESTING_IDENTIFIERMOCK_H_
#define BASYX_TESTING_IDENTIFIERMOCK_H_

#include "BaSyx/submodel/api/identifier/IIdentifier.h"

#include "BaSyx/shared/object.h"

#include "support/AdditionalAssertions.hpp"


namespace basyx {
namespace testing { 

class IdentifierMock : public submodel::IIdentifier
{
public:
  struct Path
  {
    static constexpr char id[] = "testID";
    static constexpr char idType[] = "testIDType";
  };  
public:
  IdentifierMock()
  {
    this->map = basyx::object::make_map();
    this->map.insertKey(submodel::IIdentifier::Path::Id, Path::id, true);
    this->map.insertKey(submodel::IIdentifier::Path::IdType, Path::idType, true);
  }

  // Inherited via IIdentifier
  virtual std::string getIdType() const override
  {
    return Path::idType;
  }
  virtual std::string getId() const override
  {
    return Path::id;
  }

  basyx::object getMap()
  {
    return this->map;
  }

  basyx::object map;
};

static void assertTestingIdentifier(basyx::object obj)
{
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IIdentifier::Path::IdType, IdentifierMock::Path::idType);
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IIdentifier::Path::Id, IdentifierMock::Path::id);
}

static void assertTestingIdentifierInterface(std::shared_ptr<submodel::IIdentifier> identifier)
{
  ASSERT_EQ(identifier->getId(), IdentifierMock::Path::id);
  ASSERT_EQ(identifier->getIdType(), IdentifierMock::Path::idType);
}

}
}

#endif
