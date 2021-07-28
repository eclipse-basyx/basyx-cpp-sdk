#include "identifier.h"

namespace basyx
{

Identifier::Identifier(IdentifierType idType, util::string_view id)
	: idType(idType)
	, id(id.to_string())
{};



};