#ifndef ELEMENTVECTOR_H
#define ELEMENTVECTOR_H

#include <initializer_list>
#include <vector>

template<typename ElementType>
class ElementVector: public std::vector<ElementType>
{
public:
   using element_t = ElementType;
   ElementVector() = default;
   ElementVector(std::initializer_list<element_t> list) {
      auto iter = list.begin();
      while(iter != list.end()) {
         this->emplace_back(*iter);
         iter++;
      }
   }

   void add(element_t element) { this->emplace_back(std::move(element)); }
};

#endif // ELEMENTVECTOR_H
