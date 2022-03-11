#pragma once

#include <basyx/util/optional/optional.hpp>

#include <basyx/langstringset.h>

#include <basyx/key.h>

#include <string>

namespace basyx
{

class Identifier
{
private:
	KeyType idType;
	std::string id;
private:
public:
   Identifier(KeyType idType, util::string_view id);
	Identifier(util::string_view id);

	Identifier(const Identifier&) = default;
	Identifier(Identifier&&) = default;

	Identifier & operator=(const Identifier&) = default;
	Identifier & operator=(Identifier&&) = default;

	~Identifier() = default;
public:
	const std::string & getId() const { return id; };
	KeyType getIdType() const { return idType; };
public:
	bool operator==(const Identifier & other) const;
public:
	static Identifier Custom(util::string_view id) { return Identifier(KeyType::Custom, id); }
	static Identifier IRDI(util::string_view id) { return Identifier(KeyType::IRDI, id); }
	static Identifier IRI(util::string_view id) { return Identifier(KeyType::IRI, id); }
};

};
