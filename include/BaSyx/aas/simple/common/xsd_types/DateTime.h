/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_DATETIME_H
#define BASYX_SIMPLE_SDK_DATETIME_H

#include <ctime>

namespace basyx {
namespace aas {
namespace simple {

class DateTime
{
private:
  tm time;

public:
  DateTime(const tm &);

  const tm & getTime() const;
  void setTime(const tm & time);
};

}
}
}
#endif //BASYX_MAP_V2_SDK_DATETIME_H
