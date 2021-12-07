/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/dataspecification/ValueList.h>

namespace basyx {
namespace aas {
namespace simple {

ValueList::ValueList(const std::vector<simple::ValueReferencePair> &list)
  : list(list)
{}

void ValueList::addValueReferencePair(const simple::ValueReferencePair &valueRefPair)
{
  this->list.push_back(valueRefPair);
}

std::vector<simple::ValueReferencePair> ValueList::getValueReferencePairs()
{
  return this->list;
}

}
}
}
