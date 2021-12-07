/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_GDAY_H
#define BASYX_SIMPLE_SDK_GDAY_H

#include <BaSyx/aas/simple/common/xsd_types/Timezone.h>

namespace basyx {
namespace aas {
namespace simple {

class GDay
{
private:
uint8_t day;
  Timezone timezone;

public:
  GDay(uint8_t day, const Timezone & timezone = "Z");

  uint8_t getDay() const;
  void setDay(uint8_t day);

  const Timezone & getTimezone() const;
  void setTimezone(const Timezone &timezone);
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_GDAY_H */
