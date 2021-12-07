/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONPHYSICALUNIT_H
#define BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONPHYSICALUNIT_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationPhysicalUnit.h>
#include <BaSyx/aas/map_v2/common/LangStringSet.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

struct DataSpecificationPhysicalUnitPath
{
  static constexpr char UnitName[] = "UnitName";
  static constexpr char UnitSymbol[] = "UnitSymbol";
  static constexpr char Definition[] = "Definition";
  static constexpr char SiNotation[] = "SiNotation";
  static constexpr char SiName[] = "SiName";
  static constexpr char DinNotation[] = "DinNotation";
  static constexpr char EceName[] = "EceName";
  static constexpr char EceCode[] = "EceCode";
  static constexpr char NistName[] = "NistName";
  static constexpr char SourceOfDefinition[] = "SourceOfDefinition";
  static constexpr char ConversionFactor[] = "ConversionFactor";
  static constexpr char RegistrationAuthorityId[] = "RegistrationAuthorityId";
  static constexpr char Supplier[] = "Supplier";
};

class DataSpecificationPhysicalUnit
    : public api::IDataSpecificationPhysicalUnit
    , public virtual vab::ElementMap
{
private:
  LangStringSet definition;

public:
  DataSpecificationPhysicalUnit(const std::string & unitName, const std::string & unitSymbol, const api::ILangStringSet & definition);

  const std::string & getUnitName() const override;
  void setUnitName(const std::string & unitName) override;

  const std::string & getUnitSymbol() const override;
  void setUnitSymbol(const std::string & unitSymbol) override;

  LangStringSet & getDefinition() override;
  void setDefinition(const api::ILangStringSet & unitName) override;

  const std::string * getSiNotation() const override;
  void setSiNotation(const std::string & SiNotation) override;

  const std::string * getSiName() const override;
  void setSiName(const std::string & SiName) override;

  const std::string * getDinNotation() const override;
  void setDinNotation(const std::string & DinNotation) override;

  const std::string * getEceName() const override;
  void setEceName(const std::string & EceName) override;

  const std::string * getEceCode() const override;
  void setEceCode(const std::string & EceCode) override;

  const std::string * getNistName() const override;
  void setNistName(const std::string & NistName) override;

  const std::string * getSourceOfDefinition() const override;
  void setSourceOfDefinition(const std::string & SourceOfDefinition) override;

  const std::string * getConversionFactor() const override;
  void setConversionFactor(const std::string & ConversionFactor) override;

  const std::string * getRegistrationAuthorityId() const override;
  void setRegistrationAuthorityId(const std::string & RegistrationAuthorityId) override;

  const std::string * getSupplier() const override;
  void setSupplier(const std::string & Supplier) override;


};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONPHYSICALUNIT_H */
