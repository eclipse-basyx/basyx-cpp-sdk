/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_ISUBMODEL_H
#define BASYX_SUBMODEL_API_V2_ISUBMODEL_H

#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/api_v2/qualifier/IHasKind.h>
#include <BaSyx/aas/api_v2/qualifier/IHasSemantics.h>
#include <BaSyx/aas/api_v2/qualifier/IQualifiable.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>


namespace basyx {
namespace aas {
namespace api {

class ISubmodel : 
	public virtual IIdentifiable,
	public virtual IHasSemantics, 
  public virtual IQualifiable,
	public virtual IHasDataSpecification,
	public virtual IHasKind
{
public:
	virtual ~ISubmodel() = 0;

	virtual IElementContainer<ISubmodelElement> & submodelElements() = 0;
	virtual const IElementContainer<ISubmodelElement> & submodelElements() const = 0;
};

inline ISubmodel::~ISubmodel() = default;


}
}
}


#endif /* BASYX_SUBMODEL_API_V2_ISUBMODEL_H */
