#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/submodel.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/views/view.h>

#include <util/optional/optional.hpp>

namespace basyx
{

// ToDo: replace placeholders
using Security = int;
//using AssetInformation = int;
// --------------------------

class AssetAdministrationShell : 
	public Identifiable, 
	public ModelType<ModelTypes::AssetAdministrationShell>
{
private:
	util::optional<Security> security;
	util::optional<Reference> derivedFrom;
	ElementContainer<Submodel> submodels;
	ElementContainer<View> views;
	AssetInformation assetInformation;
public:
	AssetAdministrationShell(util::string_view idShort, Identifier identifier, AssetInformation assetInformation)
		: Identifiable(idShort, std::move(identifier)), assetInformation(std::move(assetInformation)) {};

	AssetAdministrationShell(util::string_view idShort, util::string_view id, AssetInformation assetInformation)
		: Identifiable(idShort, Identifier(id)), assetInformation(std::move(assetInformation)) {};
public:
	AssetAdministrationShell(const AssetAdministrationShell &) = default;
	AssetAdministrationShell& operator=(const AssetAdministrationShell &) = default;

	AssetAdministrationShell(AssetAdministrationShell &&) = default;
	AssetAdministrationShell& operator=(AssetAdministrationShell &&) = default;
public:
	const AssetInformation & getAssetInformation() const { return assetInformation; };
	void setAssetInformation(AssetInformation assetInformation) { this->assetInformation = std::move(assetInformation); };

	const util::optional<Security> & getSecurity() const { return security; };
	void setSecurity(Security security) { this->security = std::move(security); };

	const util::optional<Reference> & getDerivedFrom() const { return this->derivedFrom; };
	template<typename Ref> void setDerivedFrom(Ref && ref) { this->derivedFrom.emplace(std::forward<Ref>(ref)); };

	const ElementContainer<Submodel> & getSubmodels() const { return this->submodels; };
	ElementContainer<Submodel> & getSubmodels() { return this->submodels; };
	void setSubmodelElements(ElementContainer<Submodel> submodels) { this->submodels = std::move(submodels); };

	const ElementContainer<View> & getViews() const { return this->views; };
	ElementContainer<View> & getViews() { return this->views; };
	void setViews(ElementContainer<View> views) { this->views = std::move(views); };
};

};
