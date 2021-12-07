/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/parts/ConceptDescription.h>


namespace basyx {
namespace aas {
namespace map {

constexpr char ConceptDescriptionPath::ModelType[];
constexpr char ConceptDescriptionPath::IsCaseOf[];
constexpr char ConceptDescriptionPath::EmbeddedDataSpecifications[];

using namespace basyx::aas::api;

ConceptDescription::ConceptDescription(const std::string & idShort,  const simple::Identifier & identifier)
  : Identifiable(idShort, identifier)
  , HasDataSpecification{}
  , vab::ElementMap{}
{
//  this->map.insertKey(ConceptDescriptionPath::IsCaseOf, this->is_case_of_refs);
  this->map.insertKey(ConceptDescriptionPath::EmbeddedDataSpecifications, this->embedded_data_specs.getMap());
}

const std::vector<std::unique_ptr<api::IReference>> & ConceptDescription::getIsCaseOf() const
{
  return this->is_case_of_refs;
}

const api::IElementContainer<api::IDataSpecification> & ConceptDescription::getEmbeddedDataSpecification() const
{
  return this->embedded_data_specs;
}

void ConceptDescription::addIsCaseOf(std::unique_ptr<Reference> reference)
{
  this->is_case_of_refs.push_back(std::move(reference));
}

void ConceptDescription::addEmbeddedDataSpecification(std::unique_ptr<DataSpecification> data_specification)
{
  this->embedded_data_specs.addElement(std::move(data_specification));
}

}
}
}
