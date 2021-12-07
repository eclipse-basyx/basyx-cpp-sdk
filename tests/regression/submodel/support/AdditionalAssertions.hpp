/*
 * AdditionalAssertions.hpp
 *
 *      Author: wendel
 */

#ifndef BASYX_TESTING_ADDITONALASSERTION_HPP_
#define BASYX_TESTING_ADDITONALASSERTION_HPP_


#include <gtest/gtest.h>

#include "BaSyx/shared/object.h"
#include "BaSyx/submodel/map/modeltype/ModelType.h"

namespace basyx {
namespace assertions {

template<typename objType>
static void AssertMapContainsValue(basyx::object map, const char* path, objType value)
{
  basyx::object prop;
  ASSERT_NO_THROW(prop = map.getProperty(path)) << "At " << path << " there seems not to be any property";
  ASSERT_FALSE(prop.IsNull()) << "Object seems to be null";
  objType obj;
  ASSERT_NO_THROW(obj = objType(prop.Get<basyx::object::object_map_t>())) 
    << "Expects obj at " << path << " to be of type " << typeid(objType).name() 
    << " but is " << typeid(prop.GetValueType()).name();
  ASSERT_EQ(obj, value);
}

template<>
void AssertMapContainsValue<std::string>(basyx::object map, const char* path, std::string value)
{
  basyx::object prop;
  ASSERT_NO_THROW(prop = map.getProperty(path)) << "At " << path << " there seems not to be any property";
  ASSERT_FALSE(prop.IsNull()) << "Object seems to be null";
  std::string str;
  ASSERT_NO_THROW(str = prop.GetStringContent()) << "Expects obj at " << path 
    << " to be string but is " << typeid(prop.GetValueType()).name();
  ASSERT_EQ(str, value);
}

template<>
void AssertMapContainsValue<bool>(basyx::object map, const char* path, bool value)
{
  basyx::object prop;
  ASSERT_NO_THROW(prop = map.getProperty(path)) << "At " << path << " there seems not to be any property";
  ASSERT_FALSE(prop.IsNull()) << "Object seems to be null";
  bool val;
  ASSERT_NO_THROW(val = prop.Get<bool>()) << "Expects obj at " << path << " to be bool but is " << typeid(prop.GetValueType()).name();
  ASSERT_EQ(val, value);
}

static void AssertIsModelType(basyx::object map, const char* modelTypeName)
{
  basyx::object name_obj = map.getProperty(submodel::ModelType::Path::Name);
  ASSERT_FALSE(name_obj.IsNull()) << "ModelType name is not initialized";
  std::string name;
  ASSERT_NO_THROW(name = name_obj.GetStringContent()) << "ModelType name is no string";
  ASSERT_EQ(modelTypeName, name) << "ModelType wrong!";
  basyx::object model_map = map.getProperty(submodel::ModelType::Path::ModelType);
  ASSERT_NO_THROW(model_map.Get<basyx::object::hash_map_t<basyx::object>>()) << "ModelType map is no map";
}

static void AssertMapContains(basyx::object map, const char* path)
{
  basyx::object prop;
  ASSERT_NO_THROW(prop = map.getProperty(path)) << "At " << path << " there seems not to be any property";
  ASSERT_FALSE(prop.IsNull()) << "Asserts object not to be null";
}

}
}

#endif // !BASYX_TESTING_ADDITONALASSERTION_HPP_
