/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SIMPLE_SDK_ANYURI_H
#define BASYX_SIMPLE_SDK_ANYURI_H

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace simple {

class AnyURI
{
private:
  std::string uri;

public:
  AnyURI(const std::string & uri);

  const std::string & getUri() const;
  void setURI(const std::string & uri);
};

}
}
}
#endif //BASYX_MAP_V2_SDK_ANYURI_H
