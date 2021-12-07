/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/core/proxy/VABElementProxy.h>

namespace basyx {
namespace vab {
namespace core {
namespace proxy {

VABElementProxy::VABElementProxy(std::string address, std::shared_ptr<IModelProvider> provider) :
  address(address),
  provider(provider)
{
}

VABElementProxy::~VABElementProxy()
{
}

basyx::object VABElementProxy::readElementValue(const VABPath & elementPath)
{
  return this->provider->getModelPropertyValue(this->get_ablsolute_path(elementPath));
}

void VABElementProxy::updateElementValue(const VABPath & elementPath, const basyx::object & newValue)
{
  this->provider->setModelPropertyValue(this->get_ablsolute_path(elementPath), newValue);
}

void VABElementProxy::createElement(const VABPath & elementPath, const basyx::object & newValue)
{
  this->provider->createValue(this->get_ablsolute_path(elementPath), newValue);
}

void VABElementProxy::deleteElement(const VABPath & elementPath)
{
  this->provider->deleteValue(this->get_ablsolute_path(elementPath));
}

void VABElementProxy::deleteElement(const VABPath & elementPath, basyx::object & value)
{
  this->provider->deleteValue(this->get_ablsolute_path(elementPath), value);
}

basyx::object VABElementProxy::invoke(const VABPath & elementPath, basyx::object & parameter)
{
	return this->provider->invokeOperation(this->get_ablsolute_path(elementPath), parameter);
}

VABPath VABElementProxy::getAddressPath() const
{
  return this->address.toString();
}

VABPath VABElementProxy::get_ablsolute_path(const VABPath & elementPath)
{
	return this->address + elementPath;
}

std::shared_ptr<IVABElementProxy> VABElementProxy::getDeepProxy(const VABPath & path)
{
  auto new_path = this->address + path;
  return std::make_shared<VABElementProxy>(new_path, this->provider);
}

}
}
}
}
