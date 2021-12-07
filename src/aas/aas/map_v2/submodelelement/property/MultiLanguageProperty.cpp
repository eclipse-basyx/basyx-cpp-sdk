/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/property/MultiLanguageProperty.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

constexpr char MultiLanguageProperty::Path::Value[];
constexpr char MultiLanguageProperty::Path::ValueId[];
constexpr char MultiLanguageProperty::Path::Kind[];

MultiLanguageProperty::MultiLanguageProperty(const std::string & idShort, ModelingKind kind)
	: DataElement(idShort, kind)
{
  this->map.insertKey(Path::Kind, ModelingKind_::to_string(kind));
}

MultiLanguageProperty::MultiLanguageProperty(basyx::object obj)
  : ElementMap{}
  , DataElement(obj)
{
  if ( not obj.getProperty(Path::Value).IsNull() )
  {
    this->value = util::make_unique<LangStringSet>(obj.getProperty(Path::Value));
    this->map.insertKey(Path::Value, this->value->getMap());
  }

  if ( not obj.getProperty(Path::ValueId).IsNull() )
  {
    this->valueId = util::make_unique<Reference>(obj.getProperty(Path::ValueId));
    this->map.insertKey(Path::ValueId, this->valueId->getMap());
  }
}

const api::ILangStringSet * const MultiLanguageProperty::getValue()
{
  if ( this->map.getProperty(Path::Value).IsNull() )
    return nullptr;

	return this->value.get();
}

void MultiLanguageProperty::setValue(std::unique_ptr<LangStringSet> langStringSet)
{
  this->value = std::move(langStringSet);
  this->map.insertKey(Path::Value, this->value->getMap());
}

const api::IReference * const MultiLanguageProperty::getValueId() const
{
  if ( this->map.getProperty(Path::Value).IsNull() )
    return nullptr;
	return this->valueId.get();
}

void MultiLanguageProperty::setValueId(std::unique_ptr<Reference> valueId)
{
	this->valueId = std::move(valueId);
	this->map.insertKey(Path::ValueId, this->valueId->getMap());
}
