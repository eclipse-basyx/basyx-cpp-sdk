/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONPHYSICALUNIT_H
#define BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONPHYSICALUNIT_H

#include <string>

#include <BaSyx/aas/api_v2/common/ILangStringSet.h>

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationContent.h>

namespace basyx {
namespace aas {
namespace api {

class IDataSpecificationPhysicalUnit
    : public IDataSpecificationContent
{
public:
  virtual ~IDataSpecificationPhysicalUnit() = 0;

  virtual const std::string & getUnitName() const = 0;
  virtual void setUnitName(const std::string & unitName) = 0;

  virtual const std::string & getUnitSymbol() const = 0;
  virtual void setUnitSymbol(const std::string & unitName) = 0;

  virtual ILangStringSet & getDefinition() = 0;
  virtual void setDefinition(const ILangStringSet & unitName) = 0;

  virtual const std::string * getSiNotation() const = 0;
  virtual void setSiNotation(const std::string & SiNotation) = 0;

  virtual const std::string * getSiName() const = 0;
  virtual void setSiName(const std::string & SiName) = 0;

  virtual const std::string * getDinNotation() const = 0;
  virtual void setDinNotation(const std::string & DinNotation) = 0;

  virtual const std::string * getEceName() const = 0;
  virtual void setEceName(const std::string & EceName) = 0;

  virtual const std::string * getEceCode() const = 0;
  virtual void setEceCode(const std::string & EceCode) = 0;

  virtual const std::string * getNistName() const = 0;
  virtual void setNistName(const std::string & NistName) = 0;

  virtual const std::string * getSourceOfDefinition() const = 0;
  virtual void setSourceOfDefinition(const std::string & SourceOfDefinition) = 0;

  virtual const std::string * getConversionFactor() const = 0;
  virtual void setConversionFactor(const std::string & ConversionFactor) = 0;

  virtual const std::string * getRegistrationAuthorityId() const = 0;
  virtual void setRegistrationAuthorityId(const std::string & RegistrationAuthorityId) = 0;

  virtual const std::string * getSupplier() const = 0;
  virtual void setSupplier(const std::string & Supplier) = 0;


};

inline IDataSpecificationPhysicalUnit::~IDataSpecificationPhysicalUnit() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONPHYSICALUNIT_H */
