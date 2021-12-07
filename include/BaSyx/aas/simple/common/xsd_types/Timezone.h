/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_TIMEZONE_H
#define BASYX_SIMPLE_SDK_TIMEZONE_H

#include <string>

namespace basyx {
namespace aas {
namespace simple {

class Timezone
{
private:
  std::string timezone;

public:
  Timezone();
  Timezone(const std::string &);
  Timezone(const char*);

  const std::string &getTimezone() const;
  void setTimezone(const std::string &timezone);

  bool isUTC() const;

  operator const std::string & () const;
};

}
}
}
#endif /* BASYX_SIMPLE_SDK_TIMEZONE_H */
