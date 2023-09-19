#ifndef LABELTYPE_H
#define LABELTYPE_H

#include <basyx/base/minMaxString.h>
#include <basyx/util/string_view/string_view.hpp>

namespace basyx
{

class LabelType: public base::MinMaxString {
private:
   static const unsigned int minLenght = 1;
   static const unsigned int maxLenght = 64;
public:
   LabelType(): base::MinMaxString(minLenght, maxLenght) {}
   LabelType(const LabelType&) = default;
   LabelType(const basyx::util::string_view &v):
      base::MinMaxString(minLenght, maxLenght) {
      base::MinMaxString::operator=(v.to_string());
   }
   LabelType(LabelType&&) = default;

   LabelType& operator=(const LabelType& id) noexcept;
   LabelType& operator=(const basyx::util::string_view& id) noexcept;
   LabelType& operator=(const std::string& id) noexcept;
   //LabelType& operator=(LabelType &) noexcept = default;

   std::string getLabel() const;

   ~LabelType() = default;
};
};
#endif // LABELTYPE_H
