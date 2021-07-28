#include <gtest/gtest.h>

#include <basyx/langstringset.h>
#include <basyx/key.h>
#include <basyx/reference.h>

#include <basyx/submodelelement/operation.h>
#include <basyx/submodelelement/operationvariable.h>
#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class BaseTest : public ::testing::Test
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

TEST_F(BaseTest, LangStringSet)
{
	basyx::langstring_t l{ "de", "test" };

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

TEST_F(BaseTest, Reference)
{
	Key key{ "loll", "lol", KeyType::LocalKeyType::Fragmentid };

	Reference reference_1{ key };
	ASSERT_EQ(reference_1.size(), 1);

	Reference reference_2({ "loll", "lol", KeyType::LocalKeyType::Fragmentid });
	ASSERT_EQ(reference_2.size(), 1);

	Reference reference_3{ key, key , key };
	ASSERT_EQ(reference_3.size(), 3);
};

TEST_F(BaseTest, MultiLangProp)
{
	basyx::MultiLanguageProperty mlp{ "multiLang" };

	mlp.set_category("test");
	ASSERT_TRUE(mlp.get_category());
	ASSERT_EQ(mlp.get_category().value(), "test");

	mlp.set_description({ 
		{"en", "example"},
		{"de", "beispiel"}
	});

	auto & description = mlp.get_description();

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

	HasKind * has_kind = mlp.get();

	has_kind->kind = ModelingKind::Instance;

	int j = 2;
};

TEST_F(BaseTest, PropertyTest1)
{
	Property<int> p1{"int_prop"};
	p1.set_value(5);

	ASSERT_EQ(*p1.get_value(), 5);
	ASSERT_EQ(p1.get_value_type(), "int");

	Property<float> p2{ "float_prop" };
	ASSERT_EQ(p2.get_value_type(), "float");
	ASSERT_FALSE(p2.get_value());

	p2.set_value(5.0f);
	ASSERT_TRUE(p2.get_value());
	ASSERT_EQ(*p2.get_value(), 5.0f);

	int j = 2;
};

TEST_F(BaseTest, PropertyTest2)
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

	int j = 2;
};

TEST_F(BaseTest, RangeTest)
{
	Range<uint32_t> p1{ "int_prop" };
	p1.set_min(1);
	p1.set_max(5);

	ASSERT_EQ(*p1.get_min(), 1);
	ASSERT_EQ(*p1.get_max(), 5);
	ASSERT_EQ(p1.get_value_type(), "unsignedInt");

	int j = 2;
};

TEST_F(BaseTest, PropertyType)
{
	ASSERT_EQ(Property<uint8_t>{"id"}.get_value_type(), "unsignedByte");
	ASSERT_EQ(Property<int8_t>{"id"}.get_value_type(), "byte");
	ASSERT_EQ(Property<std::string>{"id"}.get_value_type(), "string");
	ASSERT_EQ(Property<double>{"id"}.get_value_type(), "double");
	ASSERT_EQ(Property<float>{"id"}.get_value_type(), "float");
	ASSERT_EQ(Property<char>{"id"}.get_value_type(), "byte");

	int j = 2;
};


TEST_F(BaseTest, OperationVariable)
{
	auto var = OperationVariable::create<MultiLanguageProperty>("op_var", "mlp");
};

TEST_F(BaseTest, Operation)
{
	Operation op{ "test" };

//	op.set_input_variables({ std::move(  OperationVariable::create<MultiLanguageProperty>("op_var", "mlp") ) });

	auto mlp = std::make_unique<MultiLanguageProperty>("mlp");

	op.set_input_variables( 
		OperationVariable::create<MultiLanguageProperty>("op_var", "mlp"), 
		OperationVariable::create<MultiLanguageProperty>("op_var2", "mlp")
	);
};

TEST_F(BaseTest, SubmodelElement)
{
	std::unique_ptr<SubmodelElement> prop = std::make_unique<MultiLanguageProperty>("mlp");

	int j = 2;
}

TEST_F(BaseTest, SubmodelElementCollection)
{
	SubmodelElementCollection col{ "col" };
	SubmodelElementCollection col2{ "col2" };

	MultiLanguageProperty mlp("lol");

	Property<int> i{ "i" };
	i.set_value(5);

	col.add(i);

	i.set_value(6);

	col.add(std::move(i));
	col.add(mlp);

	mlp.get_value().add("en", "lol");

	col2.add(mlp);

	col.add(std::move(col2));

	int j = 2;
};

TEST_F(BaseTest, SubmodelElementCollection_2)
{
	SubmodelElementCollection col{ "col" };

	Property<int> i1{ "i1", 2 };

	Property<int> i2{ "i2" , 5 };

	col.add(i1);
	col.add(i2);

	auto r1 = col.get("i1");

	int j = 2;
};

