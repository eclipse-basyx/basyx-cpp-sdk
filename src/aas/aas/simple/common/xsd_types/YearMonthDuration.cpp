/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/YearMonthDuration.h>


namespace basyx {
namespace aas {
namespace simple {

YearMonthDuration::YearMonthDuration(int years, int months)
{
  this->setYears(years);
  this->setMonths(months);
}

int YearMonthDuration::getYears() const
{
  return this->years;
}

int YearMonthDuration::getMonths() const
{
  return this->months;
}

void YearMonthDuration::setYears(const int & years)
{
  this->years = years;
}

void YearMonthDuration::setMonths(const int & months)
{
  this->years += months / 12;
  if (months < 0)
  {
    this->months = 12 + (months % 12);
    this->years -= 1;
  }
  else
    this->months = months % 12;
}

}
}
}
