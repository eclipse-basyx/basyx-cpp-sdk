#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/submodel.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/enums/AssetKind.h>

#include <util/optional/optional.hpp>

namespace basyx
{

class Asset : 
	public Identifiable, 
	public ModelType<ModelTypes::Asset>
{
private:
   // Legacy AAS Part 1 - V2
   util::optional<AssetKind> assetKind;
public:
	Asset(util::string_view idShort, Identifier identifier) : Identifiable(idShort, std::move(identifier)) {};
	Asset(util::string_view idShort, util::string_view id) : Identifiable(idShort, id) {};
public:
	Asset(const Asset &) = default;
	Asset& operator=(const Asset &) = default;

	Asset(Asset &&) = default;
	Asset& operator=(Asset &&) = default;

   // Legacy AAS Part 1 - V2
   AssetKind getAssetKind() const { return assetKind.value(); };
   void setAssetKind(AssetKind kind) { this->assetKind = kind; };
};

};
