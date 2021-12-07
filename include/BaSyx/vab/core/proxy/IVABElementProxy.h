/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_CORE_PROXY_IVABELEMENTPROXY_H
#define VAB_CORE_PROXY_IVABELEMENTPROXY_H

#include <BaSyx/vab/core/util/VABPath.h>
#include <BaSyx/vab/core/IModelProvider.h>
#include <BaSyx/shared/types.h>

#include <memory>
#include <string>

namespace basyx {
namespace vab {
namespace core {
namespace proxy {

class IVABElementProxy {
public:
  virtual ~IVABElementProxy() = default;

  virtual basyx::object readElementValue(const VABPath& elementPath) = 0;
  virtual void updateElementValue(const VABPath& elementPath, const basyx::object& newValue) = 0;
  virtual void createElement(const VABPath& elementPath, const basyx::object& newValue) = 0;
  virtual void deleteElement(const VABPath& elementPath) = 0;
  virtual void deleteElement(const VABPath& elementPath, basyx::object& value) = 0;
  virtual basyx::object invoke(const VABPath& elementPath, basyx::object & parameter) = 0;

  virtual std::shared_ptr<IVABElementProxy> getDeepProxy(const VABPath & path) = 0;
  virtual VABPath getAddressPath() const = 0;
};

}
}
}
}

#endif /* VAB_CORE_PROXY_IVABELEMENTPROXY_H */
