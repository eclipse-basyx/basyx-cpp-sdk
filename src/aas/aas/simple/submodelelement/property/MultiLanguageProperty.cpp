/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/property/MultiLanguageProperty.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::simple;

MultiLanguageProperty::MultiLanguageProperty(const std::string & idShort, ModelingKind kind )
	: SubmodelElement(idShort, kind)
{}

const api::ILangStringSet * const MultiLanguageProperty::getValue()
{
	return this->value.get();
}

const api::IReference * const MultiLanguageProperty::getValueId() const
{
	return this->valueId.get();
}

void MultiLanguageProperty::setValueId(std::unique_ptr<Reference> valueId)
{
	this->valueId = std::move(valueId);
}