/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/Entity.h>
#include <BaSyx/aas/map_v2/submodelelement/Entity.h>


namespace basyx {
namespace aas {
namespace simple {

Entity::Entity(EntityType entityType, const std::string & idShort, ModelingKind kind)
  : SubmodelElement(idShort, kind)
  , entityType(entityType)
{
  this->statements = util::make_unique<ElementContainer<api::ISubmodelElement>>();
}

api::IElementContainer<api::ISubmodelElement> & Entity::getStatement()
{
  return *this->statements;
}

void Entity::addStatement(std::unique_ptr<SubmodelElement> statement)
{
  this->statements->addElement(std::move(statement));
}

EntityType Entity::getEntityType() const
{
  return this->entityType;
}

const api::IReference * const Entity::getAssetRef() const
{
  if (assetRef.empty())
    return nullptr;

  return &assetRef;
}

void Entity::setAssetRef(const Reference & assetRef)
{
  this->assetRef = assetRef;
}

}
}
}
