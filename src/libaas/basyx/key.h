#pragma once

#include <string>

#include <util/optional/optional.hpp>

#include <basyx/langstringset.h>

#include <basyx/enums/KeyElements.h>
#include <basyx/enums/KeyType.h>

namespace basyx
{

class Key
{
private:
	KeyElements type;
	std::string value;
	KeyType idType;
public:
	// Try to create a key from a given string
	Key(util::string_view value);

	// Create key from explicit values
	Key(KeyElements type, util::string_view value, KeyType idType);

	Key(const Key&) = default;
	Key & operator=(const Key&) = default;

	Key(Key&&) noexcept = default;
	Key & operator=(Key&&) noexcept = default;

	~Key() = default;
public:
	const KeyElements get_type() const { return type; };
	void set_type(KeyElements type) { this->type = type; };

	const std::string & get_value() const { return value; };
	void set_value(const std::string & value) { this->value = value; };

	KeyType get_id_type() const { return idType; };
	void set_id_type(KeyType idType) { this->idType = idType; };
};

};
