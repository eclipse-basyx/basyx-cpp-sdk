#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <basyx/base/elementcontainer.h>
#include <basyx/base/elementvector.h>
#include <basyx/assetadministrationshell.h>

namespace basyx
{

// ToDo: replace placeholders
using ConceptDescription = int;
// --------------------------

class Environment
{
private:
   ElementContainer<AssetAdministrationShell> aass;
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
};

};


#endif // ENVIRONMENT_H
