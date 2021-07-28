#ifndef BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H
#define BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H

#include <string>

namespace basyx {
namespace submodel {

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
