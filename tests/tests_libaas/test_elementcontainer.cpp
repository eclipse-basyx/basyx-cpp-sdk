#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/submodel.h>

#include <basyx/base/elementcontainer.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/operation.h>
#include <basyx/submodelelement/operationvariable.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class ElementContainerTest : public ::testing::Test {
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

TEST_F(ElementContainerTest, Constructor_1)
{
	ElementContainer<SubmodelElement> container;
	ASSERT_EQ(container.size(), 0);
}

TEST_F(ElementContainerTest, Constructor_2)
{
	ElementContainer<SubmodelElement> container_1{
		Property<int>("int", 2)
	};
	ASSERT_EQ(container_1.size(), 1);

	ElementContainer<SubmodelElement> container_2{
		Property<int>("int", 2),
		Property<float>("float", 2.0f),
	};
	ASSERT_EQ(container_2.size(), 2);
}

TEST_F(ElementContainerTest, AddElement_1)
{
	ElementContainer<SubmodelElement> container;
	ASSERT_EQ(container.size(), 0);

	auto prop = container.add(Property<int>("intProp", 2));
	ASSERT_EQ(container.size(), 1);
	ASSERT_EQ(prop->getIdShort(), "intProp");

	auto prop_ptr = std::make_unique<Property<int>>("intProp2", 2);
	auto prop_2 = container.add(std::move(prop_ptr));
	ASSERT_EQ(container.size(), 2);
	ASSERT_EQ(prop_2->getIdShort(), "intProp2");
}

TEST_F(ElementContainerTest, AddElement_2)
{
	ElementContainer<SubmodelElement> container;
	ASSERT_EQ(container.size(), 0);

	container.add(Property<int>("intProp", 2));
	ASSERT_EQ(container.size(), 1);

	auto no_prop = container.add(Property<int>("intProp", 5));
	ASSERT_EQ(container.size(), 1);
	ASSERT_EQ(no_prop, nullptr);
}

TEST_F(ElementContainerTest, HasEntry)
{
	ElementContainer<SubmodelElement> container;
	ASSERT_FALSE(container.hasEntry("intProp"));
	container.add(Property<int>("intProp", 2));
	ASSERT_TRUE(container.hasEntry("intProp"));
}

TEST_F(ElementContainerTest, GetElement_1)
{
	ElementContainer<SubmodelElement> container;
	ASSERT_EQ(container.get("test"), nullptr);
}

TEST_F(ElementContainerTest, GetElement_2)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 2));
	container.add(Property<int>("intProp2", 2));

	auto prop_1 = container.get("intProp1");
	ASSERT_EQ(prop_1->getIdShort(), "intProp1");
}

TEST_F(ElementContainerTest, GetElement_3)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 2));

	auto ok_prop = container.get<Property<int>>("intProp1");
	ASSERT_NE(ok_prop, nullptr);
	ASSERT_EQ(ok_prop->getIdShort(), "intProp1");
	ASSERT_EQ(*ok_prop->get_value(), 2);

	auto wrong_prop = container.get<MultiLanguageProperty>("intProp1");
	ASSERT_EQ(wrong_prop, nullptr);
}

TEST_F(ElementContainerTest, SubClass)
{
	ElementContainer<DataElement> container;
	ASSERT_EQ(container.size(), 0);

	container.add(Property<int>("intProp", 2));
	ASSERT_EQ(container.size(), 1);

	auto no_prop = container.add(Property<int>("intProp", 5));
	ASSERT_EQ(container.size(), 1);
	ASSERT_EQ(no_prop, nullptr);
}

TEST_F(ElementContainerTest, Submodel)
{
	ElementContainer<Submodel> container;
	ASSERT_EQ(container.size(), 0);

	container.add(Submodel("sm", Identifier::Custom("test")));
	ASSERT_EQ(container.size(), 1);
}
