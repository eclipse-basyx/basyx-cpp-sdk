/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_DAYTIMEDURATION_H
#define BASYX_SIMPLE_SDK_DAYTIMEDURATION_H

#include <chrono>

namespace basyx {
namespace aas {
namespace simple {

class DayTimeDuration
{
private:
  std::chrono::duration<long> duration_in_sec;
public:
  DayTimeDuration(const std::chrono::duration<long> &);

  const std::chrono::duration<long> & getDuration() const;
  void setDuration(const std::chrono::duration<long> &);
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_DAYTIMEDURATION_H */
