#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/assetadministrationshell.h>

namespace basyx
{

// ToDo: replace placeholders
using ConceptDescription = int;
using AssetInformation = int;
// --------------------------

class Environment
{
private:
   ElementContainer<AssetAdministrationShell> aass;
   ElementContainer<AssetInformation> assetInformations;

public:
   Environment() {};
public:
   Environment(const Environment &) = default;
   Environment& operator=(const Environment &) = default;

   Environment(Environment &&) = default;
   Environment& operator=(Environment &&) = default;
public:
   const ElementContainer<AssetAdministrationShell> & getAssetAdministrationShells() const { return this->aass; };
   ElementContainer<AssetAdministrationShell> & getAssetAdministrationShells() { return this->aass; };
   void setAssetAdministrationShells(ElementContainer<AssetAdministrationShell> aass) { this->aass = std::move(aass); };

   const ElementContainer<AssetInformation> & getAssetInformations() const { return this->assetInformations; };
   ElementContainer<AssetInformation> & getAssetInformations() { return this->assetInformations; };
   void setViews(ElementContainer<AssetInformation> assetInformations) { this->assetInformations = std::move(assetInformations); };
};

};


#endif // ENVIRONMENT_H
