/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_QUALIFIER_QUALIFIABLE_H
#define BASYX_SUBMODEL_MAP_V2_QUALIFIER_QUALIFIABLE_H

#include <BaSyx/aas/api_v2/qualifier/IQualifiable.h>
#include <BaSyx/aas/simple/constraint/Qualifier.h>
#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

	
class Qualifiable : 
	public virtual api::IQualifiable,
	public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char Qualifier[] = "qualifier";
  };
public:
	Qualifiable();
	Qualifiable(const std::vector<simple::Formula> & formulas, const std::vector<simple::Qualifier> & qualifiers);
	Qualifiable(basyx::object);

	Qualifiable(const Qualifiable & other) = default;
	Qualifiable(Qualifiable && other) noexcept = default;

	Qualifiable & operator=(const Qualifiable & other) = default;
	Qualifiable & operator=(Qualifiable && other) noexcept = default;

	~Qualifiable() = default;
public:
	virtual void addFormula(const api::IFormula & formula) override;
	virtual void addQualifier(const api::IQualifier & qualifier) override;

	virtual std::vector<simple::Formula> getFormulas() const override;
	virtual std::vector<simple::Qualifier> getQualifiers() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_QUALIFIER_QUALIFIABLE_H */
