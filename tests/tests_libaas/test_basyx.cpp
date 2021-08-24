#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/submodel.h>
#include <basyx/views/view.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/operation.h>
#include <basyx/submodelelement/operationvariable.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>

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

TEST_F(BaseTest, Key)
{
    Key key_1 { "CUSTOM" };
    Key key_2 { "http://test-key" };
    Key key_3 { "https://test-key" };
    Key key_4 { "urn://test-key" };
    Key key_5 { "0173-1#02-AAR972#002" };
    Key key_6 { "0173-1#02-AAR972#00" };
    Key key_7 { "0173-1x02-AAR972#00" };

    ASSERT_EQ(key_1.get_id_type(), KeyType::IdentifierType::Custom);
    ASSERT_EQ(key_2.get_id_type(), KeyType::IdentifierType::IRI);
    ASSERT_EQ(key_3.get_id_type(), KeyType::IdentifierType::IRI);
    ASSERT_EQ(key_4.get_id_type(), KeyType::IdentifierType::IRI);
    ASSERT_EQ(key_5.get_id_type(), KeyType::IdentifierType::IRDI);
    ASSERT_EQ(key_6.get_id_type(), KeyType::IdentifierType::Custom);
    ASSERT_EQ(key_7.get_id_type(), KeyType::IdentifierType::Custom);
};

