#include <gtest/gtest.h>

#include <basyx/serialization/json/deserializer.h>

#include <basyx/submodel.h>

using namespace basyx;

using json_t = nlohmann::json;


class JsonDeserializerTest : public ::testing::Test
{
protected:
	// Test data

	// Key #1
	const json_t json_key_1 = json_t::parse(R"(
		{
			"type": "Submodel",
			"idType": "IRDI",
			"value": "string",
			"local": true
		}
	)");

	// Key #2
	const json_t json_key_2 = json_t::parse(R"(
        {
        "type": "Asset",
        "idType": "Custom",
        "value": "string",
        "local": true
        }
	)");

	// Reference
	const json_t json_reference = { 
		{"keys", { 
				json_key_1, 
				json_key_2 
			} 
		} 
	};

	// LangstringSet
	const json_t json_langstring_set = json_t::parse(R"(
		[
		  {
			"language": "EN",
			"text": "example"
		  },
		  {
			"language": "DE",
			"text": "beispiel"
		  }
		]
	)");

	// Int-Property 
	const json_t json_prop_int = json_t::parse(R"(
	{
		"idShort": "MaxRotationSpeed",
		"category": "PARAMETER",
		"semanticId": {
			"keys": [
				{
					"type": "ConceptDescription",
					"local": true,
					"value": "0173-1#02-BAA120#008",
					"idType": "IRDI"
				}
			]
		},
		"value": "5000",
		"valueType": "integer",
		"modelType": { "name": "Property" },
		"kind": "Instance"
	}
    )");

	// Multi language property
	const json_t json_multilang_prop = json_t{
		{"idShort", "MLP" },
		{"category", "test"},
		{"modelType", { {"name" , "MultiLanguageProperty"} } },
		{ "value" , json_langstring_set },
	};
	
	// SubmodelElementCollection
	const json_t json_submodel_element_collection = json_t{
		{"idShort", "Collection" },
		{"kind", "Instance"},
		{"modelType", { {"name" , "SubmodelElementCollection"} } },
		{ "value" , {
				json_prop_int,
				json_multilang_prop,
			} 
		},
	};

	// Submodel
	const json_t json_submodel = json_t{
		{ "idShort", "sm_1" },
		{ "identification", {
			{"id", "submodel" },
			{ "idType", "Custom"}
		}},
		{"kind", "Instance"},
		{"modelType", { {"name" , "Submodel"} } },
		{ "submodelElements" , {
				json_submodel_element_collection,
				json_multilang_prop,
			}
		}
	};

	// AAS
	const json_t json_aas = json_t{
		{ "idShort", "aas_1" },
		{ "identification", {
			{"id", "asset_admin_shell_1" },
			{ "idType", "Custom"}
		}},
		{"kind", "Instance"},
		{"modelType", { {"name" , "AssetAdministrationShell"} } },
		{ "submodels" , json_t::array({json_submodel}) }
	};

	// Test variables

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{

	}
};


TEST_F(JsonDeserializerTest, Key)
{
	auto key = basyx::serialization::json::deserialize_key(json_key_1);
	ASSERT_EQ(key.get_type(), KeyElements::Submodel);
	ASSERT_EQ(key.get_id_type(), KeyType::IRDI);
	ASSERT_EQ(key.get_value(), "string");
};

TEST_F(JsonDeserializerTest, Reference)
{
	auto reference = basyx::serialization::json::deserialize_reference(json_reference);

	ASSERT_EQ(reference.size(), 2);
	ASSERT_EQ(reference.get_key(0).get_type(), KeyElements::Submodel);
	ASSERT_EQ(reference.get_key(1).get_type(), KeyElements::Asset);
};

TEST_F(JsonDeserializerTest, LangStrings)
{
	auto ls = basyx::serialization::json::deserialize_langstrings(json_langstring_set);

	ASSERT_EQ(ls.size(), 2);
	ASSERT_TRUE(ls.contains("EN"));
	ASSERT_EQ(*ls.get("EN"), "example");
	ASSERT_TRUE(ls.contains("DE"));
	ASSERT_EQ(*ls.get("DE"), "beispiel");
};

TEST_F(JsonDeserializerTest, MultiLanguageProperty)
{
	auto mlp = basyx::serialization::json::deserialize_multilang_prop(json_multilang_prop);

	ASSERT_EQ(mlp.getIdShort(), "MLP");
	ASSERT_EQ(mlp.getCategory(), "test");
	ASSERT_EQ(mlp.get_value().size(), 2);
};

TEST_F(JsonDeserializerTest, IntProperty)
{
	auto prop = basyx::serialization::json::deserialize_property(json_prop_int);

	ASSERT_EQ(prop->get_value_type(), "int");
	ASSERT_EQ(prop->getIdShort(), "MaxRotationSpeed");
	ASSERT_EQ(prop->getCategory(), "PARAMETER");

	auto int_prop = dynamic_cast<Property<int>*>(prop.get());
	ASSERT_NE(int_prop, nullptr);
	ASSERT_EQ(int_prop->get_value(), 5000);

	int j = 2;
};

TEST_F(JsonDeserializerTest, SubmodelElementCollection)
{
	auto col = basyx::serialization::json::deserialize_submodelelement_collection(json_submodel_element_collection);

	ASSERT_EQ(col.size(), 2);

	ASSERT_TRUE(col.getSubmodelElements().hasEntry("MaxRotationSpeed"));
	ASSERT_TRUE(col.getSubmodelElements().hasEntry("MLP"));
	
	ASSERT_EQ(col.getSubmodelElements().get("MaxRotationSpeed")->get_model_type(), ModelTypes::Property);
	ASSERT_EQ(col.getSubmodelElements().get("MLP")->get_model_type(), ModelTypes::MultiLanguageProperty);
};

TEST_F(JsonDeserializerTest, Submodel)
{
	auto sm = basyx::serialization::json::deserialize_submodel(json_submodel);

	ASSERT_EQ(sm.getIdShort(), "sm_1");
	ASSERT_EQ(sm.getIdentification().getId(), "submodel");
	ASSERT_EQ(sm.getIdentification().getIdType(), KeyType::Custom);

	ASSERT_EQ(sm.getSubmodelElements().size(), 2);
};

TEST_F(JsonDeserializerTest, RoundTripSubmodel)
{
	Submodel sm_in{ "sm", Identifier::Custom("submodel")};
	sm_in.getSubmodelElements().create<Property<int>>("intProp", 5000);
	sm_in.getSubmodelElements().create<MultiLanguageProperty>("multiLangProp", langstringset_t{ {"EN", "example"}, {"DE", "beispiel"} });

	auto serialized = basyx::serialization::json::serialize(sm_in);

	std::cout << std::endl << serialized.dump(4) << std::endl;

	auto sm_out = basyx::serialization::json::deserialize_submodel(serialized);
};

TEST_F(JsonDeserializerTest, AssetAdministrationShell)
{
	auto aas = basyx::serialization::json::deserialize_aas(json_aas);

	ASSERT_EQ(aas.getIdShort(), "aas_1");
	ASSERT_EQ(aas.getIdentification().getId(), "asset_admin_shell_1");
	ASSERT_EQ(aas.getIdentification().getIdType(), KeyType::Custom);

	ASSERT_EQ(aas.getSubmodels().size(), 1);
};
