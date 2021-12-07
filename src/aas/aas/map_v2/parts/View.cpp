/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/parts/View.h>

using namespace basyx::aas;
using namespace basyx::aas::map;

constexpr char View::Path::ContainedElements[];
constexpr char View::Path::SemanticId[];

View::View(const std::string &idShort, Referable *parent)
  : vab::ElementMap{}
  , Referable(idShort, parent)
{
  this->map.insertKey(Path::ContainedElements, this->contained_elements.getMap());
}

View::View(basyx::object & obj, Referable * parent)
  : vab::ElementMap{}
  , HasDataSpecification{obj}
  , Referable{obj}
{
  this->setParent(parent);

  auto contained_element_objects = obj.getProperty(Path::ContainedElements).Get<object::object_map_t>();
  for (auto ce : contained_element_objects)
    this->addContainedElement(util::make_unique<Referable>(ce.second));

  if ( not obj.getProperty(Path::SemanticId).IsNull() )
  {
    this->setSemanticId(util::make_unique<Reference>(obj.getProperty(Path::SemanticId)));
    this->map.insertKey(Path::SemanticId, this->semanticId->getMap());
  }

  this->map.insertKey(Path::ContainedElements, this->contained_elements.getMap());
}

const api::IElementContainer<api::IReferable> & View::getContainedElements() const
{
  return this->contained_elements;
}

void View::addContainedElement(std::unique_ptr<Referable> referable)
{
  this->contained_elements.addElement(std::move(referable));
}

const api::IReference * View::getSemanticId() const
{
  return this->semanticId.get();
}

void View::setSemanticId(std::unique_ptr<Reference> reference)
{
  this->semanticId = std::move(reference);
  this->map.insertKey(Path::SemanticId, this->semanticId->getMap());
}

