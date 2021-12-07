/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_RELATIONSHIPELEMENT_H
#define BASYX_SUBMODEL_MAP_RELATIONSHIPELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/IRelationshipElement.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>

namespace basyx {
namespace aas {
namespace map {

class RelationshipElement 
  : public virtual api::IRelationshipElement
  , public SubmodelElement
  , public ModelType<ModelTypes::RelationshipElement>
{
public:
  struct Path {
    static constexpr char First[] = "first";
    static constexpr char Second[] = "second";
  };

private:
  Reference first, second;

public:
  RelationshipElement(const Reference & first, const Reference & second, const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
  RelationshipElement(basyx::object);

  const Reference & getFirst() const override;
  const Reference & getSecond() const override;

  virtual KeyElements getKeyElementType() const override { return KeyElements::RelationshipElement; };
};

}
}
}
#endif //BASYX_SUBMODEL_MAP_RELATIONSHIPELEMENT_H
