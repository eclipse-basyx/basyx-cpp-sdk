/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENUMERATIONS_XSDTYPES_H
#define BASYX_SUBMODEL_ENUMERATIONS_XSDTYPES_H

#include <string>

namespace basyx {
namespace aas {

enum class XsdTypes {
    xsd_NotSupported,
    xsd_boolean,
    xsd_byte,
    xsd_short,
    xsd_int,
    xsd_long,
    xsd_unsignedByte,
    xsd_unsignedShort,
    xsd_unsignedInt,
    xsd_unsignedLong,
    xsd_double,
    xsd_float,
    xsd_string,
    xsd_anyuri,
    xsd_date,
    xsd_dateTime,
    xsd_dayTimeDuration,
    xsd_yearMonthDuration,
    xsd_time,
    xsd_gYearMonth,
    xsd_gYear,
    xsd_gMonthDay,
    xsd_gDay,
    xsd_gMonth,
};

class XsdTypes_
{
public:
    static XsdTypes from_string(const std::string & name);
    static const char * to_string(XsdTypes value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_XSDTYPES_H */
