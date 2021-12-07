/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_QUALIFIER_FORMULA_H
#define BASYX_SUBMODEL_SIMPLE_QUALIFIER_FORMULA_H

#include <BaSyx/aas/api_v2/constraint/IFormula.h>

namespace basyx {
namespace aas {
namespace simple {


class Formula : public api::IFormula
{
private:
	std::vector<Reference> dependencies;
public:
	Formula() = default;
	Formula(const api::IFormula & other);
	Formula(const Formula & other) = default;
	Formula(Formula && other) noexcept = default;

	Formula & operator=(const Formula & other) = default;
	Formula & operator=(Formula && other) noexcept = default;

	Formula(const std::vector<Reference> & dependencies);
	Formula(std::vector<Reference> && dependencies);

	~Formula() = default;
public:
	virtual std::vector<simple::Reference> getDependencies() const;
	virtual void addDependency(const api::IReference & reference);

	virtual ModelTypes GetModelType() const;
};

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IFORMULA_H */