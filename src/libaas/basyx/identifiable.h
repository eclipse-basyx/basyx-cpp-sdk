#pragma once

#include <basyx/administrative_information.h>
#include <basyx/identifier.h>
#include <basyx/referable.h>

#include <util/optional/optional.hpp>

#include <string>

namespace basyx
{

class Identifiable : public Referable
{
private:
	util::optional<AdministrativeInformation> administrativeInformation;
	Identifier identifier;
public:
	Identifiable(util::string_view idShort, IdentifierType idType, util::string_view id) : Referable(idShort), identifier(idType, id) {};
	Identifiable(util::string_view idShort, Identifier identifier) : Referable(idShort), identifier(std::move(identifier)) {};

	Identifiable(const Identifiable&) = default;
	Identifiable(Identifiable&&) = default;

	Identifiable & operator=(const Identifiable&) = default;
	Identifiable & operator=(Identifiable&&) = default;

	~Identifiable() = default;
public:
	const util::optional<AdministrativeInformation> & get_administrative_information() const { return administrativeInformation; };
	util::optional<AdministrativeInformation> & get_administrative_information() { return administrativeInformation; };
	void get_administrative_information(AdministrativeInformation administrativeInformation) { this->administrativeInformation = std::move(administrativeInformation); }

	const Identifier & get_identifier() const { return identifier; };
	void set_identifier(Identifier identifier) { this->identifier = std::move(identifier); };
};

};
