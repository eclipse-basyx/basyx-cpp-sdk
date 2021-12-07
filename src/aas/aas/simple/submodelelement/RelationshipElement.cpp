/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/RelationshipElement.h>
#include <BaSyx/aas/api_v2/qualifier/IReferable.h>


namespace basyx {
namespace aas {
namespace simple {

RelationshipElement::RelationshipElement(const Reference & first, const Reference & second, const std::string & idShort, ModelingKind kind)
  : SubmodelElement(idShort, kind)
  , first(first)
  , second(second)
{}

const Reference & RelationshipElement::getFirst() const
{
  return first;
}

const Reference & RelationshipElement::getSecond() const
{
  return second;
}

}
}
}
