/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/identifier/Identifier.h>
#include <BaSyx/aas/enumerations/IdentifierType.h>

namespace basyx {
namespace aas {
namespace simple {

Identifier::Identifier()
  : idType(IdentifierType::Unknown)
{}

Identifier::Identifier(IdentifierType idType, const std::string &id)
    : idType(idType)
    , id(id)
{
};

Identifier Identifier::Custom(const std::string &id)
{
  return Identifier(IdentifierType::Custom, id);
};

Identifier Identifier::URI(const std::string &uri)
{
  return Identifier(IdentifierType::URI, uri);
};

Identifier Identifier::IRDI(const std::string &irdi)
{
  return Identifier(IdentifierType::IRDI, irdi);
};

IdentifierType Identifier::getIdType() const
{
  return this->idType;
};

const std::string &Identifier::getId() const
{
  return this->id;
};

bool operator==(const Identifier &left, const Identifier &right)
{
  if (left.getIdType() == right.getIdType())
  {
    return left.getId().compare(right.getId()) == 0;
  }
  return false;
}

}
}
}