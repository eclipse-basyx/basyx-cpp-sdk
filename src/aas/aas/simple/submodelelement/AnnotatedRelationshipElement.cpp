/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/AnnotatedRelationshipElement.h>


namespace basyx {
namespace aas {
namespace simple {

AnnotatedRelationshipElement::AnnotatedRelationshipElement(const Reference & first, const Reference & second, const std::string & idShort, ModelingKind kind)
  : RelationshipElement(first, second, idShort, kind)
{}

const api::IElementContainer<api::IDataElement> & AnnotatedRelationshipElement::getAnnotation() const
{
  return this->annotations;
}

void AnnotatedRelationshipElement::addAnnotation(std::unique_ptr<DataElement> dataElement)
{
  this->annotations.addElement(std::move(dataElement));
}

}
}
}
