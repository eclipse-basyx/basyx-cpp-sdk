/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/Time.h>


namespace basyx {
namespace aas {
namespace simple {

Time::Time(uint8_t hours, uint8_t minutes, float seconds, const Timezone & timezone)
  : timezone{timezone}
{
  this->setHours(hours);
  this->setMinutes(minutes);
  this->setSeconds(seconds);
}

uint8_t Time::getHours() const
{
  return this->hours;
}

void Time::setHours(uint8_t hours)
{
  this->hours = hours % 24;
}

uint8_t Time::getMinutes() const
{
  return this->minutes;
}

void Time::setMinutes(uint8_t minutes)
{
  this->minutes = minutes % 60;
}

float Time::getSeconds() const
{
  return this->seconds;
}

void Time::setSeconds(float seconds)
{
  if (seconds < 61)
  {
    this->seconds = seconds;
    return;
  }
  int full_seconds = int(seconds);
  seconds -= full_seconds;
  full_seconds %= 60;
  this->seconds += full_seconds;
}

const Timezone & Time::getTimezone() const
{
  return this->timezone;
}

void Time::setTimezone(const Timezone & timezone)
{
  this->timezone = timezone;
}

}
}
}
