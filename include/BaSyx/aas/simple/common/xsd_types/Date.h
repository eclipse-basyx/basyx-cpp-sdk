/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_DATE_H
#define BASYX_SIMPLE_SDK_DATE_H

#include <ctime>

namespace basyx {
namespace aas {
namespace simple {

class Date
{
private:
  tm date;

public:
  Date(const tm &);

  const tm & getDate() const;
  void setDate(const tm &);
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_DATE_H */
