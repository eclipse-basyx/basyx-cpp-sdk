/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/constraint/Qualifier.h>


using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::simple;

Qualifier::Qualifier(const std::string & qualifierType, const std::string & valueType)
	: qualifierType(qualifierType), valueType(valueType)
{
};

Qualifier::Qualifier(const std::string & qualifierType,
	const std::string & valueType,
	const std::string & valueDataType,
	const api::IReference & valueId)
	: qualifierType(qualifierType)
	, valueType(valueType)
	, valueDataType(valueDataType)
	, valueId(valueId.getKeys())
{
};

Qualifier::Qualifier(const api::IQualifier & qualifier)
	: Qualifier( qualifier.getQualifierType(), qualifier.getValueType() )
{
	if (qualifier.getValueId() != nullptr)
		this->valueId = qualifier.getValueId()->getKeys();

	if (qualifier.getValueDataType() != nullptr)
		this->valueDataType = *qualifier.getValueDataType();
};

const std::string Qualifier::getQualifierType() const
{
	return this->qualifierType;
};

const std::string Qualifier::getValueType() const
{
	return this->valueType;
};

const std::string * const Qualifier::getValueDataType() const
{
	if (this->valueDataType.empty())
		return nullptr;

	return &this->valueDataType;
};

void Qualifier::setValueDataType(const std::string & valueDataType)
{
	this->valueDataType = valueDataType;
};

const IReference * const Qualifier::getValueId() const
{
	if (this->valueId.empty())
		return nullptr;

	return &this->valueId;
};

void Qualifier::setValueId(const IReference & reference)
{
	this->valueId = reference.getKeys();
};


bool Qualifier::operator!=(const Qualifier & other) const
{
	return this->qualifierType != other.qualifierType
		or this->valueDataType != other.valueDataType
		or this->valueType != other.valueType
		or this->valueId != other.valueId;
};

bool Qualifier::operator!=(const IQualifier & other) const
{
	return this->getQualifierType() != other.getQualifierType()
		or this->getValueType() != other.getValueType()
		or this->getValueDataType() != other.getValueDataType()
		or this->getValueId() != other.getValueId();
};

const IReference * Qualifier::getSemanticId() const
{
	if (semanticId.empty())
		return nullptr;
	return &this->semanticId;
}

void Qualifier::setSemanticId(const Reference & reference)
{
	this->semanticId = reference;
}

ModelTypes Qualifier::GetModelType() const
{
	return ModelTypes::Qualifier;
};