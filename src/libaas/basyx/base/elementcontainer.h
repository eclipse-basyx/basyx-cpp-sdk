#pragma once

#include <basyx/referable.h>

#include <util/string_view/string_view.hpp>
#include <util/container/container.hpp>

#include <vector>

namespace basyx
{

template<typename ElementType>
class ElementContainer
{
static_assert(std::is_convertible<ElementType*, Referable*>::value, "Only Referables supported by ElementContainer!");
public:
	using element_t = ElementType;
	using elementEntry_t = std::unique_ptr<element_t>;
	using elementList_t = std::vector<elementEntry_t>;
	using elementIterator_t = typename elementList_t::iterator;
	using elementConstIterator_t = typename elementList_t::const_iterator;
private:
	elementList_t elementList;
private:
	void _insert_variadic() { };

	template<typename First, typename... Tail>
	void _insert_variadic(First && first, Tail&&... tail) {
		this->add(std::forward<First>(first));
		_insert_variadic(std::forward<Tail>(tail)...);
	};
public:
	ElementContainer() {};

	template<typename... T>
	ElementContainer(T&&... t) { _insert_variadic(std::forward<T>(t)...); };

   ElementContainer(const ElementContainer&) = delete;
   ElementContainer& operator=(const ElementContainer&) = delete;

   ElementContainer(ElementContainer&&) noexcept = default;
   ElementContainer& operator=(ElementContainer&&) noexcept = default;

	~ElementContainer() = default;
public:
	template <typename T>
	ElementContainer<ElementType>& operator+=(const ElementContainer<T>& container) {
		this->append(container);
		return *this;
	}
public:
	std::size_t size() const { return elementList.size(); };
	bool hasEntry(util::string_view idShort);
public:
	ElementType* const get(util::string_view idShort);
	ElementType* const get(std::size_t n);

	const ElementType* const get(util::string_view idShort) const;
	const ElementType* const get(std::size_t n) const;
public:
	template<typename T> T* const get(util::string_view idShort) { return dynamic_cast<T*>(get(idShort)); };
	template<typename T> T* const get(std::size_t n) { return dynamic_cast<T*>(get(n)); };

	template<typename T> const T* const get(util::string_view idShort) const { return dynamic_cast<T*>(get(idShort)); };
	template<typename T> const T* const get(std::size_t n) const { return dynamic_cast<T*>(get(n)); };
public:
   template<typename T> T* const add(T & t) { return this->add(std::make_unique<T>(std::forward<T>(t))); };
   template<typename T> T* const add(T && t) { return this->add(std::make_unique<T>(std::forward<T>(t))); };
	
   template<typename T> T* const add(std::unique_ptr<T> element) {
		if (this->hasEntry(element->getIdShort()))
			return nullptr;
		auto ptr = element.get();
		this->elementList.emplace_back(std::move(element));
		return ptr;
	};

    template<typename T>
   void append(const ElementContainer<T>& container) {
	   for (const auto & entry : container) {
		   this->add(std::move(entry->template copy<ElementType>()));
	   };
   }
public:
	elementIterator_t begin() noexcept { return this->elementList.begin(); }
	elementIterator_t end() noexcept { return this->elementList.end(); }
	elementConstIterator_t begin() const noexcept { return this->elementList.begin(); }
	elementConstIterator_t end() const noexcept { return this->elementList.end(); }
};

template<typename ElementType>
inline bool ElementContainer<ElementType>::hasEntry(util::string_view idShort) 
{
	for (const auto & entry : elementList)
		if (entry->getIdShort() == idShort)
			return true;

	return false;
};

template<typename ElementType>
inline const ElementType* const ElementContainer<ElementType>::get(util::string_view idShort) const
{
	auto ret = std::find_if(elementList.begin(), elementList.end(),
		[&idShort](const elementEntry_t & element) { return element->getIdShort() == idShort; });

	if (ret != elementList.end())
		return ret->get();

	return nullptr;
};

template<typename ElementType>
inline ElementType* const ElementContainer<ElementType>::get(util::string_view idShort)
{
	auto ret = std::find_if(elementList.begin(), elementList.end(),
		[&idShort](const elementEntry_t & element) { return element->getIdShort() == idShort; });

	if (ret != elementList.end())
		return ret->get();

	return nullptr;
};

template<typename ElementType>
inline ElementType * const ElementContainer<ElementType>::get(std::size_t n)
{
	if (n > this->elementList.size())
		return nullptr;

	return this->elementList.at(n).get();
};

template<typename ElementType>
inline const ElementType * const ElementContainer<ElementType>::get(std::size_t n) const
{
	if (n > this->elementList.size())
		return nullptr;

	return this->elementList.at(n).get();
};




};
