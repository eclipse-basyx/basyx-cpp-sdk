
#include <basyx/base/minMaxString.h>

namespace basyx::base {

void MinMaxString::replace(const std::string &str) {
   std::string::operator=(str);
   fillToMin();
   truncateToMax();
   // Throw warning?
}

MinMaxString &MinMaxString::operator=(const MinMaxString &str) noexcept {
   replace(str);
   return *this;
}

MinMaxString &MinMaxString::operator=(const basyx::util::string_view& str) noexcept {
   replace(str.to_string());
   return *this;
}

MinMaxString &MinMaxString::operator=(const std::string& str) noexcept {
   replace(str);
   return *this;
}
};