TEST_F(BaseTest, Reference)
{
    Key key { KeyElements::Asset, "test", KeyType::LocalKeyType::FragmentId };

    Reference reference_1 { key };
    ASSERT_EQ(reference_1.size(), 1);

    Reference reference_2({ KeyElements::AssetAdministrationShell, "test", KeyType::LocalKeyType::FragmentId });
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

TEST_F(BaseTest, HasKind)
{
    auto mlp = std::make_unique<MultiLanguageProperty>("test");

    mlp->kind = ModelingKind::Template;
    HasKind* has_kind = mlp.get();
    has_kind->kind = ModelingKind::Instance;
};

TEST_F(BaseTest, PropertyTest1)
{
    Property<int> p1 { "int_prop" };
    p1.set_value(5);

    ASSERT_EQ(*p1.get_value(), 5);
    ASSERT_EQ(p1.get_value_type(), "int");

    Property<float> p2 { "float_prop" };
    ASSERT_EQ(p2.get_value_type(), "float");
    ASSERT_FALSE(p2.get_value());

    p2.set_value(5.0f);
    ASSERT_TRUE(p2.get_value());
    ASSERT_EQ(*p2.get_value(), 5.0f);
};

TEST_F(BaseTest, PropertyTest2)
{
    Property<int> p1 { "int_prop", 5 };
    ASSERT_EQ(*p1.get_value(), 5);
    ASSERT_EQ(p1.get_value_type(), "int");

    Property<float> p2 { "float_prop", 5.0f };
    ASSERT_TRUE(p2.get_value());
    ASSERT_EQ(*p2.get_value(), 5.0f);

    Property<std::string> p3 { "string_prop", "test" };
    ASSERT_TRUE(p3.get_value());
    ASSERT_EQ(*p3.get_value(), "test");

    int j = 2;
};

TEST_F(BaseTest, RangeTest)
{
    Range<uint32_t> p1 { "int_prop" };
    p1.set_min(1);
    p1.set_max(5);

    ASSERT_EQ(*p1.get_min(), 1);
    ASSERT_EQ(*p1.get_max(), 5);
    ASSERT_EQ(p1.get_value_type(), "unsignedInt");

    int j = 2;
};

TEST_F(BaseTest, PropertyType)
{
    ASSERT_EQ(Property<uint8_t> { "id" }.get_value_type(), "unsignedByte");
    ASSERT_EQ(Property<int8_t> { "id" }.get_value_type(), "byte");
    ASSERT_EQ(Property<std::string> { "id" }.get_value_type(), "string");
    ASSERT_EQ(Property<double> { "id" }.get_value_type(), "double");
    ASSERT_EQ(Property<float> { "id" }.get_value_type(), "float");
    ASSERT_EQ(Property<char> { "id" }.get_value_type(), "byte");

    int j = 2;
};

TEST_F(BaseTest, OperationVariable)
{
    auto var = OperationVariable::create<MultiLanguageProperty>("op_var", "mlp");
};

TEST_F(BaseTest, Operation)
{
    Operation op { "test" };

    //	op.set_input_variables({ std::move(  OperationVariable::create<MultiLanguageProperty>("op_var", "mlp") ) });

    auto mlp = std::make_unique<MultiLanguageProperty>("mlp");

    op.set_input_variables(
        OperationVariable::create<MultiLanguageProperty>("op_var", "mlp"),
        OperationVariable::create<MultiLanguageProperty>("op_var2", "mlp"));
};

TEST_F(BaseTest, SubmodelElement)
{
    std::unique_ptr<SubmodelElement> prop = std::make_unique<MultiLanguageProperty>("mlp");

    int j = 2;
}

TEST_F(BaseTest, SubmodelElementCollection)
{
    SubmodelElementCollection col { "col" };
    SubmodelElementCollection col2 { "col2" };

    MultiLanguageProperty mlp("test");

    Property<int> i { "i" };
    i.set_value(5);

    col.add(i);

    i.set_value(6);

    col.add(std::move(i));
    col.add(mlp);

    mlp.get_value().add("en", "test");

    col2.add(mlp);

    col.add(std::move(col2));

    int j = 2;
};

TEST_F(BaseTest, SubmodelElementCollection_2)
{
    SubmodelElementCollection col { "col" };

    Property<int> i1 { "i1", 2 };

    Property<int> i2 { "i2", 5 };

    col.add(i1);
    col.add(i2);

    auto r0 = col.get("none");
    ASSERT_EQ(r0, nullptr);

    auto r1 = col.get("i1");
    ASSERT_NE(r1, nullptr);

    auto r2 = col.get<Property<int>>("i2");
    ASSERT_NE(r2, nullptr);
    ASSERT_EQ(*r2->get_value(), 5);

    int j = 2;
};

TEST_F(BaseTest, IntPropertyCopy)
{
    Property<int> i { "i", 1 };
    auto i2 = i;

    i2.~Property();
    i.~Property();

    int j = 2;
}

TEST_F(BaseTest, StringProperty)
{
    spdlog::set_level(spdlog::level::debug);
    Property<std::string> s { "string_prop", "test" };
    auto s2 = s;

    s.set_value("test");

    s.~Property();
    s2.~Property();

    int j = 2;
}

TEST_F(BaseTest, SubmodelElementCollection_3)
{
    spdlog::set_level(spdlog::level::info);
    SubmodelElementCollection col1("col1",
        Property<int>("i1", 2),
        Property<float>("f2", 5.0f),
        MultiLanguageProperty("mlp", {
            { "de", "beispiel" },
            { "en", "example" },
        }));

    ASSERT_EQ(col1.size(), 3);

    // Check first property
    auto prop1 = col1.get("i1");
    ASSERT_EQ(prop1->get_model_type(), ModelTypes::Property);
};

TEST_F(BaseTest, Submodel)
{
    Submodel sm("sm", { IdentifierType::Custom, "test/sm_1" });

    sm.get_submodel_elements().addElement(Property<int>("p1", 2));
    sm.get_submodel_elements().addElement(Property<int>("p2", 3));

    sm.setSemanticId("custom_submodel");
}

TEST_F(BaseTest, SubmodelAddElements)
{
	spdlog::set_level(spdlog::level::debug);

	using stringProp_t = Property<std::string>;

	Submodel sm("sm1", Identifier::IRI("https://admin-shell.io/cpp#sm1"));
	sm.setCategory("test");
	sm.setSemanticId("0173-1#02-AAR972#002");
	sm.setAdministration({ "1.0", "v2" });

	Submodel sm2("sm2", Identifier::IRI("https://admin-shell.io/cpp#sm2"));

	sm.get_submodel_elements().addElement(Property<std::string>("testProperty1", "Yay a value!"));
	sm.get_submodel_elements().addElement(Property<std::string>("testProperty2", "Values and values! :O"));

	ASSERT_EQ(sm.get_submodel_elements().size(), 2);

	auto * elem_1 = sm.get_submodel_elements().getElement<stringProp_t>("testProperty1");
	ASSERT_TRUE(elem_1 != nullptr);
	ASSERT_EQ(*elem_1->get_value(), "Yay a value!");

	auto * elem_2 = sm.get_submodel_elements().getElement<stringProp_t>("testProperty2");
	ASSERT_TRUE(elem_2 != nullptr);
	ASSERT_EQ(*elem_2->get_value(), "Values and values! :O");

	spdlog::set_level(spdlog::level::info);
}

TEST_F(BaseTest, View)
{
	View view_1("view");
	ASSERT_EQ(view_1.size(), 0);

	View view_2("view", 
		"0173-1#02-AAR972#002", 
		"0173-1#02-AAR972#002"
	);
	ASSERT_EQ(view_2.size(), 2);
}