/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ICAPABILITY_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ICAPABILITY_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>

namespace basyx {
namespace aas {
namespace api {

class ICapability
  : ISubmodelElement
{
public:
  ~ICapability() = 0;

  virtual KeyElements getKeyElementType() const override { return KeyElements::Capability; };
};

inline ICapability::~ICapability() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ICAPABILITY_H */
