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
	langstringset_t _displayName;
	langstringset_t _description;
public:
	Referable(const std::string & idShort);

	Referable(const Referable&) = default;
	Referable(Referable&&) = default;

	Referable & operator=(const Referable&) = default;
	Referable & operator=(Referable&&) = default;

	~Referable() = default;
public:
	util::string_view get_id_short() const;
	
	util::optional<std::string> & get_category();
	void set_category(util::string_view category);

	const langstringset_t & displayname() const;
	langstringset_t & displayname();
	
	const langstringset_t & description() const;
	langstringset_t & description();
};

};
