#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <basyx/base/elementcontainer.h>
#include <basyx/base/elementvector.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/asset.h>

namespace basyx
{

// ToDo: replace placeholders
using ConceptDescription = int;
// --------------------------

class Environment
{
private:
   ElementContainer<AssetAdministrationShell> aass;
   ElementVector<Asset> assets;
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
   void setAssetAdministrationShells(ElementContainer<AssetAdministrationShell> aass) { this->aass = aass; };

   const ElementVector<Asset> & getAssets() const { return this->assets; };
   ElementVector<Asset> & getAssets() { return this->assets; };
   void setAssets(ElementVector<Asset> assets) { this->assets = std::move(assets); };
};

};


#endif // ENVIRONMENT_H
