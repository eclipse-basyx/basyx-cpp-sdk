/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_CORE_OBJ_IMODELPROVIDER_H
#define VAB_CORE_OBJ_IMODELPROVIDER_H

#include <BaSyx/shared/types.h>
#include <BaSyx/shared/object.h>

#include <map>
#include <string>

namespace basyx {
namespace vab {
namespace core {

    class IModelProvider {

    public:
		virtual ~IModelProvider() {};
    public:
        virtual basyx::object getModelPropertyValue(const std::string& path) = 0;
        virtual basyx::object::error setModelPropertyValue(const std::string& path, const basyx::object newValue) = 0;
        virtual basyx::object::error createValue(const std::string& path, const basyx::object addedValue) = 0;
        virtual basyx::object::error deleteValue(const std::string& path, basyx::object deletedValue) = 0;
        virtual basyx::object::error deleteValue(const std::string& path) = 0;
        virtual basyx::object invokeOperation(const std::string& path, basyx::object parameter) = 0;
    };


}
}
};


#endif /* VAB_CORE_IMODELPROVIDER_H */
