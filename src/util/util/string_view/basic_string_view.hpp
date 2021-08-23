#ifndef UTIL_BAISC_STRING_VIEW_HPP_
#define UTIL_BASIC_STRING_VIEW_HPP_

#include <algorithm>
#include <string>
#include <ostream>

namespace basyx::util {

template<typename CharT>
class basic_string_view
{
public:
	using char_type = CharT;
	using size_type = std::size_t;
	using const_reference = const CharT&;
	using const_iterator = const CharT*;
	using iterator = const_iterator;
public:
	static constexpr size_type npos = size_type(-1);
private:
	const char_type * _data = nullptr;
	size_type _sz = 0;
public:
	constexpr basic_string_view() noexcept = default;
	
	constexpr basic_string_view(const basic_string_view& other) noexcept = default;
	
	constexpr basic_string_view(const CharT* s, size_type count)
		: _data(s), _sz(count)
	{};

	template<typename buffer_t>
	constexpr basic_string_view(const buffer_t & buf)
		: _data(buf.data()) , _sz(buf.size())
	{
	};

	constexpr basic_string_view(const CharT* s)
		: _data(s)
	{
		constexpr std::size_t guard = 256;

		_sz = std::find(s, s + 256, CharT{ 0 }) - s;

		if (_sz < 0 || _sz >= guard )
			_sz = 0;
	};

	constexpr basic_string_view(std::nullptr_t) = delete;
public:
	// returns the number of characters
	constexpr size_type size() const noexcept { return _sz; };
	// returns the number of characters
	constexpr size_type length() const noexcept { return _sz; };
	// checks whether the view is empty
	constexpr bool empty() const noexcept { return _sz == 0; };
public:
	constexpr int compare(basic_string_view v) const noexcept
	{
		if (this->size() != v.size())
			return static_cast<int>(this->size() - v.size());

		int diff = 0;
		for (std::size_t i = 0; i < this->size(); ++i)
		{
			if (this->_data[i] != v._data[i])
				++diff;
		}

		return diff;
	};

	constexpr bool operator==(basic_string_view rhs) const noexcept { return this->compare(rhs) == 0; }
	constexpr bool operator!=(basic_string_view rhs) const noexcept { return this->compare(rhs) != 0; }
public:
	constexpr const_iterator begin() const noexcept { return &_data[0]; };
	constexpr const_iterator cbegin() const noexcept { return &_data[0]; };

	constexpr const_iterator end() const noexcept { return &_data[_sz]; };
	constexpr const_iterator cend() const noexcept { return &_data[_sz]; };
public:
	// saves the contents of the string_view to a string
	constexpr std::basic_string<CharT> to_string() const { return std::basic_string<CharT>(_data, _sz); }

	// Returns a const reference to the character at specified location pos. 
	// No bounds checking is performed : the behavior is undefined if pos >= size().
	constexpr const_reference operator[](size_type pos) const { return this->_data[pos]; };

	// returns a substring
	constexpr basic_string_view substr(size_type pos = 0, size_type count = npos) const
	{
		size_type rcount = std::min( count, size() - pos );
		return { &_data[pos], rcount };
	};
};

template<typename CharT>
inline constexpr bool operator==(basic_string_view<CharT> lhs, basic_string_view<CharT> rhs) noexcept
{
	return lhs.compare(rhs) == 0;
}

template<typename CharT>
std::ostream &operator <<(std::ostream& os, const basic_string_view<CharT>& sv) 
{
	for (const auto c : sv)
		os.put(c);

	return os;
}

}

#endif
