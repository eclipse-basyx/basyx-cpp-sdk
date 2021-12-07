/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_PARTS_ICONCEPTDESCRIPTION_H
#define BASYX_SUBMODEL_API_V2_PARTS_ICONCEPTDESCRIPTION_H

#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>
#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>
#include <BaSyx/aas/api_v2/dataspecification/IDataSpecification.h>

#include <string>
#include <vector>

namespace basyx {
namespace aas {
namespace api {

class IConceptDescription : 
	public virtual IHasDataSpecification, 
	public virtual IIdentifiable
{
public:
	virtual ~IConceptDescription() = 0;

	virtual const std::vector<std::unique_ptr<IReference>> & getIsCaseOf() const = 0;
	virtual const IElementContainer<IDataSpecification> & getEmbeddedDataSpecification() const = 0;
};

inline IConceptDescription::~IConceptDescription() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_PARTS_ICONCEPTDESCRIPTION_H */
