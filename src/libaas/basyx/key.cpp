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
	, idType(KeyType_::from_id(value))
{
};

};