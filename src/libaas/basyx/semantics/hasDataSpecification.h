#ifndef HASDATASPECIFICATION_H
#define HASDATASPECIFICATION_H

#include <basyx/reference.h>

#include <basyx/base/elementvector.h>

#include <basyx/util/optional/optional.hpp>

namespace basyx
{

class HasDataSpecification
{
private:
   ElementVector<Reference> dataSpecification;
public:
   HasDataSpecification() = default;

   HasDataSpecification(const HasDataSpecification&) = default;
   HasDataSpecification(HasDataSpecification&&) = default;

   HasDataSpecification & operator=(const HasDataSpecification&) noexcept = default;
   HasDataSpecification & operator=(HasDataSpecification&&) noexcept = default;

   ~HasDataSpecification() = default;
public:
   const ElementVector<Reference> & getDataSpecification() const {
      return this->dataSpecification;
   };
   ElementVector<Reference> & getDataSpecification() {
      return this->dataSpecification;
   };

   void addDataSpecification(Reference dataSpecification) {
      this->dataSpecification.add(dataSpecification);
   };
   void addDataSpecification(util::string_view dataSpecification) {
      this->dataSpecification.add(dataSpecification);
   };

   void setDataSpecication(ElementVector<Reference> & dataSpecification) {
      this->dataSpecification = std::move(dataSpecification);
   }

};

};

#endif /* HASDATASPECIFICATION_H */
