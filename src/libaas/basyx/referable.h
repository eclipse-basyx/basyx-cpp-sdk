#pragma once

#include <string>

#include <util/optional/optional.hpp>

#include <basyx/langstringset.h>

namespace basyx
{

class Referable
{
private:
	std::string idShort;
	util::optional<std::string> category;
	util::optional<langstringset_t> displayName;
	util::optional<langstringset_t> description;
public:
	Referable(util::string_view idShort);

	Referable(const Referable&) = default;
	Referable(Referable&&) = default;

	Referable & operator=(const Referable&) noexcept = default;
	Referable & operator=(Referable&&) noexcept = default;

	~Referable() = default;
public:
	util::string_view getIdShort() const;
	
	const util::optional<std::string> & getCategory() const;
	void setCategory(util::string_view category);

	const util::optional<langstringset_t> & getDisplayname() const;
	util::optional<langstringset_t> & getDisplayname();
	void setDisplayname(langstringset_t displayname);

	const util::optional<langstringset_t> & getDescription() const;
	util::optional<langstringset_t> & getDescription();
	void setDescription(langstringset_t displayname);
};

};
