/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_PARTS_VIEW_H
#define BASYX_SUBMODEL_MAP_V2_PARTS_VIEW_H

#include <BaSyx/aas/api_v2/parts/IView.h>

#include <BaSyx/vab/ElementMap.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>

namespace basyx {
namespace aas {
namespace map {

class View
  : public api::IView
  , public virtual HasDataSpecification
  , public virtual Referable
  , public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char ContainedElements[] = "containedElements";
    static constexpr char SemanticId[] = "semanticId";
  };

private:
  ElementContainer<IReferable> contained_elements;
  std::unique_ptr<Reference> semanticId;

public:
  View(const std::string & idShort, Referable * parent = nullptr);
  View(basyx::object & object, Referable * parent = nullptr);

  virtual ~View() = default;

  //inherited via api::IView
  const api::IElementContainer<IReferable> & getContainedElements() const override;

  //not inherited
  void addContainedElement(std::unique_ptr<Referable> referable);

  //inherited via IHasSemantics
  const api::IReference * getSemanticId() const override;
  void setSemanticId(std::unique_ptr<Reference> reference);

  virtual KeyElements getKeyElementType() const override { return KeyElements::View; };
};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_PARTS_VIEW_H */
