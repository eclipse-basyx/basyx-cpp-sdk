/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATION_H
#define BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATION_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationContent.h>

#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/api_v2/qualifier/IReferable.h>

namespace basyx {
namespace aas {	
namespace api {


/**
 * Mandatory members:
 *    DataSpecificationContent
 */
class IDataSpecification : public virtual IIdentifiable
{
public:
	virtual ~IDataSpecification() = 0;

	virtual IDataSpecificationContent & getContent() = 0;

	virtual KeyElements getKeyElementType() const override;
};

inline KeyElements IDataSpecification::getKeyElementType() const { return KeyElements::DataElement; };

inline IDataSpecification::~IDataSpecification() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATION_H */
