/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/parts/ConceptDescription.h>

using namespace basyx::aas::simple;
using namespace basyx::aas;


ConceptDescription::ConceptDescription(const std::string & idShort, const Identifier & identifier)
	: identifiable(idShort, identifier)
{}

const api::IElementContainer<api::IDataSpecification> & ConceptDescription::getEmbeddedDataSpecification() const
{
	return this->embeddedDataSpecs;
}

const std::vector<std::unique_ptr<api::IReference>> & ConceptDescription::getIsCaseOf() const
{
	return this->isCaseOf;
}

void ConceptDescription::addEmbeddedDataSpecification(std::unique_ptr<DataSpecification> data_specification)
{
  this->embeddedDataSpecs.addElement(std::move(data_specification));
}

void ConceptDescription::addIsCaseOf(std::unique_ptr<Reference> reference)
{
  this->isCaseOf.push_back(std::move(reference));
};

// Inherited via IHasDataSpecification
void ConceptDescription::addDataSpecification(const Reference & reference)
{
	return this->dataSpec.addDataSpecification(reference);
};

const std::vector<Reference> ConceptDescription::getDataSpecificationReference() const
{
	return this->dataSpec.getDataSpecificationReference();
}


const std::string & ConceptDescription::getIdShort() const
{
	return this->identifiable.getIdShort();
}

const std::string * const ConceptDescription::getCategory() const
{
	return this->identifiable.getCategory();
};

void ConceptDescription::setCategory(const std::string & category)
{
	this->identifiable.setCategory(category);
}

LangStringSet & ConceptDescription::getDescription()
{
	return this->identifiable.getDescription();
}

const LangStringSet & ConceptDescription::getDescription() const
{
	return this->identifiable.getDescription();
}

api::IReferable * ConceptDescription::getParent() const
{
	return this->identifiable.getParent();
}

void ConceptDescription::setParent(api::IReferable * parent)
{
	this->identifiable.setParent(parent);
}

const AdministrativeInformation & ConceptDescription::getAdministrativeInformation() const
{
	return this->identifiable.getAdministrativeInformation();
}

AdministrativeInformation & ConceptDescription::getAdministrativeInformation()
{
	return this->identifiable.getAdministrativeInformation();
}

Identifier ConceptDescription::getIdentification() const
{
	return this->identifiable.getIdentification();
}

bool ConceptDescription::hasAdministrativeInformation() const
{
	return this->identifiable.hasAdministrativeInformation();
};

simple::Reference ConceptDescription::getReference() const
{
	return this->identifiable.getReference();
};