/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_CONSTRAINT_IFORMULA_H
#define BASYX_SUBMODEL_API_V2_CONSTRAINT_IFORMULA_H

#include <BaSyx/aas/api_v2/constraint/IConstraint.h>
#include <BaSyx/aas/simple/reference/Reference.h>

#include <vector>

namespace basyx {
namespace aas {
namespace api {


class IFormula : public IConstraint
{
public:
	virtual ~IFormula() = 0;

	virtual std::vector<simple::Reference> getDependencies() const = 0;
	virtual void addDependency(const IReference & reference) = 0;
};

inline IFormula::~IFormula() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_CONSTRAINT_IFORMULA_H */
