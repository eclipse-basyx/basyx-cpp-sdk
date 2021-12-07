/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/constraint/Formula.h>


using namespace basyx::aas;
using namespace basyx::aas::simple;

Formula::Formula(const std::vector<Reference> & dependencies)
	: dependencies(dependencies)
{
};

Formula::Formula(std::vector<Reference> && dependencies)
	: dependencies(std::move(dependencies))
{
};


Formula::Formula(const api::IFormula & other)
	: dependencies(std::move(other.getDependencies()))
{
};

std::vector<simple::Reference> Formula::getDependencies() const
{
	return this->dependencies;
};

void Formula::addDependency(const api::IReference & reference)
{
	this->dependencies.emplace_back(reference.getKeys());
};

ModelTypes Formula::GetModelType() const
{
	return ModelTypes::Formula;
};