/*
 * ReferenceMock.cpp
 *
 *      Author: wendel
 */

#include "BaSyx/submodel/api/reference/IReference.h"
#include "BaSyx/shared/object.h"
#include "KeyMock.hpp"
#include "AdditionalAssertions.hpp"

#ifndef BASYX_TESTING_SUPPORT_REFERENCEMOCK_H_
#define BASYX_TESTING_SUPPORT_REFERENCEMOCK_H_

namespace basyx {
namespace testing {

class ReferenceMock : public submodel::IReference
{
public:
  ReferenceMock()
  {
    this->map = basyx::object::make_map();
    basyx::object keys = basyx::object::make_list<basyx::object>();
    keys.insert(KeyMock().getMap());
    map.insertKey(submodel::IReference::Path::Key, keys);
    map.insertKey("mock", "mock");
  }

  // Inherited via IReference
  virtual const basyx::specificCollection_t<submodel::IKey> getKeys() const override
  {
    auto keys = basyx::specificCollection_t<submodel::IKey>();
    keys.push_back(std::make_shared<KeyMock>());
    return keys;
  }

  virtual void setKeys(const basyx::specificCollection_t<submodel::IKey>& keys) override
  {}

  basyx::object getMap()
  {
    return this->map;
  }

  basyx::object map;
};

static bool isTestingReference(basyx::object object)
{
  basyx::object::object_map_t map = object.Get<basyx::object::object_map_t>();
  return("mock" == map.at("mock").GetStringContent());
}

static bool referenceObjectContainsKeyMock(basyx::object & ref_obj)
{
  auto prop = ref_obj.getProperty(submodel::IReference::Path::Key);
  auto list = prop.Get<basyx::object::object_list_t>();
  for ( auto & key : list )
  {
    if ( key.getProperty(submodel::IKey::Path::Type).GetStringContent() == KeyMock::Path::type )
      return true;
  }
  return false;
}

static void assertContainsKeyMock(std::shared_ptr<submodel::IReference> ref)
{
  auto list = ref->getKeys();
  for ( auto & key : list )
  {
    assertTestingKey(key);
  }
}

static void assertContainsKeyMock(submodel::IReference & ref)
{
  auto list = ref.getKeys();
  for ( auto & key : list )
  {
    assertTestingKey(key);
  }
}

static void assertTestingReference(basyx::object obj)
{
  ASSERT_TRUE(referenceObjectContainsKeyMock(obj));
}

static void assertTestingReference(basyx::submodel::IReference & ref)
{
  assertContainsKeyMock(ref);
}

}
}

#endif
