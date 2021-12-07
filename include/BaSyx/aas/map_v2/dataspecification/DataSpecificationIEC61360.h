/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONIEC61360_H
#define BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONIEC61360_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationIEC61360.h>

#include <BaSyx/aas/map_v2/common/LangStringSet.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>
#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {
class DataSpecificationIEC61360
    : public api::IDataSpecificationIEC61360
    , public virtual vab::ElementMap
{
public:
  struct Path
  {
    static constexpr char PreferredName[] = "preferredName";
    static constexpr char ShortName[] = "shortName";
    static constexpr char Unit[] = "unit";
    static constexpr char UnitId[] = "unitId";
    static constexpr char SourceOfDefinition[] = "sourceOfDefinition";
    static constexpr char Symbol[] = "symbol";
    static constexpr char DataType[] = "dataType";
    static constexpr char Definition[] = "definition";
    static constexpr char ValueFormat[] = "valueFormat";
    static constexpr char ValueList[] = "valueList";
    static constexpr char ValueId[] = "valueId";
    static constexpr char LevelType[] = "levelType";
  };

  DataSpecificationIEC61360() = delete;
  DataSpecificationIEC61360(map::LangStringSet & preferred_name);

  api::ILangStringSet & PreferredName() override;
  api::ILangStringSet & ShortName() override;
  api::ILangStringSet & Definition() override;

  std::string * const getUnit() override;
  api::IReference * const getUnitId() override;
  std::string * const getSourceOfDefinition() override;
  std::string * const getSymbol() override;
  DataTypeIEC61360 getDataType() const override;
  std::string * const getValueFormat() override;
  /* TODO
	MISSINGTYPE const getValueList() override;
  MISSINGTYPE const getValueDataType() override;
	*/
  api::IReference * const getValueId() override;
  LevelType getLevelType() const override;


  void setPreferredName(const api::ILangStringSet & preferredName);
  void setShortName(const api::ILangStringSet & shortName);
  void setDefinition(const api::ILangStringSet & definition);
  void setUnit(const std::string & unit) override;
  void setUnitId(std::unique_ptr<api::IReference> unitId);
  void setSourceOfDefinition(const std::string & sourceOfDefinition) override;
  void setSymbol(const std::string & symbol);
  void setDataType(DataTypeIEC61360 dataType) override;
  void setValueFormat(const std::string & valueFormat) override;
  /* TODO
  void setValueList(const MISSINGTYPE);
  void setValueDataType(const MISSINGTYPE);
  */
  void setValueId(std::unique_ptr<api::IReference> valueId);
  void setLevelType(LevelType levelType) override;

private:
  map::LangStringSet preferred_name, short_name, definition;
  std::unique_ptr<api::IReference> unitId, valueId;
};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONIEC61360_H */
