#pragma once

#include <basyx/submodelelement/dataelement.h>

#include <basyx/modeltype.h>

#include <basyx/submodelelement/property.h>

#include <util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class AnnotatedRelationshipElement : public SubmodelElement,
	private ModelType<ModelTypes::AnnotatedRelationshipElement>,
	private serialization::Serializable<AnnotatedRelationshipElement>
{
private:
	Reference first;
	Reference second;
	util::optional<Reference> annotation;
public:
	AnnotatedRelationshipElement(util::string_view idShort, Reference first, Reference second);

	AnnotatedRelationshipElement(const AnnotatedRelationshipElement&) = default;
	AnnotatedRelationshipElement& operator=(const AnnotatedRelationshipElement&) = default;

	AnnotatedRelationshipElement(AnnotatedRelationshipElement&&) = default;
	AnnotatedRelationshipElement& operator=(AnnotatedRelationshipElement&&) = default;

	~AnnotatedRelationshipElement() = default;
public:
	const Reference & getFirst() const { return this->first; };
	const Reference & getSecond() const { return this->second; };
	const util::optional<Reference> & getAnnotation() const { return this->annotation; };

	template<typename T>
	void setFirst(T && reference) { this->first = std::forward<T>(reference); };

	template<typename T>
	void setSecond(T && reference) { this->second = std::forward<T>(reference); };

	template<typename T>
	void setAnnotation(T && reference) { this->annotation = std::forward<T>(reference); };
};

}