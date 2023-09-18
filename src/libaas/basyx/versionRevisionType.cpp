#include <basyx/versionRevisionType.h>

namespace basyx {

VersionRevisionType &VersionRevisionType::operator=(const VersionRevisionType &id) noexcept {
   operator=(id.get());
   return *this;
}

VersionRevisionType &VersionRevisionType::operator=(const basyx::util::string_view& id) noexcept {
   operator=(id.to_string());
   return *this;
}

/* Funnel for all operator= of this class */
VersionRevisionType &VersionRevisionType::operator=(const std::string& id) noexcept {
   std::smatch matches;
   if (std::regex_match(id, matches, VERSIONREVISIONTYPEREGEX))
      base::MinMaxString::operator=(id);
   else
      base::MinMaxString::operator=(std::string(&DEFAULT_VERSION));
   return *this;
}

std::string VersionRevisionType::get() const {
   return static_cast<std::string>(*this);
}

};
