#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>
#include <basyx/util/string_view/string_view.hpp>

namespace basyx
{

class Identifier: public std::string {
public:
   Identifier() = default;
   Identifier(const Identifier&) = default;
   Identifier(const basyx::util::string_view &v) {
      std::string::operator=(v.to_string());
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
