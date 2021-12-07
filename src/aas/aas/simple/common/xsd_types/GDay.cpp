/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/GDay.h>


namespace basyx {
namespace aas {
namespace simple {

GDay::GDay(uint8_t day, const Timezone & timezone)
  : timezone{timezone}
{
  this->setDay(day);
}

uint8_t GDay::getDay() const
{
  return this->day;
}

void GDay::setDay(uint8_t day)
{
  day %= 31;
  if (day == 0)
    day = 31;
  this->day = day;
}

const Timezone &GDay::getTimezone() const
{
  return this->timezone;
}

void GDay::setTimezone(const Timezone &timezone)
{
  this->timezone = timezone;
}

}
}
}
