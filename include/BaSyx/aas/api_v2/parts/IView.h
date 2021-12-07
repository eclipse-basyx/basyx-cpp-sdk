/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_PARTS_IVIEW_H
#define BASYX_SUBMODEL_API_V2_PARTS_IVIEW_H

#include <BaSyx/aas/api_v2/qualifier/IReferable.h>
#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/api_v2/qualifier/IHasSemantics.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>

namespace basyx {
namespace aas {
namespace api {

class IView
  : public virtual IHasDataSpecification
  , public virtual IReferable
  , public virtual IHasSemantics
{
public:
  virtual ~IView() = 0;

  virtual const IElementContainer<IReferable> & getContainedElements() const = 0;
};

inline IView::~IView() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_PARTS_IVIEW_H */
