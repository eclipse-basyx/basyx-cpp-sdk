#ifndef BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H
#define BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H

#include <util/string_view/string_view.hpp>

namespace basyx {

enum class DataTypeIEC61360 {
	Date,
	String,
	String_Translatable,
	Real_Measure,
	Real_Count,
	Real_Currency,
	Boolean,
	Url,
	Rational,
	Rational_Measure,
	Time,
	Timestamp,
	Integer_Count,
	Integer_Measure,
	Integer_Currency,
};

class DataTypeIEC61360_
{
public:
    static DataTypeIEC61360 from_string(util::string_view name);
    static const char * to_string(DataTypeIEC61360 value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_DATATYPEIEC61360_H */
