#pragma once

#include <cstdint>
#include <string>

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {
namespace detail
{

	template<typename T> struct data_type_def {};
	template<> struct data_type_def<int8_t> { static constexpr char value_type[] = "byte"; };
	template<> struct data_type_def<char> { static constexpr char value_type[] = "byte"; };
	template<> struct data_type_def<uint8_t> { static constexpr char value_type[] = "unsignedByte"; };
	template<> struct data_type_def<int16_t> { static constexpr char value_type[] = "short"; };
	template<> struct data_type_def<uint16_t> { static constexpr char value_type[] = "unsignedShort"; };
	template<> struct data_type_def<int32_t> { static constexpr char value_type[] = "int"; };
	template<> struct data_type_def<uint32_t> { static constexpr char value_type[] = "unsignedInt"; };
	template<> struct data_type_def<int64_t> { static constexpr char value_type[] = "long"; };
	template<> struct data_type_def<uint64_t> { static constexpr char value_type[] = "unsignedLong"; };
	template<> struct data_type_def<float> { static constexpr char value_type[] = "float"; };
	template<> struct data_type_def<double> { static constexpr char value_type[] = "double"; };
	template<> struct data_type_def<bool> { static constexpr char value_type[] = "boolean"; };
	template<> struct data_type_def<std::string> { static constexpr char value_type[] = "string"; };

	template<typename T> struct data_type_map { using value_type_t = T; };
	template<> struct data_type_map<std::string> { using value_type_t = std::string; };
	template<> struct data_type_map<const char *> { using value_type_t = std::string; };
	template<> struct data_type_map<util::string_view> { using value_type_t = std::string; };

};
}
