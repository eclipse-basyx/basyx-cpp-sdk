/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/ElementList.h>

basyx::vab::ElementList::ElementList() : 
  collection(basyx::object::make_object_list()){}

basyx::vab::ElementList::ElementList(basyx::object object):
  collection(object){}

basyx::vab::ElementList::ElementList(const ElementList & other) : collection{ other.getList() }
{}

void basyx::vab::ElementList::insertElement(const ElementList & collection)
{
  this->collection.insert(collection.getList());
}

basyx::object basyx::vab::ElementList::getList() const
{
  return this->collection;
}
