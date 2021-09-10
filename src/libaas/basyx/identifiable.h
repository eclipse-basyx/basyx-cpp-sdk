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
	util::optional<AdministrativeInformation> administration;
	Identifier identification;
public:
	Identifiable(util::string_view idShort, util::string_view id) : Referable(idShort), identification(id) {};
	Identifiable(util::string_view idShort, Identifier identification) : Referable(idShort), identification(std::move(identification)) {};

	Identifiable(const Identifiable&) = default;
	Identifiable(Identifiable&&) = default;

	Identifiable & operator=(const Identifiable&) = default;
	Identifiable & operator=(Identifiable&&) = default;

	~Identifiable() = default;
public:
	const util::optional<AdministrativeInformation> & getAdministration() const { return administration; };
	util::optional<AdministrativeInformation> & getAdministration() { return administration; };
	void setAdministration(AdministrativeInformation administrativeInformation) { this->administration = std::move(administrativeInformation); }

	const Identifier & getIdentification() const { return identification; };
	void setIdentification(Identifier identifier) { this->identification = std::move(identifier); };
};

};
