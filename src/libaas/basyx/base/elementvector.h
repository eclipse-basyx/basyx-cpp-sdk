#ifndef ELEMENTVECTOR_H
#define ELEMENTVECTOR_H

#include <vector>

template<typename ElementType>
class ElementVector: public std::vector<ElementType>
{
public:
public:
   using element_t = ElementType;
   ElementVector() {};
   template<typename element_t>
   void add(element_t element) { this->emplace_back(std::move(element));
   }
};

#endif // ELEMENTVECTOR_H
