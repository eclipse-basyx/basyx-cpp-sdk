#pragma once

#include <basyx/base/valuetypedefs.h>

#include <basyx/constraints/constraint.h>

#include <basyx/modeltype.h>
#include <basyx/hassemantics.h>
#include <basyx/reference.h>

#include <util/optional/optional.hpp>

namespace basyx
{

class qualifier_base : 
	public Constraint,
	public HasSemantics,
	private ModelType<ModelTypes::Qualifier>
{
public:
	qualifier_base() = default;
	~qualifier_base() = 0 {};
public:
	virtual util::string_view getValueType() const = 0;
};

template<typename ValueType>
class Qualifier : public qualifier_base
{
public:
	using modeltype_base::get_model_type;
private:
	std::string qualifierType;
	util::optional<Reference> valueId;
	util::optional<ValueType> value;
public:
	Qualifier(util::string_view qualifierType) : qualifierType(qualifierType.to_string()) {};

	template<typename U = ValueType>
	Qualifier(util::string_view qualifierType, U && u) : qualifierType(qualifierType.to_string()), value(std::forward<U>(u)) {};

	Qualifier(const Qualifier&) = default;
	Qualifier& operator=(const Qualifier&) = default;

	Qualifier(Qualifier&&) = default;
	Qualifier& operator=(Qualifier&&) = default;

	~Qualifier() = default;
public:
	const std::string & getQualifierType() const { return qualifierType; };
	void setQualifierType(util::string_view qualifierType) { this->qualifierType = qualifierType.to_string(); };

	util::string_view getValueType() const override { return detail::data_type_def<ValueType>::value_type; };

	const util::optional<ValueType> & getValue() const { return this->value; };

	template<typename U = DataType>
	void setValue(U && value) {
		this->value.emplace(std::forward<U>(value));
	};
};

}