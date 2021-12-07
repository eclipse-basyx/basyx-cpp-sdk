/*
 * ReferenceMock.cpp
 *
 *      Author: wendel
 */

#include "BaSyx/submodel/api/qualifier/IReferable.h"
#include "ReferenceMock.hpp"
#include "BaSyx/shared/object.h"
#include "AdditionalAssertions.hpp"

#ifndef BASYX_TESTING_SUPPORT_REFERABLEMOCK_H_
#define BASYX_TESTING_SUPPORT_REFERABLEMOCK_H_

namespace basyx {
namespace testing {

class ReferableMock : public submodel::IReferable
{
public:
  struct Path
  {
    static constexpr char id[] = "testID";
    static constexpr char category[] = "testCategory";
    static constexpr char description_lang[] = "testLang";
    static constexpr char description_text[] = "testText";
  };

  ReferableMock()
  {
    this->map = basyx::object::make_map();
    map.insertKey(submodel::IReferable::Path::Category, Path::category);
    map.insertKey(submodel::IReferable::Path::Description, submodel::Description{Path::description_lang, Path::description_text}.getMap());
    map.insertKey(submodel::IReferable::Path::IdShort, Path::id);
    map.insertKey(submodel::IReferable::Path::Parent, ReferenceMock().getMap());
  }

  // Inherited via IReferable
  virtual std::string getIdShort() const override
  {
    return Path::id;
  }

  virtual std::string getCategory() const override
  {
    return Path::category;
  }

  virtual submodel::Description getDescription() const override
  {
    return submodel::Description(Path::description_lang, Path::description_text);
  }

  virtual std::shared_ptr<submodel::IReference> getParent() const override
  {
    return std::make_shared<ReferenceMock>();
  }

  basyx::object getMap()
  {
    return this->map;
  }

  basyx::object map;
};

static void assertTestingReferable(basyx::object obj)
{
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IReferable::Path::Category, ReferableMock::Path::category);
  assertions::AssertMapContainsValue<submodel::Description>
    (obj, submodel::IReferable::Path::Description, submodel::Description{ReferableMock::Path::description_lang, ReferableMock::Path::description_text});
  assertions::AssertMapContainsValue<std::string>(obj, submodel::IReferable::Path::IdShort, ReferableMock::Path::id);
}

static submodel::Description testingDescription()
{
  return submodel::Description(ReferableMock::Path::description_lang, ReferableMock::Path::description_text);
}

}
}

#endif
