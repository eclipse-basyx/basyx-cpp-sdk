
#include <basyx/identifier.h>

namespace basyx {

Identifier &Identifier::operator=(const Identifier &id) noexcept {
   base::MinMaxString::operator=(id);
   return *this;
}

Identifier &Identifier::operator=(const basyx::util::string_view& id) noexcept {
   base::MinMaxString::operator=(id.to_string());
   return *this;
}

Identifier &Identifier::operator=(const std::string& id) noexcept {
   base::MinMaxString::operator=(id);
   return *this;
}

std::string Identifier::getId() const {
   return str();
}
};
