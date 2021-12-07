/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_VAB_PROVIDER_MULTIELEMENTHANDLER_H
#define VAB_VAB_PROVIDER_MULTIELEMENTHANDLER_H

#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>

#include <BaSyx/vab/provider/IVABElementHandler.h>

#include <BaSyx/util/meta.h>

namespace basyx {
namespace vab {
namespace provider {

	template<typename... Handler>
	class VABMultiElementHandler : public IVABElementHandler {
	private:
		std::vector<IVABElementHandler*> handlers;
	public:
		VABMultiElementHandler() : handlers{ new Handler()... }
		{
		};

		virtual ~VABMultiElementHandler() { 
			for (auto * handler : handlers) {
				delete handler;
				handler = nullptr;
			}
		};

		virtual basyx::object PreProcessObject(const basyx::object& any) {
			basyx::object result = any;
			for (auto * handler : handlers) {
				result = handler->PreProcessObject(result);
			}
			return result;
		};

		virtual basyx::object PostProcessObject(const basyx::object& any) {
			basyx::object result = any;
			for (auto * handler : handlers) {
				result = handler->PostProcessObject(result);
			}
			return result;
		};

		virtual basyx::object GetElementProperty(basyx::object& element, const std::string & propertyName)
		{
			basyx::object result{ nullptr };
			for (auto * handler : handlers) {
				result = handler->GetElementProperty(element, propertyName);
				if (!result.IsNull()) {
					return result;
				}
			}
			return result;
		};

		virtual void SetModelPropertyValue(basyx::object&  element, const std::string &  propertyName, basyx::object &  newValue) {
			for (auto * handler : handlers) {
				handler->SetModelPropertyValue(element, propertyName, newValue);
			}
		};

		virtual void CreateValue(basyx::object&  element, basyx::object &  newValue) {
			for (auto * handler : handlers) {
				handler->CreateValue(element, newValue);
			}
		};

		virtual void DeleteProperty(basyx::object&  element, const std::string &  propertyName) {
			for (auto * handler : handlers) {
				handler->DeleteProperty(element, propertyName);
			}
		};

		virtual void DeleteValue(basyx::object&  element, const basyx::object &  property) {
			for (auto * handler : handlers) {
				handler->DeleteValue(element, property);
			}
		};

	};

}
}
}

#endif /* VAB_VAB_PROVIDER_MULTIELEMENTHANDLER_H */
