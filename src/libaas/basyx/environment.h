#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <basyx/base/elementcontainer.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/assetinformation.h>

namespace basyx
{

// ToDo: replace placeholders
using ConceptDescription = int;
//using AssetInformation = int;
// --------------------------

class Environment
{
public:
   using assetInformationList_t = std::vector<AssetInformation>;
private:
   ElementContainer<AssetAdministrationShell> aass;
   assetInformationList_t assetInformations;
public:
   Environment() = default;
public:
   Environment(const Environment &) = default;
   Environment& operator=(const Environment &) = default;

   Environment(Environment &&) = default;
   Environment& operator=(Environment &&) = default;
public:
   const ElementContainer<AssetAdministrationShell> & getAssetAdministrationShells() const { return this->aass; };
   ElementContainer<AssetAdministrationShell> & getAssetAdministrationShells() { return this->aass; };
   void setAssetAdministrationShells(ElementContainer<AssetAdministrationShell> aass) { this->aass = std::move(aass); };

   const assetInformationList_t & getAssetInformations() const { return this->assetInformations; };
   assetInformationList_t & getAssetInformations() { return this->assetInformations; };
   void setViews(assetInformationList_t assetInformations) { this->assetInformations = std::move(assetInformations); };
};

};


#endif // ENVIRONMENT_H
