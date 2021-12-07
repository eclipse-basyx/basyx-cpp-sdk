/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/qualifier/Identifiable.h>

using namespace basyx::aas;
using namespace basyx::aas::map;
using namespace basyx::aas::api;

constexpr char Identifiable::Path::IdType[];
constexpr char Identifiable::Path::Id[];
constexpr char Identifiable::Path::AdministrativeInformation[];
constexpr char Identifiable::Path::Identifier[];

Identifiable::Identifiable(const std::string & idShort, const simple::Identifier & identifier)
	: Referable(idShort)
	, vab::ElementMap()
{
	auto identifierMap = basyx::object::make_map();
	identifierMap.insertKey(Path::Id, identifier.getId());
	identifierMap.insertKey(Path::IdType, IdentifierType_::to_string(identifier.getIdType()));
	this->map.insertKey(Path::Identifier, identifierMap);
}

bool Identifiable::hasAdministrativeInformation() const noexcept
{
  return ! this->map.getProperty(Path::AdministrativeInformation).IsNull();
};

simple::Identifier Identifiable::getIdentification() const
{
	auto identifierMap = this->map.getProperty(Path::Identifier);
	return simple::Identifier{
		IdentifierType_::from_string(identifierMap.getProperty(Path::IdType).Get<std::string&>()),
		identifierMap.getProperty(Path::Id).Get<std::string&>()
	};
}

const api::IAdministrativeInformation & Identifiable::getAdministrativeInformation() const
{
	return this->administrativeInformation;
}

api::IAdministrativeInformation & Identifiable::getAdministrativeInformation()
{
	return this->administrativeInformation;
}

void Identifiable::setAdministrativeInformation(const AdministrativeInformation &administrativeInformation)
{
  this->administrativeInformation = administrativeInformation;
  this->map.insertKey(Path::AdministrativeInformation, this->administrativeInformation.getMap());
}
