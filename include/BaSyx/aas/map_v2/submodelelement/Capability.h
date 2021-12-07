/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_CAPABILITY_H
#define BASYX_SUBMODEL_MAP_CAPABILITY_H

#include <BaSyx/aas/api_v2/submodelelement/ICapability.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>

namespace basyx {
namespace aas {
namespace map {

class Capability 
  : public virtual api::ICapability
  , public SubmodelElement
  , public ModelType<ModelTypes::Capability>
{
public:
  Capability(const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
  Capability(basyx::object);

  virtual KeyElements getKeyElementType() const override { return KeyElements::Capability; };
};

}
}
}
#endif //BASYX_SUBMODEL_MAP_CAPABILITY_H
