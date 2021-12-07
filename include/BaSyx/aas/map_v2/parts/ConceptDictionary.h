/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_PARTS_CONCEPTDICTIONARY_H
#define BASYX_SUBMODEL_MAP_V2_PARTS_CONCEPTDICTIONARY_H

#include <BaSyx/aas/api_v2/parts/IConceptDictionary.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/vab/ElementMap.h>
#include <BaSyx/aas/map_v2/parts/ConceptDescription.h>

namespace basyx {
namespace aas {
namespace map {

class ConceptDictionary
    : public api::IConceptDictionary
    , public virtual Referable
    , public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char ConceptDescriptions[] = "conceptDescriptions";
  };

private:
  ElementContainer<api::IConceptDescription> concept_descriptions;

public:
  ConceptDictionary(const std::string & idShort);

  //inherited via IConceptDictionary
   const api::IElementContainer<api::IConceptDescription> & getConceptDescriptions() const override;

  // not inherited
  void addConceptDescription(std::unique_ptr<ConceptDescription> description);

  virtual KeyElements getKeyElementType() const override { return KeyElements::ConceptDictionary; };

};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_PARTS_CONCEPTDICTIONARY_H */
