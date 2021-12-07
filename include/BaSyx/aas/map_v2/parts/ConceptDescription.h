/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_PARTS_CONCEPTDESCRIPTION_H
#define BASYX_SUBMODEL_MAP_V2_PARTS_CONCEPTDESCRIPTION_H

#include <BaSyx/vab/ElementMap.h>
#include <BaSyx/aas/api_v2/parts/IConceptDescription.h>
#include <BaSyx/aas/api_v2/dataspecification/IDataSpecification.h>
#include <BaSyx/aas/map_v2/qualifier/Identifiable.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/map_v2/dataspecification/DataSpecification.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>


namespace basyx {
namespace aas {
namespace map {

struct ConceptDescriptionPath
{
  static constexpr char ModelType[] = "ConceptDescription";
  static constexpr char IsCaseOf[] = "isCaseOf";
  static constexpr char EmbeddedDataSpecifications[] = "embeddedDataSpecifications";
};

class ConceptDescription
  : public api::IConceptDescription
  , public virtual Identifiable
  , public virtual HasDataSpecification
{
private:
  std::vector<std::unique_ptr<api::IReference>> is_case_of_refs;
  ElementContainer<api::IDataSpecification> embedded_data_specs;

public:
  ConceptDescription(const std::string & idShort,  const simple::Identifier & identifier);

  const std::vector<std::unique_ptr<api::IReference>> & getIsCaseOf() const override;
  const api::IElementContainer<api::IDataSpecification> & getEmbeddedDataSpecification() const override;

  //not inherited
  void addIsCaseOf(std::unique_ptr<Reference> reference);
  void addEmbeddedDataSpecification(std::unique_ptr<DataSpecification> data_specification);

  virtual KeyElements getKeyElementType() const override { return KeyElements::ConceptDescription; };
};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_PARTS_CONCEPTDESCRIPTION_H */
