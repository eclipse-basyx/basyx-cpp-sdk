#include "administrative_information.h"

namespace basyx
{

AdministrativeInformation::AdministrativeInformation(util::string_view version)
 : version(version.to_string()) {};

AdministrativeInformation::AdministrativeInformation(util::string_view version, util::string_view revision)
 : version(version.to_string()), revision(revision.to_string()) {}

};