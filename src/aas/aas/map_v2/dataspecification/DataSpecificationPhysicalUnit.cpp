/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/


#include <BaSyx/aas/map_v2/dataspecification/DataSpecificationPhysicalUnit.h>

namespace basyx {
namespace aas {
namespace map {

constexpr char DataSpecificationPhysicalUnitPath::UnitName[];
constexpr char DataSpecificationPhysicalUnitPath::UnitSymbol[];
constexpr char DataSpecificationPhysicalUnitPath::Definition[];
constexpr char DataSpecificationPhysicalUnitPath::SiNotation[];
constexpr char DataSpecificationPhysicalUnitPath::SiName[];
constexpr char DataSpecificationPhysicalUnitPath::DinNotation[];
constexpr char DataSpecificationPhysicalUnitPath::EceName[];
constexpr char DataSpecificationPhysicalUnitPath::EceCode[];
constexpr char DataSpecificationPhysicalUnitPath::NistName[];
constexpr char DataSpecificationPhysicalUnitPath::SourceOfDefinition[];
constexpr char DataSpecificationPhysicalUnitPath::ConversionFactor[];
constexpr char DataSpecificationPhysicalUnitPath::RegistrationAuthorityId[];
constexpr char DataSpecificationPhysicalUnitPath::Supplier[];

map::DataSpecificationPhysicalUnit::DataSpecificationPhysicalUnit(const std::string &unitName,
                                                                  const std::string &unitSymbol,
                                                                  const api::ILangStringSet &definition)
  : vab::ElementMap{}
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::UnitName, unitName);
  this->map.insertKey(DataSpecificationPhysicalUnitPath::UnitSymbol, unitSymbol);
  this->definition = LangStringSet(definition);
  this->map.insertKey(DataSpecificationPhysicalUnitPath::Definition, this->definition.getMap());
}

const std::string &DataSpecificationPhysicalUnit::getUnitName() const
{
  return this->map.getProperty(DataSpecificationPhysicalUnitPath::UnitName).GetStringContent();
}

void DataSpecificationPhysicalUnit::setUnitName(const std::string &unitName)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::UnitName, unitName);
}

const std::string &DataSpecificationPhysicalUnit::getUnitSymbol() const
{
  return this->map.getProperty(DataSpecificationPhysicalUnitPath::UnitSymbol).GetStringContent();
}

void DataSpecificationPhysicalUnit::setUnitSymbol(const std::string &unitSymbol)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::UnitSymbol, unitSymbol);
}

LangStringSet & DataSpecificationPhysicalUnit::getDefinition()
{
  return this->definition;
}

void DataSpecificationPhysicalUnit::setDefinition(const api::ILangStringSet &definition)
{
  this->definition = LangStringSet(definition);
  this->map.insertKey(DataSpecificationPhysicalUnitPath::Definition, this->definition.getMap());
}

const std::string * DataSpecificationPhysicalUnit::getSiNotation() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::SiNotation) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::SiNotation).GetStringContent();
}

void DataSpecificationPhysicalUnit::setSiNotation(const std::string &siNotation)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::SiNotation, siNotation);
}

const std::string * DataSpecificationPhysicalUnit::getSiName() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::SiName) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::SiName).GetStringContent();
}

void DataSpecificationPhysicalUnit::setSiName(const std::string &siName)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::SiName, siName);
}

const std::string * DataSpecificationPhysicalUnit::getDinNotation() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::DinNotation) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::DinNotation).GetStringContent();
}

void DataSpecificationPhysicalUnit::setDinNotation(const std::string &dinNotation)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::DinNotation, dinNotation);
}

const std::string * DataSpecificationPhysicalUnit::getEceName() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::EceName) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::EceName).GetStringContent();
}

void DataSpecificationPhysicalUnit::setEceName(const std::string &eceName)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::EceName, eceName);
}

const std::string * DataSpecificationPhysicalUnit::getEceCode() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::EceCode) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::EceCode).GetStringContent();
}

void DataSpecificationPhysicalUnit::setEceCode(const std::string &eceCode)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::EceCode, eceCode);
}

const std::string * DataSpecificationPhysicalUnit::getNistName() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::NistName) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::NistName).GetStringContent();
}

void DataSpecificationPhysicalUnit::setNistName(const std::string &nistName)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::NistName, nistName);
}

const std::string * DataSpecificationPhysicalUnit::getSourceOfDefinition() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::SourceOfDefinition) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::SourceOfDefinition).GetStringContent();
}

void DataSpecificationPhysicalUnit::setSourceOfDefinition(const std::string &sourceOfDefinition)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::SourceOfDefinition, sourceOfDefinition);
}

const std::string * DataSpecificationPhysicalUnit::getConversionFactor() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::ConversionFactor) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::ConversionFactor).GetStringContent();
}

void DataSpecificationPhysicalUnit::setConversionFactor(const std::string &conversionFactor)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::ConversionFactor, conversionFactor);
}

const std::string * DataSpecificationPhysicalUnit::getRegistrationAuthorityId() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::RegistrationAuthorityId) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::RegistrationAuthorityId).GetStringContent();
}

void DataSpecificationPhysicalUnit::setRegistrationAuthorityId(const std::string &registrationAuthorityId)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::RegistrationAuthorityId, registrationAuthorityId);
}

const std::string * DataSpecificationPhysicalUnit::getSupplier() const
{
  if ( ! this->map.hasProperty(DataSpecificationPhysicalUnitPath::Supplier) )
    return nullptr;

  return &this->map.getProperty(DataSpecificationPhysicalUnitPath::Supplier).GetStringContent();
}

void DataSpecificationPhysicalUnit::setSupplier(const std::string &supplier)
{
  this->map.insertKey(DataSpecificationPhysicalUnitPath::Supplier, supplier);
}

}
}
}