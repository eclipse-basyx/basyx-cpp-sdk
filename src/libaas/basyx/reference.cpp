#include "reference.h"

basyx::Reference::Reference(util::string_view str)
	: Reference(Key{ str })
{
}
