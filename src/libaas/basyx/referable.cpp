#include "referable.h"

namespace basyx
{

Referable::Referable(util::string_view idShort)
	: _idShort( idShort.to_string() )
{};

util::string_view Referable::get_id_short() const
{
	return this->_idShort;
}

const util::optional<std::string>& Referable::get_category() const
{
	return _category;
}

void Referable::set_category(util::string_view category)
{
	this->_category.emplace(category.to_string());
}

const util::optional<langstringset_t> & Referable::get_displayname() const
{
	return this->_displayName;
}

util::optional<langstringset_t> & Referable::get_displayname()
{
	return this->_displayName;
}

void Referable::set_displayname(langstringset_t displayname)
{
	this->_displayName = std::move(displayname);
}

const util::optional<langstringset_t> & Referable::get_description() const
{
	return this->_description;
}

util::optional<langstringset_t> & Referable::get_description()
{
	return this->_description;
}

void Referable::set_description(langstringset_t description)
{
	this->_description = std::move(description);
}

};