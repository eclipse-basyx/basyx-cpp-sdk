#pragma once

#include <basyx/util/string_view/basic_string_view.hpp>
#include <basyx/util/string_view/string_view.hpp>
#include <basyx/util/optional/optional.hpp>


namespace basyx::util::algorithm
{

struct string
{
	template<typename CharT>
	using splitList_t = std::vector<util::basic_string_view<CharT>>;

	template<typename StringT, typename CharT>
	static splitList_t<CharT> split(const StringT & str, const CharT delimiter)
	{
		splitList_t<CharT> splits;

		util::optional<std::size_t> wordBegin;
		for (std::size_t i = 0; i < str.size(); ++i) {
			if (str[i] == delimiter && wordBegin) {

				auto begin = &str[*wordBegin];
				auto end = &str[i];

				splits.emplace_back( begin, end );
					wordBegin.reset();
			}
			else if (str[i] != delimiter && !wordBegin) {
				wordBegin = i;
			};
		};

		if (wordBegin)
			splits.emplace_back(&str[*wordBegin], &str[str.size()]);

		return splits;
	};

	//static auto split(util::string_view str, const char delimiter) { return split(str, delimiter); };

};

};