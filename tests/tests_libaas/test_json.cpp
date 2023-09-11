#include <gtest/gtest.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/langstringset.h>
#include <basyx/key.h>
#include <basyx/reference.h>
#include <basyx/submodel.h>

#include <basyx/assetadministrationshell.h>

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
	Key key{ KeyElements::Asset, "value", basyx::KeyType::Custom };

	auto json = basyx::serialization::json::serialize(key);
};

TEST_F(JsonTest, Reference)
{
	Key key1{ KeyElements::Asset, "value1", basyx::KeyType::Custom };
	Key key2{ KeyElements::Asset, "value2", basyx::KeyType::Custom };

	Reference reference{ key1, key2 };

	auto json = basyx::serialization::json::serialize(reference);
};


TEST_F(JsonTest, LangStrings)
{
	langstringset_t ls{
		{"en", "example"},
		{"de", "beispiel"} 
	};

	auto json = basyx::serialization::json::serialize(ls);
};

TEST_F(JsonTest, MultiLanguageProperty)
{
	MultiLanguageProperty mlp{ "mlp", {
		{"en", "test"},
		{"de", "beispiel"}
		} };

	mlp.setDescription({
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
};

TEST_F(JsonTest, SubmodelElement)
{
	std::unique_ptr<SubmodelElement> mlp = std::make_unique<MultiLanguageProperty>( "mlp" );

	MultiLanguageProperty * mlpp =  static_cast<MultiLanguageProperty*>(mlp.get());

	mlpp->set_value({
		{"en", "test"},
		{"de", "beispiel"}
	});

	mlpp->setDescription({
		{"en", "test"},
		{"de", "beispiel"}
	});

	auto model = mlp->get_model_type();
	auto json = basyx::serialization::json::serialize(*mlp);
};

TEST_F(JsonTest, SubmodelElementProperty)
{
	std::unique_ptr<SubmodelElement> prop = std::make_unique<Property<int>>("prop", 5);

	auto json = basyx::serialization::json::serialize(*prop);
	
	ASSERT_EQ(json["idShort"], "prop");
	ASSERT_EQ(json["value"], 5);
	ASSERT_EQ(json["modelType"]["name"], "Property");
	ASSERT_EQ(json["valueType"], "int");
};

TEST_F(JsonTest, SubmodelElementCollection)
{
	SubmodelElementCollection col1{ "col1" };
	{
		col1.setCategory("test");

		SubmodelElementCollection col2{ "col2" };

		Property<int> i{ "int_prop", 2 };
		Property<float> f{ "float_prop", 5.0f };
		Property<std::string> s{ "string_prop", "test" };
		MultiLanguageProperty mlp{ "mlp", {
			{"en", "test"},
			{"de", "beispiel"}
			} };

		col1.getSubmodelElements().add(Property<int>("int_prop", 2));
		col1.getSubmodelElements().add(f);
		col2.getSubmodelElements().add(mlp);
		col2.getSubmodelElements().add(s);
		col1.getSubmodelElements().add(std::move(col2));
	};

	auto json = basyx::serialization::json::serialize(col1);

	ASSERT_EQ(json["value"].size(), 3);
	ASSERT_EQ(json["modelType"]["name"], "SubmodelElementCollection" );
	ASSERT_EQ(json["category"], "test");

	bool found_int_prop = false;
	bool found_float_prop = false;
	bool found_collection_prop = false;

	for (const auto & entry : json["value"]) {
		if (entry["idShort"] == "int_prop") {
			found_int_prop = true;
			ASSERT_EQ(entry["value"], 2);
		};
		
		if (entry["idShort"] == "float_prop") {
			found_float_prop = true;
			ASSERT_EQ(entry["value"], 5.0f);
		};

		if (entry["idShort"] == "col2") {
			found_collection_prop = true;
			ASSERT_EQ(entry["value"].size(), 2);
		};
	}

	ASSERT_TRUE(found_int_prop);
	ASSERT_TRUE(found_float_prop);
	ASSERT_TRUE(found_collection_prop);
};

TEST_F(JsonTest, Submodel)
{
	Submodel sm("sm", "test/sm_1");

	sm.getSubmodelElements().add(Property<int>("p1", 2));
	sm.getSubmodelElements().add(Property<int>("p2", 3));

	auto json = basyx::serialization::json::serialize(sm);
};


TEST_F(JsonTest, AssetInfTest)
{
   Identifier id("test");

	AssetInformation assetInf{ AssetKind::Instance };
   assetInf.setGlobalAssetId(id);

	auto assetInf_j = basyx::serialization::json::serialize(assetInf);
};
