/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_SUBMODELELEMENT_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_SUBMODELELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>

#include <BaSyx/aas/map_v2/common/ModelType.h>
#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/map_v2/qualifier/Qualifiable.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>

namespace basyx {
namespace aas {
namespace map {

class SubmodelElement
  : public virtual api::ISubmodelElement
  , public virtual vab::ElementMap
  , public Qualifiable
  , public Referable
  , public HasDataSpecification
{
public:
  struct Path
  {
    static constexpr char Kind[] = "kind";
    static constexpr char SemanticId[] = "semanticId";
  };
private:
  std::unique_ptr<Reference> semanticId;

public:
  SubmodelElement(const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
  SubmodelElement(basyx::object);

  virtual ~SubmodelElement() = default;

  // Inherited via IHasDataSemantics
  virtual const api::IReference * getSemanticId() const override;

  void setSemanticId(std::unique_ptr<Reference> reference);

  // Inherited via IHasKind
  virtual ModelingKind getKind() const override;

  virtual KeyElements getKeyElementType() const override { return KeyElements::SubmodelElement; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_SUBMODELELEMENT_H */
