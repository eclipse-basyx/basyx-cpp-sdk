#ifndef BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H

#include <basyx/base/basyx_enum_base.h>

namespace basyx {

enum class DataTypeDefinition {
	ENTITIES,
	IDREFS,
	NMTOKENS,
	Integer,
	Long,
	Int,
	Short,
	Byte,
	NonNegativeInteger,
	PositiveInteger,
	UnsignedInteger,
	UnsignedLong,
	UnsignedInt,
	UnsignedShort,
	UnsignedByte,
	NonPositiveInteger,
	NegativeInteger,
	DaytimeDuration,
	YearMonthDuration,
	AnyURI,
	Base64Binary,
	Boolean,
	Date,
	DateTime,
	Decimal,
	Double,
	Duration,
	Float,
	GDay,
	GMonth,
	GMonthDay,
	GYearMonth,
	HexBinary,
	NOTATION,
	QName,
	String,
	Time,
	NormalizedString,
	Token,
	Language,
	NCName,
	ENTITY,
	ID,
	IDREF,
};

using DataTypeDefinition_ = basyx::basyx_enum_base<DataTypeDefinition, 44>;

}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H */
