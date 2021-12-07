/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/SubmodelElementCollection.h>

using namespace basyx::aas;
using namespace basyx::aas::simple;
using namespace basyx::aas::api;

SubmodelElementCollection::SubmodelElementCollection(const std::string & idShort, ModelingKind kind, bool ordered, bool allowDuplicates)
	: SubmodelElement(idShort, kind)
	, ordered(ordered)
	, allowDuplicates(allowDuplicates)
{}

api::IElementContainer<ISubmodelElement> & SubmodelElementCollection::getSubmodelElements()
{
	return this->elementContainer;
}

bool SubmodelElementCollection::isOrdered() const
{
	return this->ordered;
}

bool SubmodelElementCollection::isAllowDuplicates() const
{
	return this->allowDuplicates;
}

void SubmodelElementCollection::addElement(std::unique_ptr<SubmodelElement> submodelElement)
{
	this->elementContainer.addElement(std::move(submodelElement));
}
