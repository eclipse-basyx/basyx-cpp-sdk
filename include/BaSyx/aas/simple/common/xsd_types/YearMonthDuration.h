/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_YEARMONTHDURATION_H
#define BASYX_SIMPLE_SDK_YEARMONTHDURATION_H

namespace basyx {
namespace aas {
namespace simple {

class YearMonthDuration
{
private:
  int years = 0, months = 0;
public:
  YearMonthDuration(int years, int months);

  int getYears() const;
  int getMonths() const;

  void setYears(const int &);
  void setMonths(const int &);
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_YEARMONTHDURATION_H */
