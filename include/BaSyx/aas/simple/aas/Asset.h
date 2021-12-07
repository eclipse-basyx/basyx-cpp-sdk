/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_AAS_ASSET_H
#define BASYX_SUBMODEL_SIMPLE_AAS_ASSET_H

#include <BaSyx/aas/api_v2/aas/IAsset.h>

#include <BaSyx/aas/simple/reference/Reference.h>

namespace basyx {
namespace aas {
namespace simple {

class Asset : public api::IAsset
{
private:
	Identifiable identifiable;
	HasDataSpecification dataSpecification;

	AssetKind kind;
	Reference assetIdentificationModelRef;
	Reference billOfMaterialRef;
public:
	Asset(const std::string & idShort, const Identifier & identifier, AssetKind kind = AssetKind::Instance);
	virtual ~Asset() = default;

	virtual AssetKind getKind() override;

	virtual Reference * const getAssetIdentificationModel() override;
	virtual void setAssetIdentificationModel(const api::IReference & assetIdentificationModelRef) override;

	virtual Reference * const getBillOfMaterial() override;
	virtual void setBillOfMaterial(const api::IReference & billOfMaterialRef) override;


	// Inherited via IReferable
	virtual const std::string & getIdShort() const override;
	virtual const std::string * const getCategory() const override;
	virtual void setCategory(const std::string & category) override;
	virtual simple::LangStringSet & getDescription() override;
	virtual const simple::LangStringSet & getDescription() const override;
	virtual void setParent(api::IReferable * parent) override;
	virtual IReferable * getParent() const override;
	virtual simple::Reference getReference() const override;

	// Inherited via IIdentifiable
	virtual const AdministrativeInformation & getAdministrativeInformation() const override;
	virtual AdministrativeInformation & getAdministrativeInformation() override;

	virtual Identifier getIdentification() const override;

	virtual bool hasAdministrativeInformation() const override;

	// Inherited via IHasDataSpecification
	virtual void addDataSpecification(const Reference & reference) override;
	virtual const std::vector<Reference> getDataSpecificationReference() const override;

	virtual inline ModelTypes GetModelType() const override { return ModelTypes::Asset; };
	virtual KeyElements getKeyElementType() const override { return KeyElements::Asset; };
	virtual Key getKey(bool local = true) const override;
};

}
}
}


#endif /* BASYX_SUBMODEL_SIMPLE_AAS_ASSET_H */
