/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/dataspecification/DataSpecificationIEC61360.h>


namespace basyx {
namespace aas {
namespace map {
using namespace basyx::aas::api;

constexpr char DataSpecificationIEC61360::Path::PreferredName[];
constexpr char DataSpecificationIEC61360::Path::ShortName[];
constexpr char DataSpecificationIEC61360::Path::Unit[];
constexpr char DataSpecificationIEC61360::Path::UnitId[];
constexpr char DataSpecificationIEC61360::Path::SourceOfDefinition[];
constexpr char DataSpecificationIEC61360::Path::Symbol[];
constexpr char DataSpecificationIEC61360::Path::DataType[];
constexpr char DataSpecificationIEC61360::Path::Definition[];
constexpr char DataSpecificationIEC61360::Path::ValueFormat[];
constexpr char DataSpecificationIEC61360::Path::ValueList[];
constexpr char DataSpecificationIEC61360::Path::ValueId[];
constexpr char DataSpecificationIEC61360::Path::LevelType[];

DataSpecificationIEC61360::DataSpecificationIEC61360(map::LangStringSet & preferred_name)
  : vab::ElementMap{}
  , preferred_name(preferred_name)
{
  this->map.insertKey(Path::PreferredName, this->preferred_name.getMap());
}

api::ILangStringSet & DataSpecificationIEC61360::PreferredName()
{
  return this->preferred_name;
}

api::ILangStringSet & DataSpecificationIEC61360::ShortName()
{
  return this->short_name;
}

api::ILangStringSet & DataSpecificationIEC61360::Definition()
{
  return this->definition;
}

std::string * const DataSpecificationIEC61360::getUnit()
{
  auto unit = this->map.getProperty(Path::Unit);
  if (unit.IsNull())
    return nullptr;

  return &unit.Get<std::string&>();
}

api::IReference * const DataSpecificationIEC61360::getUnitId()
{
  return this->unitId.get();
}

std::string * const DataSpecificationIEC61360::getSourceOfDefinition()
{
  auto source_of_definition = this->map.getProperty(Path::SourceOfDefinition);
  if (source_of_definition.IsNull())
    return nullptr;

  return &source_of_definition.Get<std::string&>();
}

std::string *const DataSpecificationIEC61360::getSymbol()
{
  auto symbol = this->map.getProperty(Path::Symbol);
  if (symbol.IsNull())
    return nullptr;

  return &symbol.Get<std::string&>();
}

DataTypeIEC61360 DataSpecificationIEC61360::getDataType() const
{
  auto data_type = this->map.getProperty(Path::DataType);
  if (data_type.IsNull())
    return DataTypeIEC61360::Undefined;
  return DataTypeIEC61360_::from_string(data_type.GetStringContent());
}

std::string * const DataSpecificationIEC61360::getValueFormat()
{
  auto value_format = this->map.getProperty(Path::ValueFormat);
  if (value_format.IsNull())
    return nullptr;

  return &value_format.Get<std::string&>();
}

api::IReference * const DataSpecificationIEC61360::getValueId()
{
  return this->valueId.get();
}

LevelType DataSpecificationIEC61360::getLevelType() const
{
  auto level_type = this->map.getProperty(Path::LevelType);
  if (level_type.IsNull())
    return LevelType::Undefined;
  return LevelType_::from_string(level_type.GetStringContent());
}

void DataSpecificationIEC61360::setPreferredName(const api::ILangStringSet & preferredName)
{
  this->preferred_name = LangStringSet(preferredName);
}

void DataSpecificationIEC61360::setShortName(const api::ILangStringSet &shortName)
{
  this->short_name = LangStringSet(shortName);
}

void DataSpecificationIEC61360::setDefinition(const api::ILangStringSet &definition)
{
  this->definition = LangStringSet(definition);
}

void DataSpecificationIEC61360::setUnit(const std::string & unit)
{
  this->map.insertKey(Path::Unit, unit);
}

void DataSpecificationIEC61360::setSourceOfDefinition(const std::string & sourceOfDefinition)
{
  this->map.insertKey(Path::SourceOfDefinition, sourceOfDefinition);
}

void DataSpecificationIEC61360::setDataType(DataTypeIEC61360 dataType)
{
  this->map.insertKey(Path::DataType, DataTypeIEC61360_::to_string(dataType));
}

void DataSpecificationIEC61360::setValueFormat(const std::string & valueFormat)
{
  this->map.insertKey(Path::ValueFormat, valueFormat);
}

void DataSpecificationIEC61360::setUnitId(std::unique_ptr<api::IReference> unit_id)
{
  //Assume that map version of DataSpecification only uses map version of Reference
  this->unitId.reset(unit_id.release());
  auto unit_id_ptr = dynamic_cast<map::Reference*>(this->unitId.get());
  if (!unit_id_ptr)
	  return;

  this->map.insertKey(Path::UnitId, unit_id_ptr->getMap());
}

void DataSpecificationIEC61360::setSymbol(const std::string &symbol)
{
  this->map.insertKey(Path::Symbol, symbol);
}

void DataSpecificationIEC61360::setValueId(std::unique_ptr<api::IReference> valueId)
{
  //Assume that map version of DataSpecification only uses map version of Reference
  this->valueId = std::move(valueId);
  auto value_id_ptr = dynamic_cast<map::Reference*>(this->valueId.get());
  if (!value_id_ptr)
	  return;

  this->map.insertKey(Path::ValueId, value_id_ptr->getMap());
}

void DataSpecificationIEC61360::setLevelType(LevelType levelType)
{
  this->map.insertKey(Path::LevelType, LevelType_::to_string(levelType));
}

}
}
}
