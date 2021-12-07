/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/parts/ConceptDictionary.h>


namespace basyx {
namespace aas {
namespace map {

using namespace basyx::aas::api;

constexpr char ConceptDictionary::Path::ConceptDescriptions[];

ConceptDictionary::ConceptDictionary(const std::string & idShort)
  : vab::ElementMap{}
  , Referable(idShort)
{
  this->map.insertKey(Path::ConceptDescriptions, this->concept_descriptions.getMap());
}

const api::IElementContainer<api::IConceptDescription> & ConceptDictionary::getConceptDescriptions() const
{
  return this->concept_descriptions;
}

void ConceptDictionary::addConceptDescription(std::unique_ptr<ConceptDescription> description)
{
  this->concept_descriptions.addElement(std::move(description));
}


}
}
}
