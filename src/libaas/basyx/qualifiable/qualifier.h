#ifndef QUALIFIER_H
#define QUALIFIER_H

#pragma once

#include <basyx/base/valuetypedefs.h>

#include <basyx/enums/QualifierKind.h>

#include <basyx/modeltype.h>
#include <basyx/hassemantics.h>
#include <basyx/reference.h>

#include <basyx/util/optional/optional.hpp>

#include <basyx/qualifiable/qualifierbase.h>
#include <basyx/qualifiable/qualifiable.h>


namespace basyx
{

template<typename ValueType>
class Qualifier : public QualifierBase, public Qualifiable {
public:
	using modeltype_base::get_model_type;
private:
   QualifierKind qualifierKind;
   std::string qualifierType;
	util::optional<Reference> valueId;
	util::optional<ValueType> value;
public:
   Qualifier(util::string_view qualifierType) :
      QualifierBase(detail::data_type_def<ValueType>::value_type),
      qualifierType(qualifierType.to_string()),
      qualifierKind(QualifierKind::ConceptQualifier) {
   }

	template<typename U = ValueType>
   Qualifier(util::string_view qualifierType, U && u) :
      QualifierBase(detail::data_type_def<ValueType>::value_type),
      qualifierType(qualifierType.to_string()),
      value(std::forward<U>(u)),
      qualifierKind(QualifierKind::ConceptQualifier) {
   }

   Qualifier(const Qualifier&) = default;
	Qualifier& operator=(const Qualifier&) = default;

	Qualifier(Qualifier&&) = default;
	Qualifier& operator=(Qualifier&&) = default;

   ~Qualifier() = default;
public:
   std::string & getQualifierType() { return qualifierType; };
   void setQualifierType(util::string_view qualifierType) {
      this->qualifierType = qualifierType.to_string();
   };

   void setQualifierKind(std::string qualifierKind) {
      this->qualifierKind = QualifierKind_::from_string(qualifierKind);
   }
   void setQualifierKindEnum(QualifierKind k) { qualifierKind = k; }

   const std::string getQualifierKind() const {
      return QualifierKind_::to_string(this->qualifierKind);
   }
   const QualifierKind getQualifierKindEnum() { return qualifierKind; }

	const util::optional<ValueType> & getValue() const { return this->value; };

	template<typename U = ValueType>
	void setValue(U && value) {
		this->value.emplace(std::forward<U>(value));
	};
};

}

#endif // QUALIFIER_H
