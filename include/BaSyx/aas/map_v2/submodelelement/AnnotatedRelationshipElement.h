/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_ANNOTATEDRELATIONSHIPELEMENT_H
#define BASYX_SUBMODEL_MAP_ANNOTATEDRELATIONSHIPELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/IAnnotatedRelationshipElement.h>
#include <BaSyx/aas/map_v2/submodelelement/RelationshipElement.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>
#include <BaSyx/aas/map_v2/common/ElementListContainer.h>

namespace basyx {
namespace aas {
namespace map {

class AnnotatedRelationshipElement 
  : public virtual api::IAnnotatedRelationshipElement
  , public RelationshipElement
{
public:
  struct Path {
    static constexpr char Annotation[] = "annotation";
  };
private:
  ElementListContainer<IDataElement> annotations;
  ModelType<ModelTypes::AnnotatedRelationshipElement> modelType;

public:
  AnnotatedRelationshipElement(const Reference & first, const Reference & second, const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
  AnnotatedRelationshipElement(basyx::object);

  const api::IElementContainer<IDataElement> & getAnnotation() const override;
  void addAnnotation(std::unique_ptr<DataElement> );

  virtual KeyElements getKeyElementType() const override { return KeyElements::AnnotatedRelationshipElement; };

  ModelTypes GetModelType() const override;
};

}
}
}
#endif //BASYX_SUBMODEL_MAP_ANNOTATEDRELATIONSHIPELEMENT_H
