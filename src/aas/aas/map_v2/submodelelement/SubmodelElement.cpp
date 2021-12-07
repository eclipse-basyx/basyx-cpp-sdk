/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

constexpr char SubmodelElement::Path::Kind[];
constexpr char SubmodelElement::Path::SemanticId[];

SubmodelElement::SubmodelElement(const std::string & idShort, ModelingKind kind)
	: Referable(idShort, nullptr)
	, HasDataSpecification()
	, semanticId()
	, vab::ElementMap{}
{
	this->map.insertKey(Path::Kind, ModelingKind_::to_string(kind));
}

SubmodelElement::SubmodelElement(basyx::object obj)
	: ElementMap{}
	, Qualifiable{obj}
	, HasDataSpecification{obj}
	, Referable{obj}
{
	this->map.insertKey(Path::Kind, obj.getProperty(Path::Kind).GetStringContent());

	if ( not obj.getProperty(Path::SemanticId).IsNull() )
  {
	  this->semanticId = util::make_unique<Reference>(obj.getProperty(Path::SemanticId));
	  this->map.insertKey(Path::SemanticId, this->semanticId->getMap());
  }
}

const api::IReference * SubmodelElement::getSemanticId() const
{
	return this->semanticId.get();
}

void SubmodelElement::setSemanticId(std::unique_ptr<Reference> semanticId)
{
	this->semanticId = std::move(semanticId);
	this->map.insertKey(Path::SemanticId, this->semanticId->getMap());
}

ModelingKind SubmodelElement::getKind() const
{
	return ModelingKind_::from_string(this->map.getProperty(Path::Kind).GetStringContent());
}
