#pragma once

#include <string>
#include <vector>

#include <basyx/util/optional/optional.hpp>
#include <basyx/util/string_view/string_view.hpp>

namespace basyx
{
	class langstring_t
	{
	private:
		std::string code;
		std::string value;
	public:
		constexpr langstring_t(util::string_view code, util::string_view value)
			: code(code.to_string()), value(value.to_string())
		{};

		langstring_t(const langstring_t & other) = default;
		langstring_t& operator=(const langstring_t & other) = default;

		langstring_t(langstring_t && other) noexcept = default;
		langstring_t& operator=(langstring_t && other) noexcept = default;
	public:
		constexpr util::string_view get_code() const noexcept { return code; };
		constexpr util::string_view get_value() const noexcept { return value; };

		void set_value(util::string_view val) noexcept { this->value = val.to_string(); };
	};

	class langstringset_t
	{
	private:
		std::vector<langstring_t> langStrings;
	public:
		langstringset_t() = default;
		langstringset_t(util::string_view language_code, util::string_view value);
		langstringset_t(langstring_t langstring);
		langstringset_t(std::initializer_list<langstring_t> init_list);

		langstringset_t(const langstringset_t&) = default;
		langstringset_t& operator=(const langstringset_t&) = default;

		langstringset_t(langstringset_t&&) = default;
		langstringset_t& operator=(langstringset_t&&) = default;
	public:
		void add(util::string_view language_code, util::string_view value);
		void add(langstring_t langstring);
	public:
		auto begin() { return langStrings.begin(); };
		auto end() { return langStrings.end(); };
		auto begin() const { return langStrings.begin(); };
		auto end() const { return langStrings.end(); };
	public:
		util::optional<util::string_view> get(util::string_view language_code) const;
		bool contains(util::string_view language_code) const;
		bool empty() const noexcept;
		std::size_t size() const noexcept;
	};
};
