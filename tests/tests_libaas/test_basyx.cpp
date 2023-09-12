#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/environment.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/submodel.h>

#include <basyx/enums/IdentifiableElements.h>

#include <basyx/qualifiable/qualifier.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/entity.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class BaseTest : public ::testing::Test {
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

TEST_F(BaseTest, MinMaxString) {
   unsigned int min = 1;
   unsigned int max = 3;

   // Check if min size and content is honored
   base::MinMaxString mmStr(min, max);
   std::string s = "";
   mmStr = s;
   ASSERT_EQ(min, mmStr.length());
   std::string cmp;
   cmp+= base::STRING_PADDING;
   ASSERT_STREQ(cmp.data(), mmStr.str().data());

   // Check if max size is honored
   base::MinMaxString mmStr2(min, max);
   std::string s2;
   s2.resize(max + 10);
   mmStr2 = s2;
   ASSERT_EQ(max, mmStr2.length());

   // check if resizes does the right thing
   base::MinMaxString mmStr3(min, max);
   mmStr3.resize(3000);
   ASSERT_EQ(max, mmStr3.length());

   base::MinMaxString mmStr4(min, max);
   mmStr4.resize(3000, ' ');
   ASSERT_EQ(max, mmStr4.length());

   // Lets assign a string and see if it is set correct
   base::MinMaxString mmStr5(min, max);
   std::string ste = "te";
   mmStr5.assign(ste);
   ASSERT_STREQ(ste.data(), mmStr5.str().data());

}

TEST_F(BaseTest, LangStringSet)
{
    basyx::langstring_t l { "de", "test" };
    basyx::langstringset_t ls;

    ASSERT_EQ(ls.size(), 0);

    ls.add("en", "test");
    ASSERT_EQ(ls.size(), 1);

    ls.add(std::move(l));

    auto en = ls.get("en");
    auto de = ls.get("de");
    auto pl = ls.get("pl");

    ASSERT_TRUE(en);
    ASSERT_TRUE(de);
    ASSERT_FALSE(pl);

    ASSERT_EQ(*en, "test");
    ASSERT_EQ(*de, "test");
}

TEST_F(BaseTest, IdentifierTest)
{
   Identifier id("test");
   ASSERT_EQ("test", id);

   Identifier id2 = id;
   ASSERT_EQ("test", id2);

   Identifier id3 { "test3" };
   ASSERT_EQ("test3", id3);

   Identifier id4("test_bad");
   id4.assign("test_good");
   ASSERT_EQ("test_good", id4);
}

TEST_F(BaseTest, AutoKeyType)
{
    Key key_1 { "CUSTOM" };
    Key key_2 { "http://test-key" };
    Key key_3 { "https://test-key" };
    Key key_4 { "urn://test-key" };
    Key key_5 { "0173-1#02-AAR972#002" };
    Key key_6 { "0173-1#02-AAR972#00" };
    Key key_7 { "0173-1x02-AAR972#002" };

    ASSERT_EQ(key_1.get_id_type(), KeyType::Custom);
    ASSERT_EQ(key_2.get_id_type(), KeyType::IRI);
    ASSERT_EQ(key_3.get_id_type(), KeyType::IRI);
    ASSERT_EQ(key_4.get_id_type(), KeyType::IRI);
    ASSERT_EQ(key_5.get_id_type(), KeyType::IRDI);
    ASSERT_EQ(key_6.get_id_type(), KeyType::Custom);
    ASSERT_EQ(key_7.get_id_type(), KeyType::Custom);
};

TEST_F(BaseTest, Reference)
{
    Key key { KeyElements::Asset, "test", KeyType::FragmentId };

    Reference reference_1 { key };
    ASSERT_EQ(reference_1.size(), 1);

    Reference reference_2({ KeyElements::AssetAdministrationShell, "test", KeyType::FragmentId });
    ASSERT_EQ(reference_2.size(), 1);

    Reference reference_3 { key, key, key };
    ASSERT_EQ(reference_3.size(), 3);
};

