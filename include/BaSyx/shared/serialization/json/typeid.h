/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_SERIALIZATION_JSON_TYPEID_H
#define BASYX_SHARED_SERIALIZATION_JSON_TYPEID_H

#include <string>

namespace basyx {
namespace serialization {
    static constexpr char typeSpecifier[] = "_basyxTypes";
    static constexpr char typeIdSpecifier[] = "typeid";
    static constexpr char arrayTypeSpecifier[] = "type";
    static constexpr char valueSpecifier[] = "_value";
    static constexpr char sizeSpecifier[] = "size";
    static constexpr char mapSpecifier[] = "map";
    static constexpr char collectionSpecifier[] = "collection";
    static constexpr char arraySpecifier[] = "array";

    template <typename T>
    struct basysType {
        static constexpr char string[] = "unknown";
    };

    template <>
    struct basysType<bool> {
        static constexpr char string[] = "boolean";
    };

    template <>
    struct basysType<int> {
        static constexpr char string[] = "int";
    };

    template <>
    struct basysType<float> {
        static constexpr char string[] = "float";
    };

    template <>
    struct basysType<double> {
        static constexpr const char string[] = "double";
    };

    template <>
    struct basysType<char> {
        static constexpr const char string[] = "character";
    };

    template <>
    struct basysType<std::string> {
        static constexpr const char string[] = "string";
    };
}
};

template <typename T>
constexpr char basyx::serialization::basysType<T>::string[];

#endif /* BASYX_SHARED_SERIALIZATION_JSON_TYPEID_H */
