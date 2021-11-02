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

TEST_F(ElementContainerTest, CopyConstructor)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 2));
	container.add(Property<int>("intProp2", 2));

	ElementContainer<SubmodelElement> container_2(container);

	ASSERT_EQ(container_2.size(), 2);
}

TEST_F(ElementContainerTest, MoveConstructor)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 2));
	container.add(Property<int>("intProp2", 2));

	ElementContainer<SubmodelElement> container_2 = std::move(container);

	ASSERT_EQ(container.size(), 0);
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

TEST_F(ElementContainerTest, CreateElement_1)
{
	ElementContainer<SubmodelElement> container;
	ASSERT_EQ(container.size(), 0);

	container.create<Property<int>>("intProp", 2);
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

TEST_F(ElementContainerTest, GetElement_4)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<std::string>("stringProp", "test"));

	auto prop = container.get<Property<std::string>>("stringProp");
	ASSERT_NE(prop, nullptr);
	ASSERT_EQ(prop->get_value(), "test");
	int j = 2;
}

TEST_F(ElementContainerTest, Iteration)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 1));
	container.add(Property<int>("intProp2", 2));
	container.add(Property<int>("intProp3", 3));
	container.add(Property<int>("intProp4", 4));

	bool prop1_found = false;
	bool prop2_found = false;
	bool prop3_found = false;
	bool prop4_found = false;

	for (const auto & entry : container) {
		if (entry->getIdShort() == "intProp1")
			prop1_found = true;

		if (entry->getIdShort() == "intProp2")
			prop2_found = true;

		if (entry->getIdShort() == "intProp3")
			prop3_found = true;

		if (entry->getIdShort() == "intProp4")
			prop4_found = true;
	}

	ASSERT_TRUE(prop1_found && prop2_found && prop3_found && prop4_found);
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

TEST_F(ElementContainerTest, Append_1)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 2));
	container.add(Property<int>("intProp2", 2));

	ElementContainer<SubmodelElement> container2;
	container2.add(Property<std::string>("stringProp", "test"));
	container2.add(MultiLanguageProperty("multiLangProp", { {"en","test"},{"de","test"} }));

	ASSERT_EQ(container.size(), 2);
	ASSERT_EQ(container2.size(), 2);

	container.append(container2);

	ASSERT_EQ(container.size(), 4);

	auto stringProp = container.get<Property<std::string>>("stringProp");
	ASSERT_NE(stringProp, nullptr);
	ASSERT_EQ(*stringProp->get_value(), "test");

	auto multiLangProp = container.get<MultiLanguageProperty>("multiLangProp");
	ASSERT_NE(multiLangProp, nullptr);
	ASSERT_EQ(multiLangProp->get_value().size(), 2);
}

TEST_F(ElementContainerTest, Append_2)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 2));
	container.add(Property<int>("intProp2", 2));

	ElementContainer<SubmodelElement> container2;
	auto original = container2.add(Property<std::string>("stringProp", "test"));
	
	container.append(container2);

	auto copy = container.get<Property<std::string>>("stringProp");
	copy->set_value("edited");

	ASSERT_EQ(copy->get_value(), "edited");
	ASSERT_EQ(original->get_value(), "test");
}

TEST_F(ElementContainerTest, Append_3)
{
	ElementContainer<SubmodelElement> container;
	container.add(Property<int>("intProp1", 1));
	container.add(Property<int>("intProp2", 2));

	ElementContainer<SubmodelElement> container2;
	container2.add(Property<int>("intProp2", 42));
	container2.add(Property<int>("intProp3", 3));

	ASSERT_EQ(container.size(), 2);
	ASSERT_EQ(container2.size(), 2);

	container.append(container2);

	// Should only add intProp3, since intProp2 already exists
	ASSERT_EQ(container.size(), 3);

	ASSERT_NE(container.get(0), nullptr);
	ASSERT_EQ(container.get(0)->getIdShort(), "intProp1");

	ASSERT_NE(container.get(1), nullptr);
	ASSERT_EQ(container.get(1)->getIdShort(), "intProp2");
	ASSERT_EQ(container.get<Property<int>>(1)->get_value(), 2);

	ASSERT_NE(container.get(2), nullptr);
	ASSERT_EQ(container.get(2)->getIdShort(), "intProp3");
}

TEST_F(ElementContainerTest, Owner_Default)
{
	ElementContainer<SubmodelElement> container;
	auto prop = container.create<MultiLanguageProperty>("prop1");

	ASSERT_EQ(prop->getParent(), nullptr);
};

TEST_F(ElementContainerTest, Owner_Set)
{
	MultiLanguageProperty owner_1{ "owner_1" };

	ElementContainer<SubmodelElement> container{ &owner_1 };
	auto prop = container.create<MultiLanguageProperty>("prop1");

	ASSERT_EQ(prop->getParent(), &owner_1);
};

TEST_F(ElementContainerTest, Owner_Copy)
{
	MultiLanguageProperty owner_1{ "owner_1" };
	MultiLanguageProperty owner_2{ "owner_2" };

	ElementContainer<SubmodelElement> container1{ &owner_1 };
	ElementContainer<SubmodelElement> container2{ &owner_2 };
	container2.create<MultiLanguageProperty>("prop1");

	ASSERT_EQ(container1.size(), 0);
	ASSERT_EQ(container2.size(), 1);

	container1 = container2;

	ASSERT_EQ(container1.size(), 1);
	ASSERT_EQ(container2.size(), 1);

	ASSERT_EQ(container1.get(0)->getParent(), &owner_1);
	ASSERT_EQ(container2.get(0)->getParent(), &owner_2);
};

TEST_F(ElementContainerTest, Owner_Move)
{
	MultiLanguageProperty owner_1{ "owner_1" };
	MultiLanguageProperty owner_2{ "owner_2" };

	ElementContainer<SubmodelElement> container1{ &owner_1 };
	ElementContainer<SubmodelElement> container2{ &owner_2 };
	container2.create<MultiLanguageProperty>("prop1");

	ASSERT_EQ(container1.size(), 0);
	ASSERT_EQ(container2.size(), 1);

	container1 = std::move(container2);

	ASSERT_EQ(container1.size(), 1);
	ASSERT_EQ(container2.size(), 0);

	ASSERT_EQ(container1.get(0)->getParent(), &owner_1);
};
