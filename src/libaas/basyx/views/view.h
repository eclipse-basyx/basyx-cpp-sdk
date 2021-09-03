#pragma once

#include <basyx/reference.h>

#include <util/optional/optional.hpp>
#include <util/string_view/string_view.hpp>
#include <util/container/container.hpp>

#include <basyx/referable.h>
#include <basyx/hassemantics.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class View : public Referable, public HasSemantics, public ModelType<ModelTypes::View>
{
public:
	using elementsContainer_t = std::vector<Reference>;
private:
	std::vector<Reference> containedElements;
public:
	View(util::string_view idShort) : Referable( idShort ) {};

	template<typename... Refs>
	View(util::string_view idShort, Refs&&... refs) : Referable( idShort ) {
		util::vector_helper::emplace_variadic(containedElements, std::forward<Refs>(refs)...);
	};
public:
	View(const View &) = default;
	View& operator=(const View &) = default;

	View(View &&) noexcept = default;
	View& operator=(View &&) noexcept = default;
public:
	std::size_t size() const { return containedElements.size(); };
public:
	const elementsContainer_t & getContainedElements() const { return containedElements; };
	elementsContainer_t & getContainedElements() { return containedElements; };
	void setContainedElements(elementsContainer_t containedElements) { this->containedElements = std::move(containedElements); };
};

};
