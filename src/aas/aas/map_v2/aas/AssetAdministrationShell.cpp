/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/aas/AssetAdministrationShell.h>

using namespace basyx::aas;
using namespace basyx::aas::map;
using namespace basyx::aas::api;

constexpr char AssetAdministrationShell::Path::Submodels[];
constexpr char AssetAdministrationShell::Path::Asset[];

AssetAdministrationShell::AssetAdministrationShell(const std::string & idShort, const simple::Identifier & identifier, const Asset & asset)
	: Identifiable(idShort, identifier)
	, asset(asset)
	, submodels(this)
	, conceptDictionary(this)
{
	this->map.insertKey(Path::Submodels, submodels.getKeyMap());
	this->map.insertKey(Path::Asset, asset.getMap());
};


ElementContainer<IConceptDescription> & AssetAdministrationShell::getConceptDictionary()
{
	return this->conceptDictionary;
};


api::IAsset & AssetAdministrationShell::getAsset()
{
	return asset;
};

IReference * AssetAdministrationShell::getDerivedFrom()
{
	return &derivedFrom;
};

void AssetAdministrationShell::setDerivedFrom(const api::IReference & reference)
{
	// TODO:
};

AssetAdministrationShell::SubmodelContainer_t & AssetAdministrationShell::getSubmodels()
{
	return this->submodels;
};