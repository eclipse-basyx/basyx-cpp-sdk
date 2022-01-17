#pragma once

#include <string>

#include <basyx/util/optional/optional.hpp>

#include <basyx/langstringset.h>

#include <basyx/key.h>

namespace basyx
{

class AdministrativeInformation
{
private:
	util::optional<std::string> version;
	util::optional<std::string> revision;
public:
	AdministrativeInformation() = default;
	AdministrativeInformation(util::string_view version);
	AdministrativeInformation(util::string_view version, util::string_view revision);

	AdministrativeInformation(const AdministrativeInformation&) = default;
	AdministrativeInformation(AdministrativeInformation&&) = default;

	AdministrativeInformation & operator=(const AdministrativeInformation&) = default;
	AdministrativeInformation & operator=(AdministrativeInformation&&) = default;

	~AdministrativeInformation() = default;
public:
	const util::optional<std::string> & get_version() const { return version; };
	void set_version(util::string_view version) { this->version = version.to_string(); };

	const util::optional<std::string> & get_revision() const { return revision; };
	void set_revision(util::string_view revision) { this->revision = revision.to_string(); };
};

};
