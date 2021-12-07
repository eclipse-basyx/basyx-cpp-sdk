/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_AAS_IASSETADMINISTRATIONSHELL_H
#define BASYX_SUBMODEL_API_V2_AAS_IASSETADMINISTRATIONSHELL_H

#include <BaSyx/aas/simple/qualifier/Identifiable.h>
#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/api_v2/common/IModelType.h>
#include <BaSyx/aas/api_v2/aas/IAsset.h>
#include <BaSyx/aas/api_v2/ISubmodel.h>

#include <memory>

namespace basyx {
namespace aas {
namespace api {

class IAssetAdministrationShell : 
	public virtual IHasDataSpecification, 
	public virtual IIdentifiable,
	public virtual IModelType
{
public:
	using SubmodelContainer_t = IElementContainer<ISubmodel>;
public:
	virtual ~IAssetAdministrationShell() = 0;
	
	virtual IAsset & getAsset() = 0;

	virtual IReference * getDerivedFrom() = 0;
	virtual void setDerivedFrom(const IReference & derivedFrom) = 0;

	virtual SubmodelContainer_t & getSubmodels() = 0;
};

inline IAssetAdministrationShell::~IAssetAdministrationShell() = default;


}
}
}

#endif /* BASYX_SUBMODEL_API_V2_AAS_IASSETADMINISTRATIONSHELL_H */
