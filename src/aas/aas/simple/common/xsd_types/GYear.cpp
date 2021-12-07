/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/GYear.h>


namespace basyx {
namespace aas {
namespace simple {

GYear::GYear(int year, const Timezone & timezone)
  : year{year}
  , timezone{timezone}
{}

int GYear::getYear() const
{
  return year;
}

void GYear::setYear(int year)
{
  this->year = this->year;
}

const Timezone & GYear::getTimezone() const
{
  return this->timezone;
}

void GYear::setTimezone(const Timezone & timezone)
{
  this->timezone = timezone;
}

}
}
}
