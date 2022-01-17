#ifndef UTIL_STRING_VIEW_HPP_
#define UTIL_STRING_VIEW_HPP_

#include <cstddef>
#include <cstring>

#include <algorithm>

#include <basyx/util/string_view/basic_string_view.hpp>

namespace basyx::util {

	using string_view = util::basic_string_view<char>;
	using wstring_view = util::basic_string_view<wchar_t>;
	using u8string_view = util::basic_string_view<uint8_t>;
	using u16string_view = util::basic_string_view<char16_t>;
	using u32string_view = util::basic_string_view<char32_t>;
}

#endif