#pragma once

#include <basyx/submodelelement/submodelelement.h>
#include <basyx/serialization/serializable.h>

#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>
#include <util/container/container.hpp>

#include <string>

namespace basyx
{

class SubmodelElementCollection : 
	public SubmodelElement, 
	private ModelType<ModelTypes::SubmodelElementCollection>,
	private serialization::Serializable<SubmodelElementCollection>
{
public:
	using valuePtr_t = std::unique_ptr<SubmodelElement>;
	using valueList_t = std::vector<valuePtr_t>;
	using valueIterator_t = valueList_t::iterator;
	using constValueIterator_t = valueList_t::const_iterator;
	using constValuePtr_t = const std::unique_ptr<SubmodelElement>;
private:
	valueList_t valueList;
	bool ordered;
	bool allowDuplicates;
public:
	SubmodelElementCollection(util::string_view idShort) : SubmodelElement(idShort) {};
	SubmodelElementCollection(util::string_view idShort, valueList_t list) : SubmodelElement(idShort), valueList(std::move(list)) {};
	
	template<typename... Args>
	SubmodelElementCollection(util::string_view idShort, Args&&... args) 
		: SubmodelElement(idShort) 
	{
		util::vector_helper::emplace_variadic(valueList, 
			std::make_unique<Args>( std::forward<Args>(args) ) ...);
	};



	SubmodelElementCollection(const SubmodelElementCollection&) = default;
	SubmodelElementCollection& operator=(const SubmodelElementCollection&) = default;

	SubmodelElementCollection(SubmodelElementCollection&&) noexcept = default;
	SubmodelElementCollection& operator=(SubmodelElementCollection&&) noexcept = default;

	virtual ~SubmodelElementCollection() {
		int j = 2;
	};
public:
	valueIterator_t begin() noexcept { return this->valueList.begin(); };
	valueIterator_t end() noexcept { return this->valueList.end(); };

	constValueIterator_t begin() const noexcept { return this->valueList.begin(); };
	constValueIterator_t end() const noexcept { return this->valueList.end(); };
private:
	SubmodelElement * find_element_internal(util::string_view idShort) const noexcept;
public:
	template<typename Element>
	void add(Element && e)
	{
		using value_t = typename std::remove_reference<Element>::type;
		valueList.emplace_back(std::make_unique<value_t>( std::forward<Element>(e) ));
	};

	// Get SubmodelElement by idShort
	SubmodelElement * get(util::string_view idShort) noexcept {
		return find_element_internal(idShort);
	};

	const SubmodelElement * get(util::string_view idShort) const noexcept {
		return find_element_internal(idShort);
	};

	// Get typed element by idShort
	template<typename Element>
	Element * get(util::string_view idShort) noexcept {
		auto element = get(idShort);

		if (element != nullptr)
			return dynamic_cast<Element *>(element);
		return nullptr;
	};

	// Get typed const element by idShort
	template<typename Element>
	const Element * get(util::string_view idShort) const noexcept {
		auto element = get(idShort);

		if (element != nullptr)
			return dynamic_cast<const Element *>(element);
		return nullptr;
	};

	std::size_t size() const noexcept { return this->valueList.size(); }
};

}
