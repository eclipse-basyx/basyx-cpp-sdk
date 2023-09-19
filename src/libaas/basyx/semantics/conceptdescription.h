#pragma once

#include <basyx/reference.h>

#include <basyx/util/optional/optional.hpp>
#include <basyx/util/string_view/string_view.hpp>
#include <basyx/util/container/container.hpp>

#include <basyx/identifiable.h>
#include <basyx/semantics/hasDataSpecification.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class ConceptDescription : public Identifiable, public HasDataSpecification
{
public:
	using isCaseOf_t = std::vector<Reference>;
private:
	isCaseOf_t isCaseOf;
public:
	ConceptDescription(util::string_view idShort, Identifier identification) : Identifiable(idShort, identification) {};
	
	template<typename... Refs>
	ConceptDescription(util::string_view idShort, Identifier identification, Refs&&... refs) 
		: Identifiable(idShort, identification) {
		util::vector_helper::emplace_variadic(isCaseOf, std::forward<Refs>(refs)...);
	};
public:
	ConceptDescription(const ConceptDescription &) = default;
	ConceptDescription& operator=(const ConceptDescription &) = default;

	ConceptDescription(ConceptDescription &&) noexcept = default;
	ConceptDescription& operator=(ConceptDescription &&) noexcept = default;
public:
	std::size_t size() const { return isCaseOf.size(); };
public:
	const isCaseOf_t & getIsCaseOf() const { return isCaseOf; };
	isCaseOf_t & getIsCaseOf() { return isCaseOf; };
	void setIsCaseOf(isCaseOf_t isCaseOf) { this->isCaseOf = std::move(isCaseOf); };
};

};
