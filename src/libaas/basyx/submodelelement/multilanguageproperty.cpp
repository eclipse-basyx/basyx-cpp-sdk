#include "multilanguageproperty.h"

namespace basyx
{
	const util::optional<Reference>& MultiLanguageProperty::get_value_id() const
	{
		return this->valueId;
	}

	void MultiLanguageProperty::set_value_id(const Reference & reference)
	{
		this->valueId = reference;
	}

	const langstringset_t & MultiLanguageProperty::get_value() const
	{
		return this->value;
	}

	langstringset_t & MultiLanguageProperty::get_value()
	{
		return this->value;
	}

	void MultiLanguageProperty::set_value(langstringset_t value)
	{
		this->value = std::move(value);
	};

	util::optional<util::string_view> MultiLanguageProperty::get_value(util::string_view language_code) const
	{
		return this->value.get(language_code);
	};

	void MultiLanguageProperty::set_value(util::string_view language_code, util::string_view value)
	{
		this->value.add(language_code, value);
	};
};