/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_PROPERTY_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_PROPERTY_H

#include <BaSyx/aas/api_v2/submodelelement/property/IProperty.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>
#include <BaSyx/aas/map_v2/qualifier/Qualifiable.h>
#include <BaSyx/aas/api_v2/submodelelement/property/XSDAnySimpleType.h>

#include <BaSyx/shared/object.h>

namespace basyx {
namespace aas {
namespace map {

struct PropertyPath {
  static constexpr char Value[] = "value";
  static constexpr char ValueType[] = "valueType";
  static constexpr char ValueId[] = "valueId";
};

template<typename T>
class Property
  : public virtual api::IProperty
  , public virtual vab::ElementMap
  , public virtual DataElement
  , public ModelType<ModelTypes::Property>
{
private:
  std::unique_ptr<Reference> valueId;

public:
  Property(const std::string & idShort)
    : DataElement(idShort, ModelingKind::Instance)
  {
    this->setValueType(xsd_types::xsd_type<T>::getDataTypeDef());
  }

  Property(const vab::ElementMap & elementMap)
    : vab::ElementMap(elementMap.getMap())
    , DataElement(elementMap.getMap().getProperty(Referable::Path::IdShort).GetStringContent(), ModelingKind::Instance)
  {}

  virtual ~Property() = default;

  void setValue(const T & t)
  {
    this->map.insertKey(PropertyPath::Value, xsd_types::xsd_type<T>::getXSDRepresentation(t));
  }

  const T getValue() const
  {
    return xsd_types::xsd_type<T>::fromXSDRepresentation(this->map.getProperty(PropertyPath::Value));
  }

  virtual const std::string & getValueType() const override
  {
    return this->map.getProperty(PropertyPath::ValueType).template Get<std::string&>();
  }

  virtual void setValueType(const std::string & valueType) override
  {
    this->map.insertKey(PropertyPath::ValueType, valueType);
  }

  virtual void setObject(basyx::object & object) override
  {
    // store only if valuetype is defined
    if (object.hasProperty(PropertyPath::ValueType))
      this->map = object;

    // or if it's a primitive type, not null or object
    if (object.GetObjectType() == type::objectType::Primitive)
    {
      if (object.GetValueType() != type::valueType::Null && object.GetValueType() != type::valueType::Object)
        this->map.insertKey(PropertyPath::Value, object);
        this->map.insertKey(PropertyPath::ValueType, xsd_types::getPrimitiveXSDType(object.GetValueType()));
    }
  }

  virtual basyx::object getObject() override
  {
    return this->map.getProperty(PropertyPath::Value);
  }

  virtual const Reference * const getValueId() const override
  {
    if (&this->valueId)
    {
      return this->valueId.get();
    }
    return nullptr;
  }

  virtual void setValueId(const api::IReference & valueId) override
  {
    this->valueId = util::make_unique<Reference>(valueId);
    this->map.insertKey(PropertyPath::ValueId, this->valueId->getMap());
  }

  virtual KeyElements getKeyElementType() const override { return KeyElements::Property; }
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_PROPERTY_H */
