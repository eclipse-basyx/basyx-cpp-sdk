/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_BASICEVENT_H
#define BASYX_SUBMODEL_MAP_BASICEVENT_H

#include <BaSyx/aas/api_v2/submodelelement/IBasicEvent.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>

namespace basyx {
namespace aas {
namespace map {

class BasicEvent
  : public virtual api::IBasicEvent
  , public SubmodelElement
  , ModelType<ModelTypes::BasicEvent>
{
public:
  struct Path {
    static constexpr char Observed[] = "observed";
  };

private:
  Reference observed;

public:
  BasicEvent(const std::string& idShort, Reference observed, ModelingKind kind = ModelingKind::Instance);
  BasicEvent(basyx::object);

  BasicEvent() = delete;

  const api::IReference & getObserved() const override;

  virtual KeyElements getKeyElementType() const override { return KeyElements::BasicEvent; };
};

}
}
}
#endif //BASYX_SUBMODEL_MAP_BASICEVENT_H
