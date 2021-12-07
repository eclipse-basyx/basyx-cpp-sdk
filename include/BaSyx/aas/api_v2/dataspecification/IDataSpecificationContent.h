/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONCONTENT_H
#define BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONCONTENT_H

namespace basyx {
namespace aas {
namespace api {

class IDataSpecificationContent
{
public:
	virtual ~IDataSpecificationContent() = 0;
};

inline IDataSpecificationContent::~IDataSpecificationContent() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IDATASPECIFICATIONCONTENT_H */

