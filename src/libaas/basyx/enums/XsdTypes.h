#ifndef BASYX_SUBMODEL_ENUMERATIONS_XSDTYPES_H
#define BASYX_SUBMODEL_ENUMERATIONS_XSDTYPES_H

#include <string>

namespace basyx {
namespace submodel {

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
