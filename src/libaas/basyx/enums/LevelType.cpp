#include <basyx/enums/LevelType.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

using enum_pair_t = std::pair<const char*, LevelType>;

static const std::array<enum_pair_t, 4> string_to_enum = 
{
    std::make_pair("Max",  LevelType::Max),
    std::make_pair("Min", LevelType::Min),
    std::make_pair("Nom", LevelType::Nom),
    std::make_pair("Typ", LevelType::Typ),
};

LevelType LevelType_::from_string(util::string_view name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * LevelType_::to_string(LevelType value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

