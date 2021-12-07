/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/xsd_types/DayTimeDuration.h>
#include <chrono>


namespace basyx {
namespace aas {
namespace simple {

DayTimeDuration::DayTimeDuration(const std::chrono::duration<long> & duration)
  : duration_in_sec{duration}
{}

const std::chrono::duration<long> &DayTimeDuration::getDuration() const
{
  return this->duration_in_sec;
}

void DayTimeDuration::setDuration(const std::chrono::duration<long> & duration)
{
  this->duration_in_sec = duration;
}

}
}
}
