#pragma once

#include <basyx/submodelelement/file.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/specificAssetId.h>

#include <basyx/enums/AssetKind.h>

#include <basyx/util/optional/optional.hpp>

namespace basyx
{

class AssetInformation
{
private:
	AssetKind assetKind;
   util::optional<Identifier> globalAssetId;
   std::vector<SpecificAssetId> specificAssetId;
   util::optional<Identifier> assetType;
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

   const util::optional<Identifier> & getGlobalAssetId() const { return this->globalAssetId; };
   void setGlobalAssetId(Identifier globalAssetId) { this->globalAssetId.emplace(std::move(globalAssetId)); };

   void addSpecificAssetId(SpecificAssetId specificAssetId) { this->specificAssetId.emplace_back(std::move(specificAssetId)); };
   const std::vector<SpecificAssetId> & getSpecificAssetIds() const { return this->specificAssetId; };
   std::vector<SpecificAssetId> & getSpecificAssetIds() { return this->specificAssetId; };

   const util::optional<Identifier> & getAssetType() const { return this->assetType; };
   void setAssetType(Identifier assetType) { this->assetType.emplace(std::move(assetType)); };

   const util::optional<File> & getDefaultThumbnail() const { return defaultThumbnail; };
   void setDefaultThumbnail(File file) { this->defaultThumbnail.emplace(std::move(file)); };
};


}

