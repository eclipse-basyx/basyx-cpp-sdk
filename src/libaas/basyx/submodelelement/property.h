#pragma once

#include <basyx/submodelelement/dataelement.h>
#include <basyx/langstringset.h>
#include <basyx/modeltype.h>
//#include <basyx/serialization/serializable.h>

#include <util/string_view/string_view.hpp>

#include <string>
#include <type_traits>

namespace basyx
{

template<typename DataType>
class Property : 
	public DataElement, 
	private ModelType<ModelTypes::Property>
	//private serialization::Serializable<Property<DataType>>
{
private:
	util::optional<DataType> value;
	util::optional<Reference> valueId;
public:
	Property(util::string_view idShort) : DataElement(idShort) {
	};

	template<typename U=DataType>
	Property(util::string_view idShort, U && u) : DataElement(idShort), value(std::forward<U>(u)) {};

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
	const util::optional<Reference> & get_value_id() const { return this->valueId; }
	void set_value_id(const Reference & reference) { this->valueId = reference; };

	const util::optional<DataType> & get_value() const { return this->value; };
	util::optional<DataType> & get_value() { return this->value; };

	util::string_view get_value_type() const { return detail::data_type_def<DataType>::value_type; };

	template<typename U = DataType>
	void set_value(U && value) {
		this->value.emplace(std::forward<U>(value));
	};
};

namespace detail {

template<typename T> struct data_type_def {};
template<> struct data_type_def<int8_t> { static constexpr char value_type[] = "byte"; };
template<> struct data_type_def<char> { static constexpr char value_type[] = "byte"; };
template<> struct data_type_def<uint8_t> { static constexpr char value_type[] = "unsignedByte"; };
template<> struct data_type_def<int16_t> { static constexpr char value_type[] = "short"; };
template<> struct data_type_def<uint16_t> { static constexpr char value_type[] = "unsignedShort"; };
template<> struct data_type_def<int32_t> { static constexpr char value_type[] = "int"; };
template<> struct data_type_def<uint32_t> { static constexpr char value_type[] = "unsignedInt"; };
template<> struct data_type_def<int64_t> { static constexpr char value_type[] = "long"; };
template<> struct data_type_def<uint64_t> { static constexpr char value_type[] = "unsignedLong"; };
template<> struct data_type_def<std::string> { static constexpr char value_type[] = "string"; };
template<> struct data_type_def<float> { static constexpr char value_type[] = "float"; };
template<> struct data_type_def<double> { static constexpr char value_type[] = "double"; };
template<> struct data_type_def<bool> { static constexpr char value_type[] = "boolean"; };

};

}