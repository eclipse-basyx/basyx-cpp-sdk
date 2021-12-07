/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENTITY_H
#define BASYX_SUBMODEL_ENTITY_H

#include <BaSyx/aas/api_v2/submodelelement/IEntity.h>

#include <BaSyx/aas/simple/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/simple/common/ElementContainer.h>

namespace basyx {
namespace aas {
namespace simple {

class Entity
  : public virtual api::IEntity
  , public SubmodelElement
{
private:
  std::unique_ptr<ElementContainer<api::ISubmodelElement>> statements;
  EntityType entityType;
  Reference assetRef;

public:
  Entity(EntityType, const std::string &, ModelingKind kind = ModelingKind::Instance);

  api::IElementContainer<ISubmodelElement> & getStatement() override;
  void addStatement(std::unique_ptr<SubmodelElement>);

  EntityType getEntityType() const override;

  const api::IReference * const getAssetRef() const override;
  void setAssetRef(const Reference & assetRef);

};

}
}
}
#endif //BASYX_SUBMODEL_ENTITY_H
