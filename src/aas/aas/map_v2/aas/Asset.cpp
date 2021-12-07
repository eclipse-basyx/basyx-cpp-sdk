/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/aas/Asset.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::map;

constexpr char Asset::Path::Kind[];
constexpr char Asset::Path::AssetIdentificationModelRef[];
constexpr char Asset::Path::BillOfMaterialRef[];

Asset::Asset(const std::string & idShort, const simple::Identifier & identifier, AssetKind kind)
	: Identifiable(idShort, identifier)
	, billOfMaterialRef()
	, assetIdentificationModelRef()
	, vab::ElementMap()
{
	this->map.insertKey(Path::Kind, AssetKind_::to_string(kind));
	this->map.insertKey(Path::AssetIdentificationModelRef, assetIdentificationModelRef.getMap());
	this->map.insertKey(Path::BillOfMaterialRef, billOfMaterialRef.getMap());
};

AssetKind Asset::getKind()
{
	return AssetKind_::from_string(this->map.getProperty(Path::Kind).Get<std::string&>());
};

IReference * const Asset::getAssetIdentificationModel()
{
	return &this->assetIdentificationModelRef;
};

void Asset::setAssetIdentificationModel(const api::IReference & assetIdentificationModelRef)
{
//	this->assetIdentificationModelRef = assetIdentificationModelRef;
};

IReference * const Asset::getBillOfMaterial()
{
	return &this->billOfMaterialRef;
};

void Asset::setBillOfMaterial(const api::IReference & billOfMaterialRef)
{
//	this->billOfMaterialRef = billOfMaterialRef;
};