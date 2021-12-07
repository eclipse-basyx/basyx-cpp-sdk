/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/constraint/Qualifier.h>


using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

constexpr char Qualifier::Path::ValueDataType[];
constexpr char Qualifier::Path::QualifierType[];
constexpr char Qualifier::Path::ValueType[];
constexpr char Qualifier::Path::SemanticId[];
constexpr char Qualifier::Path::ValueId[];

Qualifier::Qualifier(const std::string & qualifierType, const std::string & valueType)
{
	this->map.insertKey(Path::QualifierType, qualifierType);
	this->map.insertKey(Path::ValueType, valueType);
	this->map.insertKey(Path::ValueId, this->valueId.getMap());
}

Qualifier::Qualifier(const std::string & qualifierType,
	const std::string & valueType,
	const std::string & valueDataType,
	const api::IReference & valueId)
	: valueId(valueId)
{
	this->map.insertKey(Path::ValueDataType, valueDataType);
	this->map.insertKey(Path::QualifierType, qualifierType);
	this->map.insertKey(Path::ValueType, valueType);
	this->map.insertKey(Path::ValueId, this->valueId.getMap());
}

Qualifier::Qualifier(basyx::object obj)
  : ElementMap{}
{
  this->map.insertKey(Path::ValueType, obj.getProperty(Path::ValueType).GetStringContent());
  this->map.insertKey(Path::QualifierType, obj.getProperty(Path::QualifierType).GetStringContent());

  if ( not obj.getProperty(Path::ValueDataType).IsNull() )
    this->map.insertKey(Path::ValueDataType, obj.getProperty(Path::ValueDataType).GetStringContent());

  if ( not obj.getProperty(Path::ValueId).IsNull() )
  {
    this->valueId = Reference(obj.getProperty(Path::ValueId));
    this->map.insertKey(Path::ValueId, this->valueId.getMap());
  }

  if ( not obj.getProperty(Path::SemanticId).IsNull() )
    this->setSemanticId(util::make_unique<Reference>(obj.getProperty(Path::SemanticId)));
}

Qualifier::Qualifier(const api::IQualifier & qualifier)
	: Qualifier( qualifier.getQualifierType(), qualifier.getValueType() )
{
	if (qualifier.getValueId() != nullptr)
		this->valueId = qualifier.getValueId()->getKeys();

	if (qualifier.getValueDataType() != nullptr)
		this->setValueDataType(*qualifier.getValueDataType());
}

const std::string Qualifier::getQualifierType() const
{
	return this->map.getProperty(Path::QualifierType).Get<std::string&>();
}

const std::string Qualifier::getValueType() const
{
	return this->map.getProperty(Path::ValueType).Get<std::string&>();
}

const std::string * const Qualifier::getValueDataType() const
{
	if (!this->map.hasProperty(Path::ValueDataType))
		return nullptr;

	return &this->map.getProperty(Path::ValueDataType).Get<std::string&>();
}

void Qualifier::setValueDataType(const std::string & valueDataType)
{
	this->map.insertKey(Path::ValueDataType, valueDataType);
};

const IReference * const Qualifier::getValueId() const
{
	if (this->valueId.empty())
		return nullptr;

	return &this->valueId;
}

void Qualifier::setValueId(const IReference & reference)
{
	this->valueId = reference.getKeys();
}

bool Qualifier::operator!=(const IQualifier & other) const
{
	return this->getQualifierType() != other.getQualifierType()
		or this->getValueType() != other.getValueType()
		or this->getValueDataType() != other.getValueDataType()
		or this->getValueId() != other.getValueId();
}

const IReference * Qualifier::getSemanticId() const
{
	return this->semanticId.get();
}

void Qualifier::setSemanticId(std::unique_ptr<Reference> reference)
{
	this->semanticId = std::move(reference);
  this->map.insertKey(Path::SemanticId, this->semanticId->getMap());
}