TEST_F(BaseTest, MultiLangProp)
{
    basyx::MultiLanguageProperty mlp { "multiLang" };

    mlp.setCategory("test");
    ASSERT_TRUE(mlp.getCategory());
    ASSERT_EQ(mlp.getCategory().value(), "test");

    mlp.setDescription({ { "en", "example" },
        { "de", "beispiel" } });

    auto& description = mlp.getDescription();

    ASSERT_TRUE(description);
    ASSERT_EQ(description->size(), 2);

    auto ls1 = description->get("en");
    auto ls2 = description->get("de");

    ASSERT_EQ(*ls1, "example");
    ASSERT_EQ(*ls2, "beispiel");

    mlp.kind = basyx::ModelingKind::Instance;
};

TEST_F(BaseTest, Enum)
{
	auto none = IdentifiableElements_::from_string("NONE");
	ASSERT_FALSE(none);

	auto asset = IdentifiableElements_::from_string("Asset");
	ASSERT_TRUE(asset);
	ASSERT_EQ(*asset, IdentifiableElements::Asset);

	std::string str = IdentifiableElements_::to_string(IdentifiableElements::AssetAdministrationShell);
	ASSERT_EQ(str, "AssetAdministrationShell");
};

TEST_F(BaseTest, HasKind)
{
    auto mlp = std::make_unique<MultiLanguageProperty>("test");

    mlp->kind = ModelingKind::Template;
    HasKind* has_kind = mlp.get();
    has_kind->kind = ModelingKind::Instance;
};

TEST_F(BaseTest, RangeTest)
{
    Range<uint32_t> p1 { "int_prop" };
    p1.set_min(1);
    p1.set_max(5);

    ASSERT_EQ(*p1.get_min(), 1);
    ASSERT_EQ(*p1.get_max(), 5);
    ASSERT_EQ(p1.get_value_type(), "unsignedInt");
};

TEST_F(BaseTest, SubmodelElement)
{
    std::unique_ptr<SubmodelElement> prop = std::make_unique<MultiLanguageProperty>("mlp");
}

TEST_F(BaseTest, SubmodelElementCollection)
{
    SubmodelElementCollection col { "col" };
    SubmodelElementCollection col2 { "col2" };

    MultiLanguageProperty mlp("test");

    Property<int> i { "i" };
    i.set_value(5);

    col.getSubmodelElements().add(i);

    i.set_value(6);

    col.getSubmodelElements().add(std::move(i));
    col.getSubmodelElements().add(mlp);

    mlp.get_value().add("en", "test");

    col2.getSubmodelElements().add(mlp);

    col.getSubmodelElements().add(std::move(col2));
};

TEST_F(BaseTest, SubmodelElementCollection_2)
{
    SubmodelElementCollection col { "col" };

    Property<int> i1 { "i1", 2 };
    Property<int> i2 { "i2", 5 };

    col.getSubmodelElements().add(i1);
    col.getSubmodelElements().add(i2);

    auto r0 = col.getSubmodelElements().get("none");
    ASSERT_EQ(r0, nullptr);

    auto r1 = col.getSubmodelElements().get("i1");
    ASSERT_NE(r1, nullptr);

    auto r2 = col.getSubmodelElements().get<Property<int>>("i2");
    ASSERT_NE(r2, nullptr);
    ASSERT_EQ(*r2->get_value(), 5);
};

TEST_F(BaseTest, SubmodelElementCollection_3)
{
    SubmodelElementCollection col1("col1",
        Property<int>("i1", 2),
        Property<float>("f2", 5.0f),
        MultiLanguageProperty("mlp", {
            { "de", "beispiel" },
            { "en", "example" },
            }));

    ASSERT_EQ(col1.size(), 3);

    // Check first property
    auto prop1 = col1.getSubmodelElements().get("i1");
    ASSERT_EQ(prop1->get_model_type(), ModelTypes::Property);
};

