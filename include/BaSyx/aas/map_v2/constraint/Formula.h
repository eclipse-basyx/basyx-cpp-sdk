/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_CONSTRAINT_FORMULA_H
#define BASYX_SUBMODEL_MAP_V2_CONSTRAINT_FORMULA_H

#include <BaSyx/aas/api_v2/constraint/IFormula.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {


class Formula : 
	public api::IFormula,
	public ModelType<ModelTypes::Formula>,
	public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char Dependencies[] = "dependencies";
  };

public:
	using vab::ElementMap::ElementMap;

	Formula();
	Formula(basyx::object);

	Formula(const api::IFormula & other);
	Formula(const Formula & other) = default;
	Formula(Formula && other) noexcept = default;

	Formula & operator=(const Formula & other) = default;
	Formula & operator=(Formula && other) noexcept = default;

	Formula(const std::vector<simple::Reference> & dependencies);

	~Formula() = default;

public:
	virtual std::vector<simple::Reference> getDependencies() const;
	virtual void addDependency(const api::IReference & reference);
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_CONSTRAINT_FORMULA_H */
