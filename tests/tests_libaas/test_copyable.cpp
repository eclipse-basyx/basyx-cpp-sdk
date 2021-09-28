#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/environment.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/asset.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/submodel.h>
#include <basyx/views/view.h>

#include <basyx/constraints/qualifier.h>
#include <basyx/constraints/formula.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/operation.h>
#include <basyx/submodelelement/operationvariable.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class CopyableTest : public ::testing::Test {
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

TEST_F(CopyableTest, TestBase)
{
	MultiLanguageProperty mlp{ "test", {{"en", "example"},{"de", "test"}} };

	auto base_copy = mlp.copy();
	ASSERT_EQ(base_copy->get_model_type(), ModelTypes::MultiLanguageProperty);
	ASSERT_EQ(base_copy->getIdShort(), "test");

	auto base_copy_casted = dynamic_cast<MultiLanguageProperty*>(base_copy.get());
	ASSERT_NE(base_copy_casted, nullptr);
	ASSERT_EQ(base_copy_casted->get_value().size(), 2);

	auto copy_back = base_copy->copy<MultiLanguageProperty>();
	ASSERT_NE(copy_back, nullptr);
	ASSERT_EQ(copy_back->get_value().size(), 2);
}

TEST_F(CopyableTest, TestSameType)
{
	MultiLanguageProperty mlp{ "test", {{"en", "example"},{"de", "test"}} };
	
	auto mlp_copy = mlp.copy<MultiLanguageProperty>();
	ASSERT_EQ(mlp_copy->get_model_type(), ModelTypes::MultiLanguageProperty);
	ASSERT_EQ(mlp_copy->getIdShort(), "test");
	ASSERT_EQ(mlp_copy->get_value().size(), 2);
}

TEST_F(CopyableTest, WrongCopy)
{
	MultiLanguageProperty mlp{ "test", {{"en", "example"},{"de", "test"}} };
	auto do_not_do_this = mlp.copy<SubmodelElementCollection>();
	ASSERT_EQ(do_not_do_this, nullptr);

	auto do_not_do_this_too = mlp.copy<Submodel>();
	ASSERT_EQ(do_not_do_this_too, nullptr);
}
