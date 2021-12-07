/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/


#include <BaSyx/aas/simple/dataspecification/DataSpecificationPhysicalUnit.h>

namespace basyx {
namespace aas {
namespace simple {

DataSpecificationPhysicalUnit::DataSpecificationPhysicalUnit(const std::string &unitName,
        const std::string &unitSymbol, const api::ILangStringSet &definition)
    : unitName(unitName)
    , unitSymbol(unitSymbol)
{
  this->setDefinition(definition);
}

const std::string &DataSpecificationPhysicalUnit::getUnitName() const
{
  return this->unitName;
}

void DataSpecificationPhysicalUnit::setUnitName(const std::string &unitName)
{
  this->unitName = unitName;
}

const std::string &DataSpecificationPhysicalUnit::getUnitSymbol() const
{
  return this->unitSymbol;
}

void DataSpecificationPhysicalUnit::setUnitSymbol(const std::string &unitSymbol)
{
  this->unitSymbol = unitSymbol;
}

LangStringSet & DataSpecificationPhysicalUnit::getDefinition()
{
  return this->definition;
}

void DataSpecificationPhysicalUnit::setDefinition(const api::ILangStringSet &definition)
{
  this->definition = LangStringSet();
  for (auto & lang_code : definition.getLanguageCodes())
  {
    this->definition.add(lang_code, definition.get(lang_code));
  }
}

const std::string * DataSpecificationPhysicalUnit::getSiNotation() const
{
  if (this->siNotation.empty())
    return nullptr;

  return &this->siNotation;
}

void DataSpecificationPhysicalUnit::setSiNotation(const std::string &siNotation)
{
  this->siNotation = siNotation;
}

const std::string * DataSpecificationPhysicalUnit::getSiName() const
{
  if (this->siName.empty())
    return nullptr;

  return &this->siName;
}

void DataSpecificationPhysicalUnit::setSiName(const std::string &siName)
{
  this->siName = siName;
}

const std::string * DataSpecificationPhysicalUnit::getDinNotation() const
{
  if (this->dinNotation.empty())
    return nullptr;

  return &this->dinNotation;
}

void DataSpecificationPhysicalUnit::setDinNotation(const std::string &dinNotation)
{
  this->dinNotation = dinNotation;
}

const std::string * DataSpecificationPhysicalUnit::getEceName() const
{
  if (this->eceName.empty())
    return nullptr;

  return &this->eceName;
}

void DataSpecificationPhysicalUnit::setEceName(const std::string &eceName)
{
  this->eceName = eceName;
}

const std::string * DataSpecificationPhysicalUnit::getEceCode() const
{
  if (this->eceCode.empty())
    return nullptr;

  return &this->eceCode;
}

void DataSpecificationPhysicalUnit::setEceCode(const std::string &eceCode)
{
  this->eceCode = eceCode;
}

const std::string * DataSpecificationPhysicalUnit::getNistName() const
{
  if (this->nistName.empty())
    return nullptr;

  return &this->nistName;
}

void DataSpecificationPhysicalUnit::setNistName(const std::string &nistName)
{
  this->nistName = nistName;
}

const std::string * DataSpecificationPhysicalUnit::getSourceOfDefinition() const
{
  if (this->sourceOfDefinition.empty())
    return nullptr;

  return &this->sourceOfDefinition;
}

void DataSpecificationPhysicalUnit::setSourceOfDefinition(const std::string &sourceOfDefinition)
{
  this->sourceOfDefinition = sourceOfDefinition;
}

const std::string * DataSpecificationPhysicalUnit::getConversionFactor() const
{
  if (this->conversionFactor.empty())
    return nullptr;

  return &this->conversionFactor;
}

void DataSpecificationPhysicalUnit::setConversionFactor(const std::string &conversionFactor)
{
  this->conversionFactor = conversionFactor;
}

const std::string * DataSpecificationPhysicalUnit::getRegistrationAuthorityId() const
{
  if (this->registrationAuthorityId.empty())
    return nullptr;

  return &this->registrationAuthorityId;
}

void DataSpecificationPhysicalUnit::setRegistrationAuthorityId(const std::string &registrationAuthorityId)
{
  this->registrationAuthorityId = registrationAuthorityId;
}

const std::string * DataSpecificationPhysicalUnit::getSupplier() const
{
  if (this->supplier.empty())
    return nullptr;

  return &this->supplier;
}

void DataSpecificationPhysicalUnit::setSupplier(const std::string &supplier)
{
  this->supplier = supplier;
}

}
}
}