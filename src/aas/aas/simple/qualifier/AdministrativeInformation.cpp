/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/qualifier/AdministrativeInformation.h>

namespace basyx {
namespace aas {
namespace simple {

AdministrativeInformation::AdministrativeInformation()
{};

AdministrativeInformation::AdministrativeInformation(const std::string & version, const std::string & revision)
  : version{version}
  , revision{revision}
{};

AdministrativeInformation::AdministrativeInformation(const api::IAdministrativeInformation &other)
    : revision{*other.getRevision()}
    , version{*other.getVersion()}
{}

void AdministrativeInformation::setVersion(const std::string & version)
{
	this->version = version;
}

void AdministrativeInformation::setRevision(const std::string & revision)
{
	this->revision = revision;
}

const std::string * const AdministrativeInformation::getVersion() const
{
  if (this->version.empty())
    return nullptr;

  return &this->version;
}

const std::string * const AdministrativeInformation::getRevision() const
{
  if (this->revision.empty())
    return nullptr;

  return &this->revision;
}

}
}
}