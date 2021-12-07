/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/aas/Asset.h>

namespace basyx {
namespace aas {
namespace simple {

Asset::Asset(const std::string & idShort, const Identifier & identifier, AssetKind kind)
	: kind(kind)
	, identifiable(idShort, identifier)
	, billOfMaterialRef()
	, assetIdentificationModelRef()
{

};

bool Asset::hasAdministrativeInformation() const
{
	return this->identifiable.hasAdministrativeInformation();
};


void Asset::addDataSpecification(const Reference & reference)
{
	this->dataSpecification.addDataSpecification(reference);
}

const std::vector<Reference> Asset::getDataSpecificationReference() const
{
	return this->dataSpecification.getDataSpecificationReference();
}


AssetKind Asset::getKind()
{
	return this->kind;
};

Reference * const Asset::getAssetIdentificationModel()
{
	return &this->assetIdentificationModelRef;
};

void Asset::setAssetIdentificationModel(const api::IReference & assetIdentificationModelRef)
{
//	this->assetIdentificationModelRef = assetIdentificationModelRef;
};

Reference * const Asset::getBillOfMaterial()
{
	return &this->billOfMaterialRef;
};

void Asset::setBillOfMaterial(const api::IReference & billOfMaterialRef)
{
//	this->billOfMaterialRef = billOfMaterialRef;
};



const std::string & Asset::getIdShort() const
{
	return this->identifiable.getIdShort();
}

const std::string * const Asset::getCategory() const
{
	return this->identifiable.getCategory();
};

void Asset::setCategory(const std::string & category)
{
	this->identifiable.setCategory(category);
};

LangStringSet & Asset::getDescription()
{
	return this->identifiable.getDescription();
}

const LangStringSet & Asset::getDescription() const
{
	return this->identifiable.getDescription();
}

api::IReferable * Asset::getParent() const
{
	return this->identifiable.getParent();
}

void Asset::setParent(IReferable * parent)
{
	this->identifiable.setParent(parent);
}

const AdministrativeInformation & Asset::getAdministrativeInformation() const
{
	return this->identifiable.getAdministrativeInformation();
}

AdministrativeInformation & Asset::getAdministrativeInformation()
{
	return this->identifiable.getAdministrativeInformation();
}

Identifier Asset::getIdentification() const
{
	return this->identifiable.getIdentification();
}

simple::Reference Asset::getReference() const
{
	return this->identifiable.getReference();
};

simple::Key Asset::getKey(bool local) const
{
	return this->identifiable.getKey();
};


}
}
}