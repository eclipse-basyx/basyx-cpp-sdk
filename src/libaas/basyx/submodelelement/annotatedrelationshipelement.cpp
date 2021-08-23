#include "annotatedrelationshipelement.h"

namespace basyx
{
AnnotatedRelationshipElement::AnnotatedRelationshipElement(util::string_view idShort, Reference first, Reference second)
	: SubmodelElement(idShort)
	, first(std::move(first))
	, second(std::move(second))
{
}

};