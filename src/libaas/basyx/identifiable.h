#pragma once

#include <basyx/administrative_information.h>
#include <basyx/identifier.h>
#include <basyx/referable.h>

#include <basyx/util/optional/optional.hpp>

#include <string>

namespace basyx
{

class Identifiable : public Referable
{
private:
	util::optional<AdministrativeInformation> administration;
   Identifier id;
public:
   Identifiable(util::string_view idShort, util::string_view id) : Referable(idShort), id(id) {};
   Identifiable(util::string_view idShort, Identifier id) : Referable(idShort), id(std::move(id)) {};

	Identifiable(const Identifiable&) = default;
	Identifiable(Identifiable&&) = default;

	Identifiable & operator=(const Identifiable&) = default;
	Identifiable & operator=(Identifiable&&) = default;

	~Identifiable() = default;
public:
	const util::optional<AdministrativeInformation> & getAdministration() const { return administration; };
	util::optional<AdministrativeInformation> & getAdministration() { return administration; };
	void setAdministration(AdministrativeInformation administrativeInformation) { this->administration = std::move(administrativeInformation); }

   const Identifier & getId() const { return id; };
   void setId(Identifier id) { this->id = std::move(id); };
};

};
