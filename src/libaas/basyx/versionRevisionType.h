#ifndef VERSIONREVISIONTYPE_H
#define VERSIONREVISIONTYPE_H

#include <regex>

#include <basyx/base/minMaxString.h>
#include <basyx/util/string_view/string_view.hpp>

namespace basyx
{

static const char DEFAULT_VERSION = '0';
static std::regex VERSIONREVISIONTYPEREGEX("^([0-9]|[1-9][0-9]*)$");

class VersionRevisionType: public base::MinMaxString {
private:
   static const unsigned int minLenght = 1;
   static const unsigned int maxLenght = 4;
public:
   VersionRevisionType(): base::MinMaxString(minLenght, maxLenght) {}
   VersionRevisionType(const VersionRevisionType&) = default;
   VersionRevisionType(const basyx::util::string_view &v):
      base::MinMaxString(minLenght, maxLenght) {
      operator=(v.to_string());
   }
   VersionRevisionType(VersionRevisionType&&) = default;

   VersionRevisionType& operator=(const VersionRevisionType& id) noexcept;
   VersionRevisionType& operator=(const basyx::util::string_view& id) noexcept;
   VersionRevisionType& operator=(const std::string& id) noexcept;
   //VersionRevisionType& operator=(VersionRevisionType &) noexcept = default;

   std::string get() const;

   ~VersionRevisionType() = default;
};
};

#endif // VERSIONREVISIONTYPE_H
