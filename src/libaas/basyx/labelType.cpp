#include <basyx/labelType.h>

namespace basyx {

LabelType &LabelType::operator=(const LabelType &id) noexcept {
   base::MinMaxString::operator=(id);
   return *this;
}

LabelType &LabelType::operator=(const basyx::util::string_view& id) noexcept {
   base::MinMaxString::operator=(id.to_string());
   return *this;
}

LabelType &LabelType::operator=(const std::string& id) noexcept {
   base::MinMaxString::operator=(id);
   return *this;
}

std::string LabelType::getLabel() const {
   return static_cast<std::string>(*this);
}

};
