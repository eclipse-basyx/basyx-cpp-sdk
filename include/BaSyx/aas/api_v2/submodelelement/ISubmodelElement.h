/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ISUBMODELELEMENT_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ISUBMODELELEMENT_H

#include <BaSyx/aas/api_v2/qualifier/IQualifiable.h>
#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/api_v2/qualifier/IHasSemantics.h>
#include <BaSyx/aas/api_v2/qualifier/IReferable.h>
#include <BaSyx/aas/api_v2/qualifier/IHasKind.h>
#include <BaSyx/aas/api_v2/common/IModelType.h>



namespace basyx {
namespace aas {
namespace api {

class ISubmodelElement
  : public virtual IHasDataSpecification
  , public virtual IReferable
  , public virtual IHasSemantics
  , public virtual IQualifiable
  , public virtual IHasKind
  ,	public virtual IModelType
{
public:
  virtual ~ISubmodelElement() = 0;

  virtual KeyElements getKeyElementType() const override;
};

inline KeyElements ISubmodelElement::getKeyElementType() const { return KeyElements::SubmodelElement; };

inline ISubmodelElement::~ISubmodelElement() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ISUBMODELELEMENT_H */
