/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IENTITY_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IENTITY_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>

#include <BaSyx/aas/enumerations/EntityType.h>

namespace basyx {
namespace aas {
namespace api {


class IEntity
  : public virtual ISubmodelElement
{
public:
	virtual ~IEntity() = 0;

	virtual IElementContainer<ISubmodelElement> & getStatement() = 0;

	virtual EntityType getEntityType() const = 0;

	virtual const IReference * const getAssetRef() const = 0;

	virtual KeyElements getKeyElementType() const override { return KeyElements::Entity; };
};

inline IEntity::~IEntity() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_IENTITY_H */
