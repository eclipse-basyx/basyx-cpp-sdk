/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/parts/ConceptDictionary.h>


namespace basyx {
namespace aas {
namespace simple {
using namespace basyx::aas::api;

ConceptDictionary::ConceptDictionary(const std::string & idShort)
  : conceptDescriptions()
  , referable(idShort)
{}

const api::IElementContainer<api::IConceptDescription> & ConceptDictionary::getConceptDescriptions() const
{
  return this->conceptDescriptions;
}

void ConceptDictionary::addConceptDescription(std::unique_ptr<ConceptDescription> description)
{
  this->conceptDescriptions.addElement(std::move(description));
}

const std::string & ConceptDictionary::getIdShort() const
{
	return this->referable.getIdShort();
}

const std::string * const ConceptDictionary::getCategory() const
{
	return this->referable.getCategory();
};

void ConceptDictionary::setCategory(const std::string & category)
{
	this->referable.setCategory(category);
}

LangStringSet & ConceptDictionary::getDescription()
{
	return this->referable.getDescription();
}

const LangStringSet & ConceptDictionary::getDescription() const
{
	return this->referable.getDescription();
}

IReferable * ConceptDictionary::getParent() const
{
	return this->referable.getParent();
}

void ConceptDictionary::setParent(IReferable * parent)
{
	this->referable.setParent(parent);
}

simple::Reference ConceptDictionary::getReference() const
{
	return this->referable.getReference();
};


}
}
}