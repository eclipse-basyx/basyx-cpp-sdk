#include "identifier.h"

namespace basyx
{

Identifier::Identifier(KeyType idType, util::string_view id)
	: idType(idType)
	, id(id.to_string())
{};

Identifier::Identifier(util::string_view id)
	: idType(KeyType_::from_id(id))
	, id(id.to_string())
{};


bool Identifier::operator==(const Identifier & other) const
{
	return (this->getIdType() == other.getIdType()) && (this->getId() == other.getId());
};

};