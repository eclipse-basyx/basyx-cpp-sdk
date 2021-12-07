/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_ANYTYPECHECKER_H
#define BASYX_SHARED_ANYTYPECHECKER_H

#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>

#include <string>

namespace basyx {

namespace PropertyTypeInfo {
    static constexpr char STRING[] = "string";
    static constexpr char INT[] = "int";
    static constexpr char COLLECTION[] = "collection";
    static constexpr char MAP[] = "map";
    static constexpr char BOOL[] = "boolean";
    static constexpr char DOUBLE[] = "double";
    static constexpr char FLOAT[] = "long";
    static constexpr char PROPNULL[] = "null";
    static constexpr char NONETYPE[] = "Type not specified";
}

static std::string getPropertyTypeInfo(const basyx::object& object)
{
    if (object.InstanceOf<std::string>())
        return PropertyTypeInfo::STRING;
    if (object.InstanceOf<int>())
        return PropertyTypeInfo::INT;
    if (object.InstanceOf<basyx::object::object_list_t>())
        return PropertyTypeInfo::COLLECTION;
    if (object.InstanceOf<basyx::object::object_map_t>())
        return PropertyTypeInfo::MAP;
    if (object.InstanceOf<bool>())
        return PropertyTypeInfo::BOOL;
    if (object.InstanceOf<double>())
        return PropertyTypeInfo::DOUBLE;
    if (object.InstanceOf<float>())
        return PropertyTypeInfo::FLOAT;
    if (object.InstanceOf<std::nullptr_t>())
        return PropertyTypeInfo::PROPNULL;
    return PropertyTypeInfo::NONETYPE;
}

}

#endif /* BASYX_SHARED_ANYTYPECHECKER_H */
