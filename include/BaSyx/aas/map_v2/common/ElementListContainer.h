/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTLISTCONTAINER_H
#define BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTLISTCONTAINER_H

#include <BaSyx/vab/ElementList.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>
#include <BaSyx/aas/map_v2/common/ElementFactory.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElementFactory.h>

#include <vector>

namespace basyx {
namespace aas {
namespace map {

struct ElementListContainerPath {
	static constexpr const char* IdShort = "idShort";
};

template<typename IElementType>
class ElementListContainer final : public api::IElementContainer<IElementType>, public virtual vab::ElementList
{
  
public:
  using elementPtr_t = typename api::IElementContainer<IElementType>::elementPtr_t;
  using cache_t = std::vector<elementPtr_t>;
private:
  api::IReferable * parent = nullptr;
  mutable cache_t cache;
public:
  using vab::ElementList::ElementList;
  ElementListContainer() : vab::ElementList(basyx::object::make_object_list()) { }

public:

  virtual std::size_t size() const override;

  virtual api::IReferable * getParent() const override;

  virtual IElementType * const getElement(const std::string & idShort) const override;

  virtual IElementType * const getElement(std::size_t n) const override;

  virtual void addElement(elementPtr_t element) override;

  void removeElement(std::size_t index) const;
};

template<typename IElementType>
inline IElementType * const ElementListContainer<IElementType>::getElement(const std::string & idShort) const
{
  size_t i(0);
  for (auto& ele : this->collection.Get<basyx::object::object_list_t&>())
  {
    std::string& idShort_{ele.getProperty(ElementListContainerPath::IdShort).Get<std::string&>()};

    if (idShort_ == idShort)
    {
      elementPtr_t elementPtr = ElementFactory<IElementType>::Create(vab::ElementMap(ele));
      cache.emplace_back(std::move(elementPtr));
      return cache.at(i).get();
    }
    i++;
  }
  return nullptr;
}

template<typename IElementType>
inline IElementType * const ElementListContainer<IElementType>::getElement(std::size_t n) const
{
  if (n > this->size())
    return nullptr;

  size_t i(0);
  for (const auto& ele : this->collection.Get<basyx::object::object_list_t&>()) 
  {
    if (i++ == n) 
    {
      elementPtr_t elementPtr = ElementFactory<IElementType>::Create(vab::ElementMap(ele));
      cache.emplace_back(std::move(elementPtr));
      return cache.at(n).get();
    }
  }
  return nullptr;
}

template<typename IElementType>
inline void ElementListContainer<IElementType>::addElement(elementPtr_t element)
{
  if(auto elementMap = dynamic_cast<vab::ElementMap*>(element.get()))
  {
      this->collection.insert(elementMap->getMap());
      cache.emplace_back(std::move(element));
  }
}

template<typename IElementType>
inline void ElementListContainer<IElementType>::removeElement(std::size_t n) const
{
  if (n < size())
  {
    auto& ele_list{this->collection.Get<basyx::object::object_list_t&>()};
    ele_list.erase(ele_list.begin() + n);
    cache.erase(cache.begin() + n);
  }
}

template<typename IElementType>
inline std::size_t ElementListContainer<IElementType>::size() const
{
  return this->collection.size();
}

template<typename IElementType>
inline api::IReferable * ElementListContainer<IElementType>::getParent() const
{
  return this->parent;
}

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_COMMON_ELEMENTLISTCONTAINER_H */