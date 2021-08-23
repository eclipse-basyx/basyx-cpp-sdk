#pragma once

#include <cstdint>

namespace basyx
{

struct basyx_enum_base
{
public:
	using val_t = uint32_t;
	constexpr static val_t uninitialized = -1;
protected:
	val_t _val = 0;
public:
	constexpr basyx_enum_base() : _val(uninitialized) {};
	constexpr basyx_enum_base(const val_t _val) : _val(_val) {};
	constexpr basyx_enum_base(int _val) : _val(_val) {};
public:
	basyx_enum_base(const basyx_enum_base &) = default;
	constexpr basyx_enum_base& operator=(const basyx_enum_base &) = default;

	basyx_enum_base(basyx_enum_base &&) = default;
	constexpr basyx_enum_base& operator=(basyx_enum_base &&) = default;

	~basyx_enum_base() = default;
public:
	constexpr basyx_enum_base& operator=(val_t val) { this->_val = val; return *this; };

	template<typename T>
	constexpr bool operator==(const T t) { return static_cast<const val_t>(t) == this->_val; }

	operator const val_t() const { return this->_val; };
};

};
