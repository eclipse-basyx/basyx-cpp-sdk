/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_GYEARMONTH_H
#define BASYX_SIMPLE_SDK_GYEARMONTH_H

#include "Timezone.h"

namespace basyx {
namespace aas {
namespace simple {

class GYearMonth
{
private:
  int year;
  uint8_t month;
private:
  Timezone timezone;
public:
  GYearMonth(int year, uint8_t month, const Timezone & = Timezone{});

  int getYear() const;
  void setYear(int year);

  uint8_t getMonth() const;
  void setMonth(uint8_t month);

  const Timezone &getTimezone() const;
  void setTimezone(const Timezone &timezone);
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_GYEARMONTH_H */
