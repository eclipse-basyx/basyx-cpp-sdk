#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/environment.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/asset.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/submodel.h>

#include <basyx/enums/IdentifiableElements.h>

#include <basyx/constraints/qualifier.h>
#include <basyx/constraints/formula.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/entity.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class PropertyTest : public ::testing::Test {
protected:
    // Test settings

    // Test variables

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};


TEST_F(PropertyTest, PropertyType)
{
    ASSERT_EQ(Property<uint8_t> { "id" }.get_value_type(), "unsignedByte");
    ASSERT_EQ(Property<int8_t> { "id" }.get_value_type(), "byte");
    ASSERT_EQ(Property<std::string> { "id" }.get_value_type(), "string");
    ASSERT_EQ(Property<double> { "id" }.get_value_type(), "double");
    ASSERT_EQ(Property<float> { "id" }.get_value_type(), "float");
    ASSERT_EQ(Property<char> { "id" }.get_value_type(), "byte");
};

TEST_F(PropertyTest, PropertyTest1)
{
    Property<int> p1{ "int_prop" };
    p1.set_value(5);

    ASSERT_EQ(*p1.get_value(), 5);
    ASSERT_EQ(p1.get_value_type(), "int");

    Property<float> p2{ "float_prop" };
    ASSERT_EQ(p2.get_value_type(), "float");
    ASSERT_FALSE(p2.get_value());

    p2.set_value(5.0f);
    ASSERT_TRUE(p2.get_value());
    ASSERT_EQ(*p2.get_value(), 5.0f);
};

TEST_F(PropertyTest, PropertyTest2)
{
    Property<int> p1{ "int_prop", 5 };
    ASSERT_EQ(*p1.get_value(), 5);
    ASSERT_EQ(p1.get_value_type(), "int");

    Property<float> p2{ "float_prop", 5.0f };
    ASSERT_TRUE(p2.get_value());
    ASSERT_EQ(*p2.get_value(), 5.0f);

    Property<std::string> p3{ "string_prop", "test" };
    ASSERT_TRUE(p3.get_value());
    ASSERT_EQ(*p3.get_value(), "test");
};


TEST_F(PropertyTest, IntPropertyCopy)
{
    Property<int> i{ "i", 1 };
    auto i2 = i;

    i2.~Property();
    i.~Property();
}

TEST_F(PropertyTest, StringPropertyCopy)
{
    Property<std::string> s{ "string_prop", "test" };
    auto s2 = s;

    s.set_value("test");

    s.~Property();
    s2.~Property();
}

TEST_F(PropertyTest, PropertyCast)
{
    Property<int> i{ "i", 1 };
    property_base* base_prop = &i;

    auto casted_ok = base_prop->cast<int>();
    ASSERT_NE(casted_ok, nullptr);
    ASSERT_EQ(casted_ok->get_value(), i.get_value());

    auto casted_bad = base_prop->cast<std::string>();
    ASSERT_EQ(casted_bad, nullptr);
}

TEST_F(PropertyTest, SetValueHelper)
{
    // Integer
    Property<int> i{ "i", 1 };
    PropertyHelper::SetValue(i, 5);
    ASSERT_EQ(i.get_value(), 5);

    // Float
    Property<float> f{ "f", 1.0f };
    PropertyHelper::SetValue(f, 0.0f);
    ASSERT_EQ(f.get_value(), 0.0f);

    // String
    Property<std::string> s{ "str", "test" };
    PropertyHelper::SetValue(s, "basyx");
    ASSERT_EQ(s.get_value(), "basyx");
}

TEST_F(PropertyTest, GetStringValue)
{
    // Integer
    Property<int> i{ "i", 1 };
    ASSERT_EQ(i.get_value_as_string(), "1");

    // Float
    Property<float> f{ "f", 1.0f };
    ASSERT_EQ(f.get_value_as_string(), std::to_string(1.0f));

    // String
    Property<std::string> s{ "str", "test" };
    ASSERT_EQ(s.get_value_as_string(), "test");
};


TEST_F(PropertyTest, SetStringValue)
{
    // Integer
    Property<int> i{ "i", 1 };
    i.set_value_from_string("2");
    ASSERT_EQ(i.get_value(), 2);

    // Integer - Error
    Property<int> i2{ "i", 1 };
    ASSERT_FALSE(i2.set_value_from_string("test"));
    ASSERT_EQ(i2.get_value(), 1);

    // Float
    Property<float> f{ "f", 1.0f };
    f.set_value_from_string("2.0000");
    ASSERT_EQ((int)*f.get_value(), 2);

    // String
    Property<std::string> s{ "str", "test" };
    s.set_value_from_string("basyx");
    ASSERT_EQ(s.get_value(), "basyx");
}