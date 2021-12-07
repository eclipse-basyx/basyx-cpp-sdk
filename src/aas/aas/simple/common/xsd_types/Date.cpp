/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/Date.h>


namespace basyx {
namespace aas {
namespace simple {

Date::Date(const tm & date)
    : date{date}
{}

const tm &Date::getDate() const
{
  return this->date;
}

void Date::setDate(const tm & date)
{
  this->date = date;
}

}
}
}
