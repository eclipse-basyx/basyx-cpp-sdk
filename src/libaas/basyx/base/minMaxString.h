#ifndef MINMAXSTRING_H
#define MINMAXSTRING_H

#include <string>
#include <basyx/util/string_view/string_view.hpp>

namespace basyx::base
{

static const char STRING_PADDING = ' ';

class MinMaxString: protected std::string {
protected:
   unsigned int minLength;
   unsigned int maxLength;
   void replace(const std::string &str);
   void fillToMin() {
      while (std::string::length() < minLength)
         std::string::operator+=(STRING_PADDING);
   }
   void truncateToMax() {
      if (this->length() > maxLength) {
         this->resize(maxLength);
      }
   }
public:
   MinMaxString(unsigned int min, unsigned int max): minLength(min), maxLength(max) {
      fillToMin();
   }
   MinMaxString(const MinMaxString&) = default;
   MinMaxString(const basyx::util::string_view &v) {
      operator=(v.to_string());
   }
   MinMaxString(MinMaxString&&) = default;

   MinMaxString& operator=(const MinMaxString& str) noexcept;
   MinMaxString& operator=(const basyx::util::string_view& str) noexcept;
   MinMaxString& operator=(const std::string& str) noexcept;
   //MinMaxString& operator=(MinMaxString &) noexcept = default;

   bool operator==(const std::string& rhs) {
      if (std::strcmp(this->data(), rhs.data()) == 0)
         return true;
      return false;
   }

   bool operator!=(const std::string& rhs) {
      return !operator==(rhs);
   }

   void resize(size_type __n, char c) {
      if (__n < minLength) {
         std::string::resize(minLength, c);
         return;
      }
      if (__n > maxLength) {
         std::string::resize(maxLength, c);
         return;
      }
      std::string::resize(__n, c);
   }

   void resize(size_type __n) {
      resize(__n, STRING_PADDING);
   }

   size_type length() { return std::string::length(); }

   /* We want to copy here, as manipulation of the base string is just not
    * intended
    */
   std::string str() const { return *this; }

   const std::string& assign(const basic_string& __str) { return operator=(__str); }


   ~MinMaxString() = default;
};
};
#endif // MINMAXSTRING_H
