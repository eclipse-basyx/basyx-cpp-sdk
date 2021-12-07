/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/Submodel.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::simple;

Submodel::Submodel(const std::string & idShort, const Identifier & identifier)
	: kind(ModelingKind::Instance)
	, identifiable(idShort, identifier)
{
};

IElementContainer<ISubmodelElement> & Submodel::submodelElements()
{
	return this->elementContainer;
}

const IElementContainer<ISubmodelElement> & Submodel::submodelElements() const
{
	return this->elementContainer;
}

ModelingKind Submodel::getKind() const
{
	return this->kind;
}

const std::string & Submodel::getIdShort() const
{
	return this->identifiable.getIdShort();
}

const std::string * const Submodel::getCategory() const
{
	return this->identifiable.getCategory();
};

void Submodel::setCategory(const std::string & category)
{
	this->identifiable.setCategory(category);
};

LangStringSet & Submodel::getDescription()
{
	return this->identifiable.getDescription();
}

const LangStringSet & Submodel::getDescription() const
{
	return this->identifiable.getDescription();
}

IReferable * Submodel::getParent() const
{
	return this->identifiable.getParent();
}

void Submodel::setParent(IReferable * parent)
{
	return this->identifiable.setParent(parent);
};

const AdministrativeInformation & Submodel::getAdministrativeInformation() const
{
	return this->identifiable.getAdministrativeInformation();
}

Identifier Submodel::getIdentification() const
{
	return this->identifiable.getIdentification();
}

AdministrativeInformation & Submodel::getAdministrativeInformation()
{
	return this->identifiable.getAdministrativeInformation();
}

bool Submodel::hasAdministrativeInformation() const
{
	return this->identifiable.hasAdministrativeInformation();
};

void Submodel::addDataSpecification(const Reference & reference)
{
	this->dataSpecification.addDataSpecification(reference);
}

const std::vector<Reference> Submodel::getDataSpecificationReference() const
{
	return this->dataSpecification.getDataSpecificationReference();
}

const IReference * Submodel::getSemanticId() const
{
	return this->semanticId.get();
}

void Submodel::setSemanticId(std::unique_ptr<Reference> semanticId)
{
	this->semanticId = std::move(semanticId);
}

void Submodel::addFormula(const api::IFormula & formula)
{
	this->qualifiable.addFormula(formula);
};

void Submodel::addQualifier(const api::IQualifier & qualifier)
{
	this->qualifiable.addQualifier(qualifier);
};

std::vector<simple::Formula> Submodel::getFormulas() const
{
	return this->qualifiable.getFormulas();
};

std::vector<simple::Qualifier> Submodel::getQualifiers() const
{
	return this->qualifiable.getQualifiers();
};

simple::Reference Submodel::getReference() const
{
	return this->identifiable.getReference();
};

simple::Key Submodel::getKey(bool local) const
{
	return this->identifiable.getKey();
};
