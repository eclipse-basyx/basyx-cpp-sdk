/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/GMonth.h>


namespace basyx {
namespace aas {
namespace simple {

GMonth::GMonth(uint8_t month, const Timezone &timezone)
  : timezone{timezone}
{
  this->setMonth(month);
}


uint8_t GMonth::getMonth() const
{
  return this->month;
}

void GMonth::setMonth(uint8_t month)
{
  month %= 12;
  if (month == 0)
    month = 12;
  this->month = month;
}

const Timezone &GMonth::getTimezone() const
{
  return this->timezone;
}

void GMonth::setTimezone(const Timezone &timezone)
{
  this->timezone = timezone;
}

}
}
}
