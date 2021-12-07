/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_QUALIFIER_IHASDATASPECIFICATION_H
#define BASYX_SUBMODEL_API_V2_QUALIFIER_IHASDATASPECIFICATION_H

#include <vector>
#include <BaSyx/aas/simple/reference/Reference.h>

namespace basyx {
namespace aas {
namespace api {

class IHasDataSpecification
{
public:
	virtual ~IHasDataSpecification() = default;

	virtual void addDataSpecification(const simple::Reference & reference) = 0;
	virtual const std::vector<simple::Reference> getDataSpecificationReference() const = 0;
};

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IHASDATASPECIFICATION_H */
