#pragma once

#include <basyx/base/token.h>

#include <basyx/serialization/base/serialization.h>

#include <basyx/base/elementcontainer.h>
#include <basyx/submodel.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/enums/AssetKind.h>

#include <util/optional/optional.hpp>

namespace basyx
{

using namespace basyx::base;
using namespace basyx::serialization::priv;

class Asset : 
	public Identifiable, 
	public ModelType<ModelTypes::Asset>
{
private:
   // Legacy AAS Part 1 - V2
   util::optional<AssetKind> assetKind;
   util::optional<Reference> billOfMaterialModelRef;
   util::optional<Reference> assetIdentificationModelRef;
public:
	Asset(util::string_view idShort, Identifier identifier) : Identifiable(idShort, std::move(identifier)) {};
	Asset(util::string_view idShort, util::string_view id) : Identifiable(idShort, id) {};
public:
	Asset(const Asset &) = default;
	Asset& operator=(const Asset &) = default;

	Asset(Asset &&) = default;
	Asset& operator=(Asset &&) = default;

   // Legacy AAS Part 1 - V2
   const util::optional<AssetKind> & getAssetKind() {
      return assetKind;
   };
   void setAssetKind(AssetKind kind) { this->assetKind = kind; };

   util::optional<Reference> & getBillOfMaterialModelRef() {
      return billOfMaterialModelRef;
   }
   void setBillOfMaterialModelRef(Reference bomModelRef) {
      billOfMaterialModelRef = bomModelRef;
   }

   const util::optional<Reference> & getAssetIDentificationModelRef() {
      return assetIdentificationModelRef;
   }
   const void setAssetIdentificationModelRef(Reference assetIdentModelRef) {
      assetIdentificationModelRef = assetIdentModelRef;
   }

   // Referable - special purpose
   void setIdShort(Token<Deserializer> t, std::string idShort) {
      this->Identifiable::setIdShort(idShort);
   }
   void setParent(Token<Deserializer> t, Referable * referable) {
      this->Identifiable::setParent(referable);
   }
   void setCategory(Token<Deserializer> t, std::string category) {
      this->Identifiable::setCategory(category);
   }
   void setDisplayname(Token<Deserializer> t, langstringset_t displayname) {
      this->Identifiable::setDisplayname(displayname);
   }
   void setDescription(Token<Deserializer> t, langstringset_t description) {
      this->Identifiable::setDescription(description);
   }

   // Identifiable - special purpose
   void setIdentification(Token<Deserializer> t, Identifier identifier) {
      this->Identifiable::setIdentification(identifier);
   }
   void setAdministration(Token<Deserializer> t,
                          AdministrativeInformation administrativeInformation) {
      this->Identifiable::setAdministration(administrativeInformation);
   }
};

};
