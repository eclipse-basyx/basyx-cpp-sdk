#include <basyx/enums/AssetKind.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

using enum_pair_t = std::pair<const char*, AssetKind>;

static const std::array<enum_pair_t, 3> string_to_enum = 
{
    std::make_pair("Type",  AssetKind::Type),
    std::make_pair("Instance", AssetKind::Instance),
};

AssetKind AssetKind_::from_string(util::string_view name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * AssetKind_::to_string(AssetKind value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

