#pragma once

#include <util/string_view/basic_string_view.hpp>
#include <util/optional/optional.hpp>


namespace basyx::util::algorithm
{

struct string 
{
	template<typename CharT>
	using splitList_t = std::vector<util::basic_string_view<CharT>>;

	template<typename CharT>
	static splitList_t<CharT> split(util::basic_string_view<CharT> str, const CharT delimiter)
	{
		splitList_t<CharT> splits;

		util::optional<std::size_t> wordBegin;
		for (std::size_t i = 0; i < str.size(); ++i) {
			if (str[i] == delimiter && wordBegin) {
				splits.push_back(str.substr(*wordBegin, i - *wordBegin));
				wordBegin.reset();
			}
			else if (str[i] != delimiter && !wordBegin) {
				wordBegin = i;
			};
		};

		if (wordBegin)
			splits.push_back(str.substr(*wordBegin, str.length()));

		return splits;
	};
};



}