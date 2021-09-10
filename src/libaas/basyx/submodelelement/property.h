#pragma once

#include <basyx/base/valuetypedefs.h>

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>
#include <basyx/serialization/serializable.h>

#include <util/string_view/string_view.hpp>

#include <string>
#include <type_traits>

namespace basyx
{

class property_base : public DataElement, private ModelType<ModelTypes::Property>
{
public:
	property_base(util::string_view idShort) : DataElement(idShort) {};
	virtual ~property_base() = default;
public:
	virtual util::string_view get_value_type() const = 0;

	virtual const util::optional<Reference> & get_value_id() const = 0;
	virtual void set_value_id(const Reference & reference) = 0;

	template<typename DataType>
	Property<DataType> * cast() { return dynamic_cast<Property<DataType>>(this); };
};

template<typename DataType>
class Property : 
	public property_base, 
	private serialization::Serializable<Property<DataType>>
{
private:
	util::optional<DataType> value;
	util::optional<Reference> valueId;
public:
	Property(util::string_view idShort) : property_base(idShort) {};

	template<typename U=DataType>
	Property(util::string_view idShort, U && u) : property_base(idShort), value(std::forward<U>(u)) {};

	//// Enable string_view constructor for DataType == std::string
	//template <typename U = DataType, std::enable_if_t<std::is_same<DataType, std::string>::value, bool> = true>
	//Property(util::string_view idShort, util::string_view value)
	//	: DataElement(idShort), value(value.to_string())
	//{
	//};

	Property(const Property&) = default;
	Property& operator=(const Property&) = default;

	Property(Property&&) = default;
	Property& operator=(Property&&) = default;

	~Property() = default;
public:
	const util::optional<Reference> & get_value_id() const override { return this->valueId; }
	void set_value_id(const Reference & reference) override { this->valueId = reference; };

	util::string_view get_value_type() const override { return detail::data_type_def<DataType>::value_type; };

	const util::optional<DataType> & get_value() const { return this->value; };

	template<typename U = DataType>
	void set_value(U && value) {
		this->value.emplace(std::forward<U>(value));
	};
};

}
