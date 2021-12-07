/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/Timezone.h>


namespace basyx {
namespace aas {
namespace simple {

Timezone::Timezone()
  : timezone{"Z"}
{}

Timezone::Timezone(const std::string & timezone)
  : timezone{timezone}
{}

Timezone::Timezone(const char * timezone)
  : timezone{timezone}
{

}

const std::string &Timezone::getTimezone() const
{
  return this->timezone;
}

void Timezone::setTimezone(const std::string &timezone)
{
  this->timezone = timezone;
}

bool Timezone::isUTC() const
{
  return this->timezone.compare("Z");
}

Timezone::operator const std::string&() const
{
  return this->timezone;
}

}
}
}
