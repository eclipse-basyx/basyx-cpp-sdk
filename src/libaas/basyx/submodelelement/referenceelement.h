#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>

#include <basyx/modeltype.h>

#include <basyx/submodelelement/property.h>

#include <basyx/util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class ReferenceElement : 
	public DataElement, 
	private ModelType<ModelTypes::ReferenceElement>,
	private serialization::Serializable<ReferenceElement>
{
private:
	util::optional<Reference> value;
public:
	ReferenceElement(util::string_view idShort) : DataElement(idShort) {};

	ReferenceElement(const ReferenceElement&) = default;
	ReferenceElement& operator=(const ReferenceElement&) = default;

	ReferenceElement(ReferenceElement&&) = default;
	ReferenceElement& operator=(ReferenceElement&&) = default;

	~ReferenceElement() = default;
public:
	const util::optional<Reference> & getValue() const { return this->value; };
	util::optional<Reference> & getValue() { return this->value; };

	template<typename T>
	void setValue(T && t) { this->value.emplace(std::forward<T>(t)); };
};

}