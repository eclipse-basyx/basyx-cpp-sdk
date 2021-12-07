/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IVALUELIST_H
#define BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IVALUELIST_H

#include <BaSyx/aas/simple/dataspecification/ValueReferencePair.h>

namespace basyx {
namespace aas {
namespace api {

class IValueList
{
public:
	virtual ~IValueList() = 0;

	virtual void addValueReferencePair(const simple::ValueReferencePair & valueRefPair) = 0;
	virtual std::vector<simple::ValueReferencePair> getValueReferencePairs() = 0;
};

inline IValueList::~IValueList() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IVALUELIST_H */
