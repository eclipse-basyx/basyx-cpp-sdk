/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/Entity.h>


namespace basyx {
namespace aas {
namespace map {

constexpr char Entity::Path::EntityType[];
constexpr char Entity::Path::Kind[];
constexpr char Entity::Path::Asset[];
constexpr char Entity::Path::Statement[];

Entity::Entity(EntityType entityType, const std::string & idShort, ModelingKind kind)
  : SubmodelElement(idShort, kind)
{
  this->map.insertKey(Path::EntityType, EntityType_::to_string(entityType));
  this->map.insertKey(Path::Statement, statements.getMap());
}

Entity::Entity(basyx::object obj)
  : SubmodelElement(obj)
{
  this->map.insertKey(Path::EntityType, obj.getProperty(Path::EntityType).GetStringContent());
  this->map.insertKey(Path::Statement, statements.getMap());

  if ( not obj.getProperty(Path::Asset).IsNull() )
  {
    Reference asset{obj.getProperty(Path::Asset)};
    this->setAssetRef(asset);
  }

  if ( not obj.getProperty(Path::Statement).IsNull() )
  {
    auto obj_statements = obj.getProperty(Path::Statement).Get<object::hash_map_t<object>>();
    for (auto statement : obj_statements)
    {
      auto new_statement = SubmodelElementFactory::Create(statement.second);
      this->addStatement(std::move(new_statement));
    }
  }
}

api::IElementContainer<api::ISubmodelElement> & Entity::getStatement()
{
  return this->statements;
}

void Entity::addStatement(std::unique_ptr<SubmodelElement> statement)
{
  this->statements.addElement(std::move(statement));
}

EntityType Entity::getEntityType() const
{
  return EntityType_::from_string(this->map.getProperty(Path::EntityType).GetStringContent());
}

const api::IReference * const Entity::getAssetRef() const
{
  if (this->map.getProperty(Path::Asset).IsNull())
    return nullptr;
  return &this->asset;
}

void Entity::setAssetRef(const Reference & assetRef)
{
  this->asset = assetRef;
  this->map.insertKey(Path::Asset, asset.getMap());
}

ModelingKind Entity::getKind() const
{
  return ModelingKind_::from_string(this->map.getProperty(Path::Kind).GetStringContent());
}

}
}
}
