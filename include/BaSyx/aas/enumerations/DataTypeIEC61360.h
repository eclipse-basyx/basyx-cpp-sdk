/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H
#define BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H

#include <string>

namespace basyx {
namespace aas {

enum class DataTypeIEC61360 {
    Boolean,
    Date,
    Rational,
    Rational_Measure,
    Real_Count,
    Real_Currency,
    Real_Measure,
    String,
    String_Translatable,
    Time,
    Timestamp,
    Url,
    Undefined,
};

class DataTypeIEC61360_
{
public:
    static DataTypeIEC61360 from_string(const std::string & name);
    static const char * to_string(DataTypeIEC61360 value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H */
