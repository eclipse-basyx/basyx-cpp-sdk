#include <gtest/gtest.h>

#include <basyx/langstringset.h>
#include <basyx/key.h>
#include <basyx/reference.h>

#include <basyx/serialization/json/serializer.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class JsonTest : public ::testing::Test
{
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


TEST_F(JsonTest, Key)
{
	Key key{ "type", "value", basyx::KeyType::IdentifierType::Custom };

	auto json = basyx::serialization::json::serialize(key);

	int j = 2;
};

TEST_F(JsonTest, Reference)
{
	Key key1{ "type1", "value1", basyx::KeyType::IdentifierType::Custom };
	Key key2{ "type2", "value2", basyx::KeyType::IdentifierType::Custom };

	Reference reference{ key1, key2 };

	auto json = basyx::serialization::json::serialize(reference);

	int j = 2;
};


TEST_F(JsonTest, LangStrings)
{
	langstringset_t ls{
		{"en", "example"},
		{"de", "beispiel"} 
	};

	auto json = basyx::serialization::json::serialize(ls);

	int j = 2;
};

TEST_F(JsonTest, MultiLanguageProperty)
{
	MultiLanguageProperty mlp{ "mlp", {
		{"en", "test"},
		{"de", "beispiel"}
		} };

	mlp.set_description({
		{"en", "test"},
		{"de", "beispiel"}
	});

	auto json = basyx::serialization::json::serialize(mlp);

	ASSERT_EQ(json["value"].is_array(), true);
	ASSERT_EQ(json["value"].size(), 2);

	ASSERT_EQ(json["description"].size(), 2);
	ASSERT_EQ(json["description"].size(), 2);
};

TEST_F(JsonTest, Property)
{
	Property<int> p_int{ "int_prop" };
	p_int.set_value(5);

	Property<float> p_float{ "float_prop" };
	p_float.set_value(2.0f);

	Property<std::string> p_string{ "string_prop" };
	p_string.set_value("test");

	auto json_int = basyx::serialization::json::serialize(p_int);
	auto json_float = basyx::serialization::json::serialize(p_float);
	auto json_string = basyx::serialization::json::serialize(p_string);

	int j = 2;
};

TEST_F(JsonTest, SubmodelElement)
{
	std::unique_ptr<SubmodelElement> mlp = std::make_unique<MultiLanguageProperty>( "mlp" );

	MultiLanguageProperty * mlpp =  static_cast<MultiLanguageProperty*>(mlp.get());

	mlpp->set_value({
		{"en", "test"},
		{"de", "beispiel"}
	});

	mlpp->set_description({
		{"en", "test"},
		{"de", "beispiel"}
	});

	auto model = mlp->get_model_type();
	auto json = basyx::serialization::json::serialize(*mlp);

	int j = 2;
};



TEST_F(JsonTest, SubmodelElementCollection)
{
	SubmodelElementCollection col1{ "col1" };
	{
		SubmodelElementCollection col2{ "col2" };

		Property<int> i{ "int_prop", 2 };
		Property<float> f{ "float_prop", 5.0f };

		Property<std::string> s{ "string_prop", "test" };
		auto s2 = s;

		s2.~Property();


		col1.add(Property<int>("int_prop", 2));
		col1.add(f);
		//col2.add(s);
		//col1.add(std::move(col2));
	};

	//auto json = basyx::serialization::json::serialize(col1);

	int j = 2;
};

