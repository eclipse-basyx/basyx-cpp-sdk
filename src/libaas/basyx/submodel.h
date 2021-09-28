#pragma once

#include <util/optional/optional.hpp>

#include <basyx/identifiable.h>
#include <basyx/haskind.h>
#include <basyx/hassemantics.h>
#include <basyx/submodelelement/submodelelement.h>

#include <basyx/serialization/serializable.h>

#include <basyx/base/elementcontainer.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class Submodel : 
   public Identifiable,
	public HasKind, 
	public HasSemantics,
   public ModelType<ModelTypes::Submodel>,
   private Identifiable::Copyable<Submodel>
{
private:
	ElementContainer<SubmodelElement> submodelElements;
public:
	Submodel(util::string_view idShort, util::string_view identifier) : Identifiable(idShort, Identifier(identifier)) {};
	Submodel(util::string_view idShort, Identifier identifier) : Identifiable(idShort, std::move(identifier)) {};
public:
   Submodel(const Submodel &sm) : Identifiable(sm.getIdShort(), std::move(sm.getIdentification().getId())) {
      this->submodelElements.append(sm.getSubmodelElements());
   };

   Submodel& operator=(const Submodel &sm) {
      this->setIdentification(sm.getIdentification());
      this->getIdShort() = sm.getIdShort();
      this->submodelElements.append(sm.getSubmodelElements());
      return *this;
   }

	Submodel(Submodel &&) = default;
	Submodel& operator=(Submodel &&) = default;
   Submodel& operator+=(const Submodel& sm) {
      this->getSubmodelElements().append(sm.getSubmodelElements());
      return *this;
   }
public:
	const ElementContainer<SubmodelElement> & getSubmodelElements() const { return this->submodelElements; };
	ElementContainer<SubmodelElement> & getSubmodelElements() { return this->submodelElements; };
	void setSubmodelElements(ElementContainer<SubmodelElement> elements) { this->submodelElements = std::move(elements); };
};

};
