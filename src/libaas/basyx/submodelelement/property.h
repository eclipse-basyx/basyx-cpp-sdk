#pragma once

#include <basyx/base/valuetypedefs.h>

#include <basyx/langstringset.h>
#include <basyx/modeltype.h>
#include <basyx/serialization/serializable.h>
#include <basyx/submodelelement/dataelement.h>

#include <basyx/util/string_view/string_view.hpp>

#include <sstream>
#include <string>
#include <type_traits>

namespace basyx {

class property_base : public DataElement, private ModelType<ModelTypes::Property> {
public:
    property_base(util::string_view idShort)
        : DataElement(idShort) {};
    virtual ~property_base() = default;

public:
    virtual util::string_view get_value_type() const = 0;

    virtual const util::optional<Reference>& get_value_id() const = 0;
    virtual void set_value_id(const Reference& reference) = 0;

    virtual const util::optional<std::string> get_value_as_string() const = 0;
    virtual bool set_value_from_string(util::string_view value) = 0;

    template <typename DataType>
    Property<DataType>* cast() { return dynamic_cast<Property<DataType>*>(this); };
};

template <typename DataType>
class Property : public property_base,
                 private serialization::Serializable<Property<DataType>>,
                 private Referable::Copyable<Property<DataType>> {
private:
    util::optional<DataType> value;
    util::optional<Reference> valueId;

public:
    Property(util::string_view idShort)
        : property_base(idShort) {};

    template <typename U = DataType>
    Property(util::string_view idShort, U&& u)
        : property_base(idShort)
        , value(std::forward<U>(u)) {};

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
    const util::optional<Reference>& get_value_id() const override { return this->valueId; }
    void set_value_id(const Reference& reference) override { this->valueId = reference; };

    util::string_view get_value_type() const override {
       util::string_view typeStr = detail::toString(detail::data_type_def<DataType>::value_type);
       return typeStr;
    };

    const util::optional<DataType>& get_value() const { return this->value; };

    const util::optional<std::string> get_value_as_string() const override;
    bool set_value_from_string(util::string_view value) override;

    template <typename U = DataType>
    void set_value(U&& value)
    {
        this->value.emplace(std::forward<U>(value));
    };
};

class PropertyHelper {
public:
    template <typename ValueType>
    static bool SetValue(property_base& prop, ValueType value)
    {
        using data_type_t = typename detail::data_type_map<ValueType>::value_type_t;

        auto p = prop.cast<data_type_t>();
        if (p == nullptr)
            return false;

        p->set_value(value);
        return true;
    };

    template <typename ValueType>
    static std::string value_to_string(const Property<ValueType>& prop)
    {
        if (!prop.get_value())
            return {};

        return std::to_string(*prop.get_value());
    };

    template <typename ValueType>
    static bool set_value_from_string(Property<ValueType>& prop, util::string_view value)
    {
        std::istringstream sstream(value.to_string());

        ValueType val;
        sstream >> val;

        if (sstream.fail())
            return false;

        prop.set_value(val);
        return true;
    };
};

template <>
inline std::string PropertyHelper::value_to_string<std::string>(const Property<std::string>& prop)
{
    if (!prop.get_value())
        return {};

    return *prop.get_value();
};

template <>
inline bool PropertyHelper::set_value_from_string<std::string>(Property<std::string>& prop, util::string_view value)
{
    prop.set_value(value.to_string());
    return true;
};

template <typename T>
const util::optional<std::string> Property<T>::get_value_as_string() const
{
    return PropertyHelper::value_to_string<T>(*this);
};

template <typename T>
bool Property<T>::set_value_from_string(util::string_view value)
{
    return PropertyHelper::set_value_from_string<T>(*this, value);
};

}
