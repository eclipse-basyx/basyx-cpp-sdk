/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTCONTAINER_H
#define BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTCONTAINER_H

#include <BaSyx/aas/api_v2/common/IElementContainer.h>
#include <BaSyx/aas/map_v2/common/ElementFactory.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/qualifier/Identifiable.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>
#include <BaSyx/vab/ElementMap.h>

#include <unordered_map>
#include <algorithm>

namespace basyx {
namespace aas {
namespace map {

struct ElementContainerPath {
	static constexpr char IdShort[] = "idShort";
};

template<typename IElementType>
class ElementContainer : public api::IElementContainer<IElementType>, public virtual vab::ElementMap
{
public:
    using elementPtr_t = typename api::IElementContainer<IElementType>::elementPtr_t;
    using cache_t = std::unordered_map<std::string, elementPtr_t>;
private:
	api::IReferable * parent;
	mutable cache_t cache;
	basyx::object keyList;
public:
	using vab::ElementMap::ElementMap;
	ElementContainer(api::IReferable * parent = nullptr)
		: vab::ElementMap(basyx::object::make_map())
		, keyList(basyx::object::make_object_list())
		, parent(parent)
	{
	};

	virtual ~ElementContainer() = default;
public:
	basyx::object getKeyMap() { return this->keyList; };
public:
	virtual std::size_t size() const override;
	virtual api::IReferable * getParent() const override;

	virtual IElementType * const getElement(const std::string & idShort) const override;
	virtual IElementType * const getElement(std::size_t n) const override;
	virtual void addElement(elementPtr_t element) override;
//	virtual std::vector<simple::Identifier> getIdentifierList();
};

template<typename IElementType>
std::size_t ElementContainer<IElementType>::size() const
{
	return this->map.size();
};

template<typename IElementType>
api::IReferable * ElementContainer<IElementType>::getParent() const
{
	return this->parent;
};

template<typename IElementType>
IElementType * const ElementContainer<IElementType>::getElement(const std::string & idShort) const
{
	// Find element in object tree
	auto && object = this->map.getProperty(idShort);

	// element doesn't exist, remove from cache and return nullptr
	if (object.IsNull() || object.IsError()) {
		this->cache.erase(idShort);
		return nullptr;
	}
	else { // element found
		// check if already in cache
		auto element = cache.find(idShort);
		if (element == cache.end()) {
			// not in cache, re-create elementPtr and return
			elementPtr_t elementPtr = ElementFactory<IElementType>::Create(vab::ElementMap(object));
			auto ptr = this->cache.emplace(idShort, std::move(elementPtr));
			ptr.first->second.get();
		}
		else { // found inside cache, return pointer
			return element->second.get();
		}
	}

	return nullptr;
};

template<typename IElementType>
IElementType * const ElementContainer<IElementType>::getElement(std::size_t n) const
{
	if (n > this->size())
		return nullptr;

	// Iterate through object map
	int i = 0;
	
	for(const auto & entry : map.Get<basyx::object::object_map_t&>())
	{
		if (i++ == n)
		{
			// Get id of object and create temporary
			const auto & id = entry.first;
			return this->getElement(id);
		};
	};

	return nullptr;
};


template<typename IElementType>
void ElementContainer<IElementType>::addElement(elementPtr_t element)
{
	auto shortId = element->getIdShort();

	auto elementMap = dynamic_cast<vab::ElementMap*>(element.get());
	if (elementMap != nullptr)
	{
		// Get reference from element
		map::Reference reference(element->getReference());

		this->keyList.insert(reference.getMap());
		this->map.insertKey(shortId, elementMap->getMap());
		this->cache.emplace(shortId, std::move(element));
	};
};



}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTCONTAINER_H */
