/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_GMONTH_H
#define BASYX_SIMPLE_SDK_GMONTH_H

#include <BaSyx/aas/simple/common/xsd_types/Timezone.h>

namespace basyx {
namespace aas {
namespace simple {

class GMonth
{
private:
  uint8_t month;
  Timezone timezone;

public:
  GMonth(uint8_t month, const Timezone & timezone = "Z");

  uint8_t getMonth() const;
  void setMonth(uint8_t month);

  const Timezone & getTimezone() const;
  void setTimezone(const Timezone &timezone);
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_GMONTH_H */
