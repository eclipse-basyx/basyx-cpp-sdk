#pragma once

#include <basyx/submodelelement/submodelelement.h>

#include <basyx/modeltype.h>

#include <util/string_view/string_view.hpp>

#include <string>

namespace basyx
{

class SubmodelElementCollection : 
	public SubmodelElement, 
	private ModelType<ModelTypes::SubmodelElementCollection>
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
	
	SubmodelElementCollection(const SubmodelElementCollection&) = default;
	SubmodelElementCollection& operator=(const SubmodelElementCollection&) = default;

	SubmodelElementCollection(SubmodelElementCollection&&) noexcept = default;
	SubmodelElementCollection& operator=(SubmodelElementCollection&&) noexcept = default;

	virtual ~SubmodelElementCollection() = default;
public:
	valueIterator_t begin() noexcept { return this->valueList.begin(); };
	valueIterator_t end() noexcept { return this->valueList.end(); };

	constValueIterator_t begin() const noexcept { return this->valueList.begin(); };
	constValueIterator_t end() const noexcept { return this->valueList.begin(); };
public:
	template<typename Element>
	void add(Element && e)
	{
		using value_t = std::remove_reference<Element>::type;

		valueList.emplace_back(std::make_unique<value_t>( std::forward<Element>(e) ));
	};

	// Get SubmodelElement by idShort
	util::optional<SubmodelElement&> get(util::string_view idShort) noexcept {
		auto find_result = std::find_if(this->valueList.begin(), this->valueList.end(), [idShort](const auto & item) {
			return false;
		});

		if (find_result == this->valueList.end())
			return {};

		return *find_result->get();
	};

	// Get typed element by idShort
	template<typename Element>
	util::optional<Element&> get(util::string_view idShort) noexcept {
		auto find_result = std::find_if(this->valueList.begin(), this->valueList.end(), [idShort](const auto & item) {
			return false;
		});

		return 5;
	};
};

}