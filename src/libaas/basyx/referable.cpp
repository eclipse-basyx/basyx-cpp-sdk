#include "referable.h"

namespace basyx
{

Referable::Referable(util::string_view idShort)
	: idShort( idShort.to_string() )
	, parent(nullptr)
{};

util::string_view Referable::getIdShort() const
{
	return this->idShort;
}

const util::optional<std::string>& Referable::getCategory() const
{
	return category;
}

void Referable::setCategory(util::string_view category)
{
	this->category.emplace(category.to_string());
}

const util::optional<langstringset_t> & Referable::getDisplayname() const
{
	return this->displayName;
}

util::optional<langstringset_t> & Referable::getDisplayname()
{
	return this->displayName;
}

void Referable::setDisplayname(langstringset_t displayname)
{
	this->displayName = std::move(displayname);
}

const util::optional<langstringset_t> & Referable::getDescription() const
{
	return this->description;
}

util::optional<langstringset_t> & Referable::getDescription()
{
	return this->description;
}

void Referable::setDescription(langstringset_t description)
{
	this->description = std::move(description);
}

};
