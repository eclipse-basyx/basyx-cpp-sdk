/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_ENTITY_H
#define BASYX_SUBMODEL_MAP_ENTITY_H

#include <BaSyx/aas/api_v2/submodelelement/IEntity.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>

namespace basyx {
namespace aas {
namespace map {

class Entity 
  : public virtual api::IEntity
  , public SubmodelElement
  , public ModelType<ModelTypes::Entity>
{
public:
  struct Path {
    static constexpr char EntityType[] = "entityType";
    static constexpr char Kind[] = "kind";
    static constexpr char Statement[] = "statement";
    static constexpr char Asset[] = "asset";
  };

private:
  ElementContainer<api::ISubmodelElement> statements;
  Reference asset;

public:
  Entity(EntityType, const std::string &, ModelingKind kind = ModelingKind::Instance);
  Entity(basyx::object);

  api::IElementContainer<ISubmodelElement> & getStatement() override;
  void addStatement(std::unique_ptr<SubmodelElement>);

  EntityType getEntityType() const override;

  const api::IReference * const getAssetRef() const override;
  void setAssetRef(const Reference & assetRef);

  virtual ModelingKind getKind() const override;
  virtual KeyElements getKeyElementType() const override { return KeyElements::Entity; };
};

}
}
}
#endif //BASYX_SUBMODEL_MAP_ENTITY_H
