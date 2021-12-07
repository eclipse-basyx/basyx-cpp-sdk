/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_TIME_H
#define BASYX_SIMPLE_SDK_TIME_H

#include "Timezone.h"

#include <cstdint>
#include <string>

namespace basyx {
namespace aas {
namespace simple {

/**
 * Time represents instants of time that recur at the same point in each calendar day, or that occur in some arbitrary calendar day.
 */
class Time
{
private:
  uint8_t hours, minutes;
  float seconds;
  Timezone timezone;
public:
  Time(uint8_t hours, uint8_t minutes, float seconds, const Timezone & timezone = "Z");

  uint8_t getHours() const;
  void setHours(uint8_t hours);

  uint8_t getMinutes() const;
  void setMinutes(uint8_t minutes);

  float getSeconds() const;
  void setSeconds(float seconds);

  const Timezone & getTimezone() const;
  void setTimezone(const Timezone &);
};

}
}
}

#endif /* BASYX_SIMPLE_SDK_TIME_H */
