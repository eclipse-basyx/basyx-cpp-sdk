#include <basyx/enums/DataTypeDefinition.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

template<>
const DataTypeDefinition_::enum_array_t DataTypeDefinition_::string_to_enum =
{
	std::make_pair("ENTITIES",  DataTypeDefinition::ENTITIES),
	std::make_pair("IDREFS",  DataTypeDefinition::IDREFS),
	std::make_pair("NMTOKENS",  DataTypeDefinition::NMTOKENS),
	std::make_pair("Integer",  DataTypeDefinition::Integer),
	std::make_pair("Long",  DataTypeDefinition::Long),
	std::make_pair("Int",  DataTypeDefinition::Int),
	std::make_pair("Short",  DataTypeDefinition::Short),
	std::make_pair("Byte",  DataTypeDefinition::Byte),
	std::make_pair("NonNegativeInteger",  DataTypeDefinition::NonNegativeInteger),
	std::make_pair("PositiveInteger",  DataTypeDefinition::PositiveInteger),
	std::make_pair("UnsignedInteger",  DataTypeDefinition::UnsignedInteger),
	std::make_pair("UnsignedLong",  DataTypeDefinition::UnsignedLong),
	std::make_pair("UnsignedInt",  DataTypeDefinition::UnsignedInt),
	std::make_pair("UnsignedShort",  DataTypeDefinition::UnsignedShort),
	std::make_pair("UnsignedByte",  DataTypeDefinition::UnsignedByte),
	std::make_pair("NonPositiveInteger",  DataTypeDefinition::NonPositiveInteger),
	std::make_pair("NegativeInteger",  DataTypeDefinition::NegativeInteger),
	std::make_pair("DaytimeDuration",  DataTypeDefinition::DaytimeDuration),
	std::make_pair("YearMonthDuration",  DataTypeDefinition::YearMonthDuration),
	std::make_pair("AnyURI",  DataTypeDefinition::AnyURI),
	std::make_pair("Base64Binary",  DataTypeDefinition::Base64Binary),
	std::make_pair("Boolean",  DataTypeDefinition::Boolean),
	std::make_pair("Date",  DataTypeDefinition::Date),
	std::make_pair("DateTime",  DataTypeDefinition::DateTime),
	std::make_pair("Decimal",  DataTypeDefinition::Decimal),
	std::make_pair("Double",  DataTypeDefinition::Double),
	std::make_pair("Duration",  DataTypeDefinition::Duration),
	std::make_pair("Float",  DataTypeDefinition::Float),
	std::make_pair("GDay",  DataTypeDefinition::GDay),
	std::make_pair("GMonth",  DataTypeDefinition::GMonth),
	std::make_pair("GMonthDay",  DataTypeDefinition::GMonthDay),
	std::make_pair("GYearMonth",  DataTypeDefinition::GYearMonth),
	std::make_pair("HexBinary",  DataTypeDefinition::HexBinary),
	std::make_pair("NOTATION",  DataTypeDefinition::NOTATION),
	std::make_pair("QName",  DataTypeDefinition::QName),
	std::make_pair("String",  DataTypeDefinition::String),
	std::make_pair("Time",  DataTypeDefinition::Time),
	std::make_pair("NormalizedString",  DataTypeDefinition::NormalizedString),
	std::make_pair("Token",  DataTypeDefinition::Token),
	std::make_pair("Language",  DataTypeDefinition::Language),
	std::make_pair("NCName",  DataTypeDefinition::NCName),
	std::make_pair("ENTITY",  DataTypeDefinition::ENTITY),
	std::make_pair("ID",  DataTypeDefinition::ID),
	std::make_pair("IDREF",  DataTypeDefinition::IDREF)
};