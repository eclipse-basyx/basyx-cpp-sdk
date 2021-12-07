/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_RANGE_H
#define BASYX_SUBMODEL_SIMPLE_RANGE_H

#include <BaSyx/aas/api_v2/submodelelement/IRange.h>
#include <BaSyx/aas/simple/submodelelement/DataElement.h>

namespace basyx {
namespace aas {
namespace simple {

template<typename T>
class Range
  : public virtual api::IRange<T>
  , public DataElement
{
public:
  using ValueDataType = typename api::IRange<T>::ValueDataType;
private:
  DataTypeDef dataTypeDef;
  std::unique_ptr<T> min, max;

public:
  ~Range() override = default;

  Range(const std::string & idShort, ModelingKind kind = ModelingKind::Instance)
    : DataElement(idShort, kind)
    , dataTypeDef(ValueDataType::getDataTypeDef())
  {}

  const DataTypeDef & getDataTypeDef() const override
  {
    return this->dataTypeDef;
  }

  void setMin(std::unique_ptr<T> min) override
  {
    this->min = std::move(min);
  }

  const T * const getMin() override
  {
    return this->min.get();
  }

  void setMax(std::unique_ptr<T> max) override
  {
    this->max = std::move(max);
  }

  const T * const getMax() override
  {
    return this->max.get();
  }
};

}
}
}
#endif //BASYX_SUBMODEL_RANGE_H
