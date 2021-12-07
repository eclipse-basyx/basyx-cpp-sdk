/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/submodelelement/property/ReferenceElement.h>

using namespace basyx::aas;
using namespace basyx::aas::api;
using namespace basyx::aas::simple;

ReferenceElement::ReferenceElement(const std::string & idShort, ModelingKind kind)
	: DataElement(idShort, kind)
{}

const api::IReference * const ReferenceElement::getValue() const
{
	return &this->value;
};

void ReferenceElement::setValue(const api::IReference & valueId)
{
	this->value = Reference( valueId.getKeys() );
};