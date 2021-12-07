/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/aas/AssetAdministrationShell.h>
#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/aas/enumerations/ModelTypes.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::simple;

AssetAdministrationShell::AssetAdministrationShell(const std::string & idShort, const Identifier & identifier, const Asset & asset)
	: identifiable(idShort, identifier)
	, asset(asset)
{
	
};

ElementContainer<IConceptDescription> & AssetAdministrationShell::getConceptDictionary()
{
	return this->conceptDictionary;
};


IAsset & basyx::aas::simple::AssetAdministrationShell::getAsset()
{
	return this->asset;
}

Reference * basyx::aas::simple::AssetAdministrationShell::getDerivedFrom()
{
	return &this->derivedFrom;
}

void basyx::aas::simple::AssetAdministrationShell::setDerivedFrom(const IReference & derivedFrom)
{
//	this->derivedFrom = dynamic_cast<Reference>(derivedFrom);
}

IAssetAdministrationShell::SubmodelContainer_t & basyx::aas::simple::AssetAdministrationShell::getSubmodels()
{
	return this->submodels;
}

const std::string & AssetAdministrationShell::getIdShort() const
{
	return this->identifiable.getIdShort();
}

const std::string * const AssetAdministrationShell::getCategory() const
{
	return this->identifiable.getCategory();
};

void AssetAdministrationShell::setCategory(const std::string & category)
{
	this->identifiable.setCategory(category);
}

LangStringSet & AssetAdministrationShell::getDescription()
{
	return this->identifiable.getDescription();
}

const LangStringSet & AssetAdministrationShell::getDescription() const
{
	return this->identifiable.getDescription();
}

IReferable * AssetAdministrationShell::getParent() const
{
	return this->identifiable.getParent();
}

void AssetAdministrationShell::setParent(IReferable * parent)
{
	this->identifiable.setParent(parent);
}


const api::IAdministrativeInformation & AssetAdministrationShell::getAdministrativeInformation() const
{
	return this->identifiable.getAdministrativeInformation();
}

api::IAdministrativeInformation & AssetAdministrationShell::getAdministrativeInformation()
{
	return this->identifiable.getAdministrativeInformation();
}

Identifier AssetAdministrationShell::getIdentification() const
{
	return this->identifiable.getIdentification();
}

bool AssetAdministrationShell::hasAdministrativeInformation() const
{
	return this->identifiable.hasAdministrativeInformation();
};


void AssetAdministrationShell::addDataSpecification(const Reference & reference)
{
	this->dataSpecification.addDataSpecification(reference);
}

const std::vector<Reference> AssetAdministrationShell::getDataSpecificationReference() const
{
	return this->dataSpecification.getDataSpecificationReference();
}

simple::Reference AssetAdministrationShell::getReference() const
{
	return this->identifiable.getReference();
};


ModelTypes AssetAdministrationShell::GetModelType() const
{
	return ModelTypes::AssetAdministrationShell;
}

simple::Key AssetAdministrationShell::getKey(bool local) const
{
	return this->identifiable.getKey();
};