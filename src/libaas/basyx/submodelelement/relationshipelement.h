#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>

#include <basyx/modeltype.h>

#include <basyx/submodelelement/property.h>

#include <basyx/util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class RelationshipElement : public SubmodelElement, 
	private ModelType<ModelTypes::RelationshipElement>,
	private serialization::Serializable<RelationshipElement>
{
private:
	Reference first;
	Reference second;
public:
	RelationshipElement(util::string_view idShort, Reference first, Reference second);

	RelationshipElement(const RelationshipElement&) = default;
	RelationshipElement& operator=(const RelationshipElement&) = default;

	RelationshipElement(RelationshipElement&&) = default;
	RelationshipElement& operator=(RelationshipElement&&) = default;

	~RelationshipElement() = default;
public:
	const Reference & getFirst() const { return this->first; };
	const Reference & getSecond() const { return this->second; };

	template<typename T>
	void setFirst(T && t) { this->first = std::forward<T>(t); };

	template<typename T>
	void setSecond(T && t) { this->second = std::forward<T>(t); };
};

}