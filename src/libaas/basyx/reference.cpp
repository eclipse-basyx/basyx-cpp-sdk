#include "reference.h"

#include <basyx/serialization/private/deserializer_priv.h>

using namespace basyx;

Reference::Reference(basyx::base::Token<serialization::priv::Deserializer> t) {}

basyx::Reference::Reference(util::string_view str)
	: Reference(Key{ str })
{
}

Reference::Reference(const Referable & referable)
{
	
}

