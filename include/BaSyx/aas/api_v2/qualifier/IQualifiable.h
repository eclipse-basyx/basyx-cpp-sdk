/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_QUALIFIER_IQUALIFIABLE_H
#define BASYX_SUBMODEL_API_V2_QUALIFIER_IQUALIFIABLE_H

#include <BaSyx/aas/api_v2/constraint/IFormula.h>

#include <BaSyx/aas/simple/constraint/Formula.h>

#include <vector>

namespace basyx {
namespace aas {

namespace simple { class Qualifier; }

namespace api {

class IQualifier;

class IQualifiable
{
public:
	virtual ~IQualifiable() = 0;

	virtual void addFormula(const IFormula & formula) = 0;
	virtual void addQualifier(const IQualifier & qualifier) = 0;

	virtual std::vector<simple::Formula> getFormulas() const = 0;
	virtual std::vector<simple::Qualifier> getQualifiers() const = 0;
};

inline IQualifiable::~IQualifiable() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IQUALIFIABLE_H */
