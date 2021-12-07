/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/dataspecification/ValueList.h>


namespace basyx {
namespace aas {
namespace map {

constexpr char ValueList::Path::Value[];
constexpr char ValueList::Path::ValueId[];

ValueList::ValueList()
  : vab::ElementMap(basyx::object::make_object_list())
{}

ValueList::ValueList(const std::vector<simple::ValueReferencePair> &list)
    : vab::ElementMap()
{}

void ValueList::addValueReferencePair(const simple::ValueReferencePair & valueRefPair)
{
  object obj = object::make_map();
  obj.insertKey(Path::Value, valueRefPair.getValue());
  obj.insertKey(Path::ValueId, map::Reference(valueRefPair.getValueId()).getMap());
  this->map.insert(obj);
}

std::vector<simple::ValueReferencePair> ValueList::getValueReferencePairs()
{
  std::vector<simple::ValueReferencePair> list;
  for (auto & pair_obj : this->map.Get<object::object_list_t&>())
  {
    std::string value = pair_obj.getProperty(Path::Value).GetStringContent();
    auto reference = simple::Reference(map::Reference(pair_obj.getProperty(Path::ValueId)));
    simple::ValueReferencePair pair(value, reference);
    list.push_back(pair);
  }
  return list;
}

}
}
}
