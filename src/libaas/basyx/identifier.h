#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <basyx/base/minMaxString.h>
#include <basyx/util/string_view/string_view.hpp>

namespace basyx
{

class Identifier: public base::MinMaxString {
   static const unsigned int minLenght = 1;
   static const unsigned int maxLenght = 2000;
public:
   Identifier() : base::MinMaxString(minLenght, maxLenght) {}
   Identifier(const Identifier&) = default;
   Identifier(const basyx::util::string_view &v):
      base::MinMaxString(minLenght, maxLenght) {
      base::MinMaxString::operator=(v.to_string());
   }
   Identifier(Identifier&&) = default;

   Identifier& operator=(const Identifier& id) noexcept;
   Identifier& operator=(const basyx::util::string_view& id) noexcept;
   Identifier& operator=(const std::string& id) noexcept;
   //Identifier& operator=(Identifier &) noexcept = default;

   std::string getId() const;

   ~Identifier() = default;
};
};
#endif /* IDENTIFIER_H */
