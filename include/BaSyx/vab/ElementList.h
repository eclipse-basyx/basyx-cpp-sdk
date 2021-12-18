/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_AAS_METAMODEL_ELEMENT_LIST_H_
#define BASYX_AAS_METAMODEL_ELEMENT_LIST_H_

#include <BaSyx/shared/object.h>

namespace basyx {
namespace vab {

class ElementList 
{
protected:
  mutable basyx::object collection;
public:
  ElementList();
    
  ElementList(basyx::object object);
  
  ElementList(const ElementList & other);

  void insertElement(const ElementList& collection);

  basyx::object getList() const;
};

}
}

#endif
