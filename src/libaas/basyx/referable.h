#pragma once

#include <string>

#include <util/optional/optional.hpp>

#include <basyx/langstringset.h>

namespace basyx
{

class Referable
{
private:
	std::string _idShort;
	util::optional<std::string> _category;
	util::optional<langstringset_t> _displayName;
	util::optional<langstringset_t> _description;
public:
	Referable(util::string_view idShort);

	Referable(const Referable&) = default;
	Referable(Referable&&) = default;

	Referable & operator=(const Referable&) noexcept = default;
	Referable & operator=(Referable&&) noexcept = default;

	~Referable() = default;
public:
	util::string_view get_id_short() const;
	
	const util::optional<std::string> & get_category() const;
	void set_category(util::string_view category);

	const util::optional<langstringset_t> & get_displayname() const;
	util::optional<langstringset_t> & get_displayname();
	void set_displayname(langstringset_t displayname);

	const util::optional<langstringset_t> & get_description() const;
	util::optional<langstringset_t> & get_description();
	void set_description(langstringset_t displayname);
};

};
