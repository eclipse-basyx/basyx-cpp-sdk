#pragma once

#include <basyx/reference.h>
#include <basyx/referable.h>
#include <basyx/haskind.h>
#include <basyx/hassemantics.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>
#include <basyx/serialization/serializable_base.h>

#include <basyx/util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class SubmodelElement : 
	public Referable, 
	public HasKind,
	public HasSemantics, 
	public virtual serialization::serializable_base
{
protected:
	SubmodelElement(util::string_view idShort) : Referable(idShort) {};
public:
	SubmodelElement(const SubmodelElement&) = default;
	SubmodelElement& operator=(const SubmodelElement&) = default;

	SubmodelElement(SubmodelElement&&) noexcept = default;
	SubmodelElement& operator=(SubmodelElement&&) noexcept = default;

	virtual ~SubmodelElement() = default;
public:
	template<typename submodel_element_t>
	static bool is_element_type(SubmodelElement* sel) { return dynamic_cast<submodel_element_t*>(sel) != nullptr; }

	template<typename submodel_element_t>
	static submodel_element_t* element_cast(SubmodelElement* sel) { return dynamic_cast<submodel_element_t*>(sel); }
};

}