TEST_F(BaseTest, SubmodelElementCollection_CopyConstructor)
{
    SubmodelElementCollection col1("col1",
        Property<int>("i1", 2),
        Property<float>("f2", 5.0f),
        MultiLanguageProperty("mlp", {
            { "de", "beispiel" },
            { "en", "example" },
    }));

    SubmodelElementCollection col2 = col1;
    SubmodelElementCollection col3(col1);
    auto col4 = std::make_unique<SubmodelElementCollection>(col1);

    ASSERT_EQ(col1.size(), 3);
    ASSERT_EQ(col2.size(), 3);
    ASSERT_EQ(col3.size(), 3);
    ASSERT_EQ(col4->size(), 3);

    ASSERT_EQ(col1.getIdShort(), "col1");
    ASSERT_EQ(col2.getIdShort(), "col1");
    ASSERT_EQ(col3.getIdShort(), "col1");
    ASSERT_EQ(col4->getIdShort(), "col1");
};


TEST_F(BaseTest, Submodel)
{
	Submodel sm("sm", "test/sm_1");

    sm.getSubmodelElements().add(Property<int>("p1", 2));
    sm.getSubmodelElements().add(Property<int>("p2", 3));

    sm.setSemanticId("custom_submodel");
}

TEST_F(BaseTest, SubmodelAddElements)
{
	using stringProp_t = Property<std::string>;

   Submodel sm("sm1", Identifier("https://admin-shell.io/cpp#sm1"));
	sm.setCategory("test");
	sm.setSemanticId("0173-1#02-AAR972#002");
	sm.setAdministration({ "1.0", "v2" });

   Submodel sm2("sm2", Identifier("https://admin-shell.io/cpp#sm2"));

	sm.getSubmodelElements().add(Property<std::string>("testProperty1", "Yay a value!"));
	sm.getSubmodelElements().add(Property<std::string>("testProperty2", "Values and values! :O"));

	ASSERT_EQ(sm.getSubmodelElements().size(), 2);

	auto * elem_1 = sm.getSubmodelElements().get<stringProp_t>("testProperty1");
	ASSERT_TRUE(elem_1 != nullptr);
	ASSERT_EQ(*elem_1->get_value(), "Yay a value!");

	auto * elem_2 = sm.getSubmodelElements().get<stringProp_t>("testProperty2");
	ASSERT_TRUE(elem_2 != nullptr);
	ASSERT_EQ(*elem_2->get_value(), "Values and values! :O");
}

TEST_F(BaseTest, EntityTest)
{
	Entity entity{ "entity" };
}

TEST_F(BaseTest, QualifierTest)
{
	std::unique_ptr<QualifierBase> constraint_qualifier = std::make_unique<Qualifier<int>>("test", 5);

	ASSERT_EQ(constraint_qualifier->get_model_type(), ModelTypes::Qualifier);
}

TEST_F(BaseTest, AutoIdentifierTest)
{
	AssetAdministrationShell aas{ "aas", "https://admin-shell.io/aas", { AssetKind::Instance } };

	Submodel sm{ "sm", "test/sm1" };
}

TEST_F(BaseTest, AssetInfTest)
{
   Identifier id("test");
	AssetInformation assetInf{ AssetKind::Instance };

   assetInf.setGlobalAssetId(id);
};

TEST_F(BaseTest, AssetAdministrationShell)
{
	AssetAdministrationShell aas("aas", "https://admin-shell.io/aas", { AssetKind::Instance });
	aas.getSubmodels().add(Submodel("sm", "test/sm_1"));
}

TEST_F(BaseTest, Environment)
{
	Environment env;

	env.getAssetAdministrationShells().add(
		AssetAdministrationShell("aas", "https://admin-shell.io/aas", AssetInformation{ AssetKind::Instance })
	);
}

TEST_F(BaseTest, AssetInfoInAas)
{
      Identifier id("cppTestAsset");
		AssetInformation assetinfo(basyx::AssetKind::Instance);
      assetinfo.setGlobalAssetId(id);

		auto assetInfo2 = assetinfo;
		AssetAdministrationShell aas("cppAas", "cppAas", assetinfo);
}
