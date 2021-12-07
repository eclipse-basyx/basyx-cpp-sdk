/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_CORE_PROXY_VABELEMENTPROXY_H
#define VAB_CORE_PROXY_VABELEMENTPROXY_H

#include <BaSyx/vab/core/proxy/IVABElementProxy.h>

#include <BaSyx/vab/core/util/VABPath.h>
#include <BaSyx/vab/core/IModelProvider.h>
#include <BaSyx/shared/types.h>

#include <memory>
#include <string>

namespace basyx {
namespace vab {
namespace core {
namespace proxy {

class VABElementProxy : public IVABElementProxy {
public:
  VABElementProxy(std::string address, std::shared_ptr<IModelProvider> provider);
  ~VABElementProxy();

  virtual basyx::object readElementValue(const VABPath& elementPath) override;
  virtual void updateElementValue(const VABPath& elementPath, const basyx::object& newValue) override;
  virtual void createElement(const VABPath& elementPath, const basyx::object& newValue) override;
  virtual void deleteElement(const VABPath& elementPath) override;
  virtual void deleteElement(const VABPath& elementPath, basyx::object& value) override;
  virtual basyx::object invoke(const VABPath& elementPath, basyx::object & parameter) override;
  virtual VABPath getAddressPath() const override;

private:
  VABPath get_ablsolute_path(const VABPath& elementPath);

private:
  VABPath address;
  std::shared_ptr<IModelProvider> provider;

  // Inherited via IVABElementProxy
  virtual std::shared_ptr<IVABElementProxy> getDeepProxy(const VABPath & path) override;
};

}
}
}
}

#endif /* VAB_CORE_PROXY_VABELEMENTPROXY_H */
