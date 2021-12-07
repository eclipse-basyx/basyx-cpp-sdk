/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_ANNOTATEDRELATIONSHIPELEMENT_H
#define BASYX_SUBMODEL_SIMPLE_ANNOTATEDRELATIONSHIPELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/IAnnotatedRelationshipElement.h>
#include <BaSyx/aas/simple/submodelelement/DataElement.h>
#include <BaSyx/aas/simple/common/ElementContainer.h>
#include <BaSyx/aas/simple/submodelelement/RelationshipElement.h>

namespace basyx {
namespace aas {
namespace simple {

class AnnotatedRelationshipElement
  : public virtual api::IAnnotatedRelationshipElement
  , public RelationshipElement
{
private:
  ElementContainer<IDataElement> annotations;
public:
  AnnotatedRelationshipElement(const Reference &, const Reference &, const std::string & idShort, ModelingKind kind = ModelingKind::Instance);

  const api::IElementContainer<IDataElement> & getAnnotation() const override;
  void addAnnotation(std::unique_ptr<DataElement> dataElement);

  KeyElements getKeyElementType() const override { return KeyElements::AnnotatedRelationshipElement; };
};

}
}
}
#endif //BASYX_SUBMODEL_ANNOTATEDRELATIONSHIPELEMENT_H
