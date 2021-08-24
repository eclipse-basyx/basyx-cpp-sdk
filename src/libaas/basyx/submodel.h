#pragma once

#include <util/optional/optional.hpp>

#include <basyx/identifiable.h>
#include <basyx/haskind.h>
#include <basyx/hassemantics.h>

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
	public ModelType<ModelTypes::Submodel>
{
private:
	ElementContainer<SubmodelElement> submodelElements;
public:
	Submodel(util::string_view idShort, Identifier identifier) : Identifiable(idShort, std::move(identifier)) {};
public:
	Submodel(const Submodel &) = default;
	Submodel& operator=(const Submodel &) = default;

	Submodel(Submodel &&) = default;
	Submodel& operator=(Submodel &&) = default;
public:
	const ElementContainer<SubmodelElement> & get_submodel_elements() const { return this->submodelElements; };
	ElementContainer<SubmodelElement> & get_submodel_elements() { return this->submodelElements; };
	void set_submodel_elements(ElementContainer<SubmodelElement> elements) { this->submodelElements = std::move(elements); };
};

};
