/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_COMMON_ELEMENTCONTAINER_H
#define BASYX_SUBMODEL_SIMPLE_COMMON_ELEMENTCONTAINER_H

#include <BaSyx/aas/api_v2/common/IElementContainer.h>

#include <algorithm>

namespace basyx {
namespace aas {
namespace simple {

template<typename IElementType>
class ElementContainer : public api::IElementContainer<IElementType>
{
public:
    using elementPtr_t = typename api::IElementContainer<IElementType>::elementPtr_t;
    using container_t = std::vector<elementPtr_t>;
private:
    container_t container;
	api::IReferable * parent;
public:
	ElementContainer(api::IReferable * parent = nullptr) : parent(parent) {};
	virtual ~ElementContainer() = default;
public:
	// Inherited via IElementContainer
	virtual std::size_t size() const override;
	virtual api::IReferable * getParent() const override;

	virtual IElementType * const getElement(const std::string & idShort) const override;
	virtual IElementType * const getElement(std::size_t n) const override;
	virtual void addElement(elementPtr_t element) override;
public:
	auto begin() -> decltype(this->container.begin())
	{
		return this->container.begin();
	}

	auto end() -> decltype(this->container.end())
	{
		return this->container.end();
	}
};

template<typename IElementType>
std::size_t ElementContainer<IElementType>::size() const
{
	return this->container.size();
};

template<typename IElementType>
api::IReferable * ElementContainer<IElementType>::getParent() const
{
	return this->parent;
};

template<typename IElementType>
IElementType * const ElementContainer<IElementType>::getElement(const std::string & idShort) const
{
	auto ret = std::find_if(container.begin(), container.end(),
		[&idShort](const elementPtr_t & element) { return element->getIdShort() == idShort; });

	if (ret != container.end())
		return ret->get();

	return nullptr;
};

template<typename IElementType>
IElementType * const ElementContainer<IElementType>::getElement(std::size_t n) const
{
	if (n > this->container.size())
		return nullptr;

	return this->container.at(n).get();
};


template<typename IElementType>
void ElementContainer<IElementType>::addElement(elementPtr_t element)
{
	this->container.emplace_back(std::move(element));
};



}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_COMMON_ELEMENTCONTAINER_H */
