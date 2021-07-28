#pragma once

#include <string>

#include <util/optional/optional.hpp>

#include <basyx/langstringset.h>

#include <basyx/base/basyx_enum_base.h>

namespace basyx
{

struct IdentifierType : public basyx_enum_base
{
private:
	using basyx_enum_base::basyx_enum_base;
public:
	static const IdentifierType Custom;
	static const IdentifierType IRDI;
	static const IdentifierType IRI;
};

struct LocalKeyType : public basyx_enum_base
{
private:
	using basyx_enum_base::basyx_enum_base;
public:
	static const LocalKeyType IdShort;
	static const LocalKeyType Fragmentid;
};

struct KeyType : public basyx_enum_base
{
public:
	using IdentifierType = IdentifierType;
	using LocalKeyType = LocalKeyType;
private:
	using basyx_enum_base::basyx_enum_base;
public:
	KeyType(LocalKeyType rhs) : basyx_enum_base{ rhs } {};
	KeyType(IdentifierType rhs) : basyx_enum_base{ rhs } {};
};

class Key
{
private:
	std::string type;
	std::string value;
	KeyType idType;
public:
	// Try to create a key from a given string
	Key(util::string_view value);

	// Create key from explicit values
	Key(std::string type, util::string_view value, KeyType idType);

	Key(const Key&) = default;
	Key(Key&&) = default;

	Key & operator=(const Key&) = default;
	Key & operator=(Key&&) = default;

	~Key() = default;
public:
	const std::string & get_type() const { return type; };
	void set_type(const std::string & type) { this->type = type; };

	const std::string & get_value() const { return value; };
	void set_value(const std::string & value) { this->value = value; };

	KeyType get_id_type() const { return idType; };
	void set_id_type(KeyType idType) { this->idType = idType; };
};

};
