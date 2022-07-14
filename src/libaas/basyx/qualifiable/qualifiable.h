#ifndef QUALIFIABLE_H
#define QUALIFIABLE_H

#pragma once

#include <basyx/qualifiable/qualifierbase.h>

#include <memory>
#include <vector>

namespace basyx {

using namespace basyx;

class Qualifiable {
public:
   using qualifierPtr_t = std::shared_ptr<QualifierBase>;
   using qualifierList_t = std::vector<qualifierPtr_t>;
private:
	qualifierList_t qualifierList;
public:
	Qualifiable() = default;

	Qualifiable(const Qualifiable&) = default;
	Qualifiable(Qualifiable&&) = default;

	Qualifiable & operator=(const Qualifiable&) = default;
	Qualifiable & operator=(Qualifiable&&) = default;

	~Qualifiable() = default;
public:
   const qualifierList_t & getQualifiers() const { return this->qualifierList; };
   qualifierList_t & getQualifiers() { return this->qualifierList; };

   template<typename T>
   Qualifier<T> * addQualifier(Qualifier<T> &q) {
      auto qu = std::make_unique<Qualifier<T>>(q);
      qualifierList.emplace_back(std::move(qu));
      return qualifierList.back().get()->cast<T>();
   }
};

};

#endif // QUALIFIABLE_H
