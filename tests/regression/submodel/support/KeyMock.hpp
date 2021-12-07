/*
 * KeyMock.cpp
 *
 *      Author: wendel
 */

#ifndef BASYX_TESTING_SUPPORT_KEYMOCK_H_
#define BASYX_TESTING_SUPPORT_KEYMOCK_H_

#include "BaSyx/submodel/api/reference/IKey.h"

#include "BaSyx/shared/object.h"

#include "AdditionalAssertions.hpp"

#include <memory>

namespace basyx {
namespace testing {


class KeyMock : public submodel::IKey
{
public:
  struct Path
  {
    static constexpr char type[] = "keyMockType";
    static constexpr char value[] = "keyMockValue";
    static constexpr char idType[] = "keyMockIdType";
  };
  KeyMock()
  {
    this->map = basyx::object::make_map();
    this->map.insertKey(submodel::IKey::Path::Type, Path::type, true);
    this->map.insertKey(submodel::IKey::Path::Value, Path::value, true);
    this->map.insertKey(submodel::IKey::Path::IdType, Path::idType, true);
    this->map.insertKey<bool>(submodel::IKey::Path::Local, true, true);
  }
  ~KeyMock() = default;

  // Inherited via IKey
  std::string getType() const override
  {
    return Path::type;
  }

  bool isLocal() const override
  {
    return true;
  }

  std::string getValue() const override
  {
    return Path::value;
  }

  std::string getidType() const override
  {
    return Path::idType;
  }

  basyx::object getMap()
  {
    return this->map;
  }

  basyx::object map;
};

static void assertTestingKey(basyx::object obj)
{
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IKey::Path::Type, KeyMock::Path::type);
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IKey::Path::Value, KeyMock::Path::value);
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IKey::Path::IdType, KeyMock::Path::idType);
}

static void assertTestingKey(std::shared_ptr<submodel::IKey> key)
{
  ASSERT_EQ(key->getType(), KeyMock::Path::type);
  ASSERT_EQ(key->getValue(), KeyMock::Path::value);
  ASSERT_EQ(key->getidType(), KeyMock::Path::idType);
}

static bool isKeyMock(std::shared_ptr<submodel::IKey> key)
{
  return ((key->getType() ==KeyMock::Path::type) && (key->getValue() == KeyMock::Path::value) && (key->getidType() == KeyMock::Path::idType));
}

}
}

#endif
