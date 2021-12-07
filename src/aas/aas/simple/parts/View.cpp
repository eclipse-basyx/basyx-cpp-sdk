/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/parts/View.h>

using namespace basyx::aas;
using namespace basyx::aas::simple;

View::View(const std::string &idShort, Referable * parent)
  : referable(idShort, parent)
  , dataSpec()
{}

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

void View::setSemanticId(std::unique_ptr<Reference> semanticId)
{
  this->semanticId = std::move(semanticId);
}

void View::addDataSpecification(const simple::Reference & reference)
{
	this->dataSpec.addDataSpecification(reference);
}

const std::vector<simple::Reference> View::getDataSpecificationReference() const
{
	return this->dataSpec.getDataSpecificationReference();
}

const std::string & View::getIdShort() const
{
	return this->referable.getIdShort();
}

const std::string * const View::getCategory() const
{
	return this->referable.getCategory();
};

void View::setCategory(const std::string & category)
{
	this->referable.setCategory(category);
};

LangStringSet & View::getDescription()
{
	return this->referable.getDescription();
}

const LangStringSet & View::getDescription() const
{
	return this->referable.getDescription();
}

api::IReferable * View::getParent() const
{
	return this->referable.getParent();
}

void View::setParent(IReferable * parent)
{
	this->referable.setParent(parent);
}

simple::Reference View::getReference() const
{
	return this->referable.getReference();
};

