#include "relationshipelement.h"

namespace basyx
{
RelationshipElement::RelationshipElement(util::string_view idShort, Reference first, Reference second)
	: SubmodelElement(idShort)
	, first(std::move(first))
	, second(std::move(second))
{
}

};