#pragma once

#include <util/optional/optional.hpp>
#include <util/string_view/string_view.hpp>

namespace basyx
{

template<typename EnumType, std::size_t N>
struct basyx_enum_base
{
private:
	using enum_pair_t = std::pair<const char*, EnumType>;
	using enum_array_t = std::array<enum_pair_t, N>;
private:
	static const enum_array_t string_to_enum;
public:
	static util::optional<EnumType> from_string(util::string_view name)
	{
		auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(),
			[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
		});

		if (pair == string_to_enum.end())
			return {};

		return pair->second;
	};

	static const char * to_string(EnumType value)
	{
		auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(),
			[value](const enum_pair_t & pair) {
			return value == pair.second;
		});

		if (pair == string_to_enum.end())
			return nullptr;

		return pair->first;
	};
};

};
