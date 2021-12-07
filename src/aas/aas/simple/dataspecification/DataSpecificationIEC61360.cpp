/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/dataspecification/DataSpecificationIEC61360.h>

namespace basyx {
namespace aas {
namespace simple {


DataSpecificationIEC61360::DataSpecificationIEC61360(const LangStringSet & preferredName)
	: preferredName(preferredName)
{
}

DataSpecificationIEC61360::DataSpecificationIEC61360(const std::string & langCode, const std::string & preferredName)
	: preferredName(langCode, preferredName)
{
}

LangStringSet & DataSpecificationIEC61360::PreferredName()
{
	return this->preferredName;
}

LangStringSet & DataSpecificationIEC61360::ShortName()
{
	return this->shortName;
}

LangStringSet & DataSpecificationIEC61360::Definition()
{
	return this->definition;
}

std::string * const DataSpecificationIEC61360::getUnit()
{
	return &this->unit;
}

Reference * const DataSpecificationIEC61360::getUnitId()
{
	return &this->unitId;
}

std::string * const DataSpecificationIEC61360::getSourceOfDefinition()
{
	return &this->sourceOfDefinition;
}

DataTypeIEC61360 DataSpecificationIEC61360::getDataType() const
{
	return this->dataType;
}

std::string * const DataSpecificationIEC61360::getValueFormat()
{
	if (valueFormat.empty())
		return nullptr;

	return &this->valueFormat;
}

Reference * const DataSpecificationIEC61360::getValueId()
{
	return &this->valueId;
}

LevelType DataSpecificationIEC61360::getLevelType() const
{
	return this->levelType;
}
void DataSpecificationIEC61360::setUnit(const std::string & unit)
{
	this->unit = unit;
}

void DataSpecificationIEC61360::setSourceOfDefinition(const std::string & sourceOfDefinition)
{
	this->sourceOfDefinition = sourceOfDefinition;
}

void DataSpecificationIEC61360::setDataType(DataTypeIEC61360 dataType)
{
	this->dataType = dataType;
}

void DataSpecificationIEC61360::setValueFormat(const std::string & valueFormat)
{
	this->valueFormat;
}

void DataSpecificationIEC61360::setLevelType(LevelType levelType)
{
	this->levelType = levelType;
}

}
}
}