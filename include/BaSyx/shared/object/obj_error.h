/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SHARED_OBJECT_OBJ_ERROR_H
#define BASYX_SHARED_OBJECT_OBJ_ERROR_H

#include <string>

namespace basyx {
namespace detail {

enum class error {
    None,
    PropertyNotFound,
    IndexOutOfBounds,
    NotInvokable,
    ObjectAlreadyExists,
    MalformedRequest,
    ProviderException,
};

class error_
{
public:
    static error from_string(const std::string & name);
    static const char * to_string(error value);
};

}
}

#endif /* BASYX_SHARED_OBJECT_OBJ_ERROR_H */
