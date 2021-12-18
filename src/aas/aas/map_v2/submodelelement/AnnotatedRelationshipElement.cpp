/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/AnnotatedRelationshipElement.h>


namespace basyx {
namespace aas {
namespace map {

constexpr char AnnotatedRelationshipElement::Path::Annotation[];

AnnotatedRelationshipElement::AnnotatedRelationshipElement(const Reference & first, const Reference & second, const std::string & idShort, ModelingKind kind)
  : RelationshipElement(first, second, idShort, kind)
{
  this->map.insertKey(Path::Annotation, this->annotations.getList());
  this->map.insert(this->modelType.getMap());
}

AnnotatedRelationshipElement::AnnotatedRelationshipElement(basyx::object obj)
  : RelationshipElement {obj}
{
  if ( not obj.getProperty(Path::Annotation).IsNull() )
  {
    auto annotation_objects = obj.getProperty(Path::Annotation).Get<object::object_list_t>();

    for ( auto annotation : annotation_objects )
      this->annotations.addElement(SubmodelElementFactory::CreateDataElement(annotation));
  }

  this->map.insertKey(Path::Annotation, this->annotations.getList());
  this->map.insert(this->modelType.getMap());
}

const api::IElementContainer<api::IDataElement> & AnnotatedRelationshipElement::getAnnotation() const
{
  return this->annotations;
}

void AnnotatedRelationshipElement::addAnnotation(std::unique_ptr<DataElement> annotation)
{
  this->annotations.addElement(std::move(annotation));
}

ModelTypes AnnotatedRelationshipElement::GetModelType() const
{
  return this->modelType.GetModelType();
}

}
}
}
