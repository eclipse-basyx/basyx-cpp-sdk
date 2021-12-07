/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/GYearMonth.h>


namespace basyx {
namespace aas {
namespace simple {

GYearMonth::GYearMonth(int year, uint8_t month, const Timezone & timezone)
  : year{year}
  , timezone{timezone}
{
  this->setMonth(month);
}

int GYearMonth::getYear() const
{
  return year;
}

void GYearMonth::setYear(int year)
{
  this->year = year;
}

uint8_t GYearMonth::getMonth() const
{
  return month;
}

void GYearMonth::setMonth(uint8_t month)
{
  //fit month in 1-12
  month %= 13;
  if (!month)
    month = 12;
  this->month = month;
}

const Timezone &GYearMonth::getTimezone() const
{
  return timezone;
}

void GYearMonth::setTimezone(const Timezone &timezone)
{
  this->timezone = timezone;
}

}
}
}
