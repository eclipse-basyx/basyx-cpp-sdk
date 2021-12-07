/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/submodelelement/BasicEvent.h>

namespace basyx {
namespace aas {
namespace map {

constexpr char BasicEvent::Path::Observed[];

BasicEvent::BasicEvent(const std::string & idShort, Reference observed, ModelingKind kind)
  : SubmodelElement{idShort, kind}
  , observed{observed}
{
  this->map.insertKey(Path::Observed, this->observed.getMap());
}

BasicEvent::BasicEvent(basyx::object obj)
  : SubmodelElement{obj}
  , observed{obj.getProperty(Path::Observed)}
{
  this->map.insertKey(Path::Observed, this->observed.getMap());
}

const api::IReference & BasicEvent::getObserved() const
{
  return this->observed;
}

}
}
}
