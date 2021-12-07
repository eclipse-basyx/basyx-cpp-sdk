/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/qualifier/Identifiable.h>

using namespace basyx::aas::simple;
using namespace basyx::aas::api;

Identifiable::Identifiable(const std::string & idShort, const Identifier & identifier)
	: Referable(idShort)
	, identifier(identifier)
{}

Identifiable::Identifiable(const IIdentifiable &other)
  : Referable(other)
  , identifier(other.getIdentification().getIdType(), other.getIdentification().getId())
  , administrativeInformation(other.getAdministrativeInformation())
{}

bool Identifiable::hasAdministrativeInformation() const noexcept
{ 
	return this->administrativeInformation.exists(); 
};

const AdministrativeInformation & Identifiable::getAdministrativeInformation() const
{
	return this->administrativeInformation;
}

AdministrativeInformation & Identifiable::getAdministrativeInformation()
{
	return this->administrativeInformation;
}

Identifier Identifiable::getIdentification() const
{
	return this->identifier;
}

void Identifiable::setAdministrativeInformation(const AdministrativeInformation &administrativeInformation)
{
  this->administrativeInformation = administrativeInformation;
}
