#pragma once

#include <string>

#include <util/optional/optional.hpp>

#include <basyx/langstringset.h>

#include <basyx/key.h>

namespace basyx
{

class Identifier
{
private:
	IdentifierType idType;
	std::string id;
public:
	Identifier(IdentifierType idType, util::string_view id);

	Identifier(const Identifier&) = default;
	Identifier(Identifier&&) = default;

	Identifier & operator=(const Identifier&) = default;
	Identifier & operator=(Identifier&&) = default;

	~Identifier() = default;
public:
	const std::string & get_id() const { return id; };
	void set_id(const std::string & value) { this->id = id; };

	IdentifierType get_id_type() const { return idType; };
	void set_id_type(IdentifierType idType) { this->idType = idType; };
public:
	static Identifier Custom(util::string_view id) { return Identifier(IdentifierType::Custom, id); }
	static Identifier IRDI(util::string_view id) { return Identifier(IdentifierType::IRDI, id); }
	static Identifier IRI(util::string_view id) { return Identifier(IdentifierType::IRI, id); }
};

};
