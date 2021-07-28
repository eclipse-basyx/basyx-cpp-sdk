#include "key.h"

namespace basyx
{

Key::Key(std::string type, util::string_view value, KeyType idType)
	: type(type)
	, value(value.to_string())
	, idType(idType)
{};



};