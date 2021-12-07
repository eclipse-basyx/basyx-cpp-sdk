/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_GYEAR_H
#define BASYX_SIMPLE_SDK_GYEAR_H

#include <BaSyx/aas/simple/common/xsd_types/Timezone.h>

namespace basyx {
namespace aas {
namespace simple {

class GYear
{
private:
  int year;
  Timezone timezone;

public:
  GYear(int year, const Timezone & timezone = "Z");

  int getYear() const;
  void setYear(int year);

  const Timezone & getTimezone() const;
  void setTimezone(const Timezone &timezone);


};

}
}
}
#endif /* BASYX_SIMPLE_SDK_GYEAR_H */
