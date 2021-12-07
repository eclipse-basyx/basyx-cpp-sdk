/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/DateTime.h>
#include <chrono>

namespace basyx {
namespace aas {
namespace simple {

DateTime::DateTime(const tm & time)
  : time{time}
{}

const tm &DateTime::getTime() const
{
  return this->time;
}

void DateTime::setTime(const tm & time)
{
  this->time = time;
}

}
}
}
