#include "key.h"

namespace basyx
{

Key::Key(KeyElements type, util::string_view value, KeyType idType)
	: type(type)
	, value(value.to_string())
	, idType(idType)
{};

Key::Key(util::string_view value)
	: type(KeyElements::GlobalReference)
	, value(value.to_string())
	, idType(KeyType::IdentifierType::Custom)
{
	// If begins with an URI schema, assume it's an IRDI
	if ((value.substr(0, 7) == "http://") || (value.substr(0, 8) == "https://") || (value.substr(0, 6) == "urn://"))
	{
		this->idType = KeyType::IdentifierType::IRI;
	}
	// check if it is an ISO/IEC 11179-6 eClass identifier, see: https://wiki.eclass.eu/wiki/IRDI
	// e.g. 0173-1#02-AAR972#002 
	else if(value.length() == 20 &&  
			value[4] == '-' && value[6] == '#' && value[9] == '-' && value[16] == '#'  )
	{
		this->idType = KeyType::IdentifierType::IRDI;
	}

	// otherwise, assume it's a Custom identifier
};

};