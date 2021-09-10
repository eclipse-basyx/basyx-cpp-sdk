#include "reference.h"

using namespace basyx;

basyx::Reference::Reference(util::string_view str)
	: Reference(Key{ str })
{
}

Reference::Reference(const Referable & referable)
{
	
}
