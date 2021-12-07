/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace vab {

ElementMap::ElementMap()
  : map(basyx::object::make_map())
{}

ElementMap::ElementMap(basyx::object object)
  : map(object)
{
}

ElementMap::ElementMap(const ElementMap & other) :
  map{other.getMap()}
{}

basyx::object ElementMap::getMap() const
{
  return map;
};

void ElementMap::insertMapElement(const std::string & key, const ElementMap & element)
{
  this->map.insertKey(key, element.getMap(), true);
}

}
}
