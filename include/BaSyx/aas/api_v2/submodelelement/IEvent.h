/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IEVENT_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IEVENT_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>

namespace basyx {
namespace aas {
namespace api {

class IEvent
    : public virtual ISubmodelElement
{
public:
  ~IEvent() = 0;

  virtual KeyElements getKeyElementType() const override { return KeyElements::Event; };
};

inline IEvent::~IEvent() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IEVENT_H */
