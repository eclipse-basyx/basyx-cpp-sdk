#include "langstringset.h"

using namespace basyx;

langstringset_t::langstringset_t(util::string_view language_code, util::string_view value)
{
	this->add(language_code, value);
};

langstringset_t::langstringset_t(langstring_t langstring)
{
	this->add(std::move(langstring));
};

langstringset_t::langstringset_t(std::initializer_list<langstring_t> init_list)
	: langStrings(std::forward<std::initializer_list<langstring_t>>(init_list))
{
};


void langstringset_t::add(util::string_view language_code, util::string_view value) {
	this->add({ language_code, value });
};

void langstringset_t::add(langstring_t langstring) {
	auto code = langstring.get_code();
	auto existing = std::find_if(langStrings.begin(), langStrings.end(), [code](const auto & it) {
		return it.get_code() == code;
	});

	// overwrite, if already exists
	if (existing != langStrings.end()) {
		existing->set_value(langstring.get_value());
	}
	else {
		langStrings.emplace_back(std::move(langstring));
	}
};

util::optional<util::string_view> langstringset_t::get(util::string_view language_code) const
{
	auto langString = std::find_if(langStrings.begin(), langStrings.end(), [language_code](const auto & it) {
		return it.get_code() == language_code;
	});

	if (langString == langStrings.end())
		return {};

	return langString->get_value();
};

bool langstringset_t::contains(util::string_view language_code) const
{
	auto langString = std::find_if(langStrings.begin(), langStrings.end(), [language_code](const auto & it) {
		return it.get_code() == language_code;
	});

	return langString != langStrings.end();
};

bool langstringset_t::empty() const noexcept { return this->langStrings.empty(); };

std::size_t langstringset_t::size() const noexcept { return this->langStrings.size(); };
