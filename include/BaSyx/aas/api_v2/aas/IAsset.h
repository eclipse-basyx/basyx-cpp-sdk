/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_AAS_IASSET_H
#define BASYX_SUBMODEL_API_V2_AAS_IASSET_H

#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/api_v2/common/IModelType.h>

#include <BaSyx/aas/api_v2/ISubmodel.h>
#include <BaSyx/aas/enumerations/AssetKind.h>
#include <BaSyx/aas/simple/qualifier/Identifiable.h>


namespace basyx {
namespace aas {

namespace api {

class IAsset : 
	public virtual IHasDataSpecification, 
	public virtual IIdentifiable,
	public virtual IModelType
{
public:
	virtual ~IAsset() = 0;

	virtual AssetKind getKind() = 0;
	virtual IReference * const getAssetIdentificationModel() = 0;
	virtual void setAssetIdentificationModel(const IReference & assetIdentificationModel) = 0;

	virtual IReference * const getBillOfMaterial() = 0;
	virtual void setBillOfMaterial(const IReference & billOfMaterial) = 0;
};

inline IAsset::~IAsset() = default;

}
}
}


#endif /* BASYX_SUBMODEL_API_V2_AAS_IASSET_H */
