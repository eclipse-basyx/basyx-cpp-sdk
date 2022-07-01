#ifndef QUALIFIER_H
#define QUALIFIER_H

#pragma once

#include <basyx/base/valuetypedefs.h>

#include <basyx/constraints/constraint.h>

#include <basyx/modeltype.h>
#include <basyx/hassemantics.h>
#include <basyx/reference.h>

#include <basyx/util/optional/optional.hpp>

#include <basyx/serialization/serializable.h>

namespace basyx
{

class qualifier_base : 
	public Constraint,
	private ModelType<ModelTypes::Qualifier>
{
public:
	qualifier_base() = default;
   virtual ~qualifier_base() = default;
public:
	virtual util::string_view getValueType() const = 0;
};

class QualifierBase: public qualifier_base {
   basyx::detail::datatypes type;
public:
   QualifierBase(basyx::detail::datatypes type): type(type) {}
   ~QualifierBase() = default;

   util::string_view getValueType() const override { return basyx::detail::toString(type); }
   basyx::detail::datatypes getValueTypeEnum() { return type; }

   template <typename DataType>
   Qualifier<DataType>* cast() { return dynamic_cast<Qualifier<DataType>*>(this); };
};

template<typename ValueType>
class Qualifier : public QualifierBase {
public:
	using modeltype_base::get_model_type;
private:
   std::string qualifierType;
	util::optional<Reference> valueId;
	util::optional<ValueType> value;
public:
   Qualifier(util::string_view qualifierType) :
      QualifierBase(detail::data_type_def<ValueType>::value_type),
      qualifierType(qualifierType.to_string()) {
   }

	template<typename U = ValueType>
   Qualifier(util::string_view qualifierType, U && u) :
      QualifierBase(detail::data_type_def<ValueType>::value_type),
      qualifierType(qualifierType.to_string()),
      value(std::forward<U>(u)) {
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

   /*util::string_view getValueType() const override {
      return basyx::detail::toString(detail::data_type_def<ValueType>::value_type);
   }*/

	const util::optional<ValueType> & getValue() const { return this->value; };

	template<typename U = ValueType>
	void setValue(U && value) {
		this->value.emplace(std::forward<U>(value));
	};
};

}

#endif // QUALIFIER_H
