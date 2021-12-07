/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/map_v2/qualifier/AdministrativeInformation.h>


namespace basyx {
namespace aas {
namespace map {

using namespace basyx::aas::api;

constexpr char AdministrativeInformation::Path::Version[];
constexpr char AdministrativeInformation::Path::Revision[];

AdministrativeInformation::AdministrativeInformation()
{}

AdministrativeInformation::AdministrativeInformation(const std::string &version, const std::string &revision)
  : HasDataSpecification()
{
  this->map.insertKey(Path::Version, version);
  this->map.insertKey(Path::Revision, revision);
}

AdministrativeInformation::AdministrativeInformation(basyx::object obj)
  : HasDataSpecification(obj)
{
  if ( not obj.getProperty(Path::Version).IsNull() )
    this->map.insertKey(Path::Version, obj.getProperty(Path::Version).GetStringContent());

  if ( not obj.getProperty(Path::Version).IsNull() )
    this->map.insertKey(Path::Revision, obj.getProperty(Path::Revision).GetStringContent());
}

void AdministrativeInformation::setVersion(const std::string &version)
{
  this->map.insertKey(Path::Version, version);
}

void AdministrativeInformation::setRevision(const std::string &revision)
{
  this->map.insertKey(Path::Revision, revision);
}

bool AdministrativeInformation::hasVersion() const
{
  return ! this->map.getProperty(Path::Version).IsNull();
}

bool AdministrativeInformation::hasRevision() const
{
  return ! this->map.getProperty(Path::Revision).IsNull();
}

const std::string * const AdministrativeInformation::getVersion() const
{
  auto version = this->map.getProperty(Path::Version);
  if (version.IsNull())
    return nullptr;

  return &version.Get<std::string&>();
}

const std::string * const AdministrativeInformation::getRevision() const
{
  auto revision = this->map.getProperty(Path::Revision);
  if (revision.IsNull())
    return nullptr;

  return &revision.Get<std::string&>();
}

}
}
}
