/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/qualifier/Qualifiable.h>

using namespace basyx::aas::api;
using namespace basyx::aas::simple;

Qualifiable::Qualifiable(const std::vector<Formula> & formulas, const std::vector<Qualifier> & qualifiers)
	: formulas(formulas), qualifiers(qualifiers)
{
};

Qualifiable::Qualifiable(std::vector<Formula> && formulas, std::vector<Qualifier> && qualifiers)
	: formulas(formulas), qualifiers(qualifiers)
{
};

void basyx::aas::simple::Qualifiable::addFormula(const api::IFormula & formula)
{
	this->formulas.emplace_back(std::move(formula.getDependencies()));
}

void basyx::aas::simple::Qualifiable::addQualifier(const api::IQualifier & qualifier)
{
	this->qualifiers.emplace_back(qualifier);
}

std::vector<Formula> basyx::aas::simple::Qualifiable::getFormulas() const
{
	return this->formulas;
}

std::vector<Qualifier> basyx::aas::simple::Qualifiable::getQualifiers() const
{
	return this->qualifiers;
}
