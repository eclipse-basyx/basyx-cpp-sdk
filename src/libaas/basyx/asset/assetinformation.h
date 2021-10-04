#pragma once

#include <basyx/submodelelement/file.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/identifierkeyvaluepair.h>
#include <basyx/asset/asset.h>

#include <basyx/enums/AssetKind.h>

#include <util/optional/optional.hpp>

namespace basyx
{

class AssetInformation
{
private:
	AssetKind assetKind;
	util::optional<Asset> asset;
	util::optional<Reference> globalAssetIdRef;
	std::vector<IdentifierKeyValuePair> specificAssetId;
	std::vector<Reference> billOfMaterial;
	util::optional<File> defaultThumbnail;
public:
	AssetInformation(AssetKind assetkind) : assetKind(assetkind) {};

	AssetInformation(const AssetInformation & other) = default;
	AssetInformation& operator=(const AssetInformation & other) = default;

	AssetInformation(AssetInformation &&) noexcept = default;
	AssetInformation& operator=(AssetInformation &&) noexcept = default;
public:
	AssetKind getAssetKind() const { return assetKind; };
	void setAssetKind(AssetKind kind) { this->assetKind = kind; };

	void setAsset(Asset asset) { 
		//this->globalAssetIdRef = asset;
		this->asset.emplace(std::move(asset)); 
	};
	const util::optional<Asset> & getAsset() const { return asset; };

	const util::optional<Reference> & getGlobalAssetId() const { return this->globalAssetIdRef; };
	void setGlobalAssetId(Reference globalAssetId) { this->globalAssetIdRef.emplace(std::move(globalAssetId)); };

	const util::optional<File> & getDefaultThumbnail() const { return defaultThumbnail; };
	void setDefaultThumbnail(File file) { this->defaultThumbnail.emplace(std::move(file)); };

	void addBillOfMaterial(Reference bom) { this->billOfMaterial.emplace_back(std::move(bom)); };
	const std::vector<Reference> & getBillOfMaterials() const { return this->billOfMaterial; };
	std::vector<Reference> & getBillOfMaterials() { return this->billOfMaterial; };

	void addSpecificAssetId(IdentifierKeyValuePair specificAssetId) { this->specificAssetId.emplace_back(std::move(specificAssetId)); };
	const std::vector<IdentifierKeyValuePair> & getSpecificAssetIds() const { return this->specificAssetId; };
	std::vector<IdentifierKeyValuePair> & getSpecificAssetIds() { return this->specificAssetId; };
};


}

