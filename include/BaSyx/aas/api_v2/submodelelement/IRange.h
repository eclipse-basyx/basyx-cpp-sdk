/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IRANGE_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IRANGE_H

#include <string>

#include <BaSyx/aas/api_v2/submodelelement/IDataElement.h>
#include <BaSyx/aas/api_v2/submodelelement/property/XSDAnySimpleType.h>

/**
 * Mandatory members: valueType
 */
namespace basyx {
namespace aas {

using DataTypeDef = std::string;

namespace api {

template<typename T>
class IRange
  : public virtual IDataElement
{
public:
  using ValueDataType = xsd_types::xsd_type<T>;
  virtual ~IRange() = 0;

  virtual DataTypeDef const & getDataTypeDef() const = 0;

  virtual const T * const getMin() = 0;
  virtual void setMin(std::unique_ptr<T>) = 0;

  virtual const T * const getMax() = 0;
  virtual void setMax(std::unique_ptr<T>) = 0;

  virtual KeyElements getKeyElementType() const override { return KeyElements::Range; };
};

template<typename T>
inline IRange<T>::~IRange() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IRANGE_H */
