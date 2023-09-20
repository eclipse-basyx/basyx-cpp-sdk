#include <gtest/gtest.h>

#include <basyx/util/constrained_string/constrained_string.hpp>
#include <basyx/util/constrained_string/regex_checker.hpp>

#include <string>

using namespace basyx;

class TestRegEx
{
public:
	static std::regex regex;
};

std::regex TestRegEx::regex("^([0-9]|[1-9][0-9]*)$");

class ConstrainedStringTest : public ::testing::Test
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

using label_type_t = util::constrained_string<1, 64>;
using short_label_type_t = util::constrained_string<1, 4>;
using min_label_type_t = util::constrained_string<4, 8>;
using version_revision_type_t = util::constrained_string<1, 4, util::RegExChecker<TestRegEx>>;

TEST_F(ConstrainedStringTest, Constructor1)
{
	std::string test_str = "test";
	util::string_view test_sv = test_str;

	label_type_t label_c_str("test");
	label_type_t label_c_str_assign = "test";

	label_type_t label_str(test_str);
	label_type_t label_str_assign = test_str;

	label_type_t label_sv(test_sv);
	label_type_t label_sv_assign = test_sv;

	ASSERT_EQ(label_c_str, "test");
	ASSERT_EQ(label_c_str_assign, "test");

	ASSERT_EQ(label_str, test_str);
	ASSERT_EQ(label_str_assign, test_str);

	ASSERT_EQ(label_sv, test_sv);
	ASSERT_EQ(label_sv_assign, test_sv);
}

TEST_F(ConstrainedStringTest, Compare)
{
	label_type_t label_1("test");
	label_type_t label_2("999");
	version_revision_type_t version_1("999");

	ASSERT_EQ(label_1, label_1);
	ASSERT_NE(label_1, label_2);
	ASSERT_NE(label_1, version_1);

	ASSERT_EQ(label_1, label_1);
	ASSERT_EQ(label_2, label_2);
	ASSERT_EQ(version_1, version_1);
	ASSERT_EQ(version_1, label_2);
}

TEST_F(ConstrainedStringTest, EqualsOperator)
{
	label_type_t label_1("test");
	label_type_t label_2("999");
	version_revision_type_t version_1("999");

	ASSERT_TRUE(label_1 == "test");
	ASSERT_TRUE(label_1 == std::string("test"));
	ASSERT_TRUE(label_1 == util::string_view("test"));
	ASSERT_FALSE(label_1 == "abcd");

	ASSERT_TRUE(version_1 == "999");
	ASSERT_TRUE(version_1 == std::string("999"));
	ASSERT_TRUE(version_1 == util::string_view("999"));
	ASSERT_FALSE(version_1 == "111");
}

TEST_F(ConstrainedStringTest, StringInteropTests)
{
	std::string str("abcd");
	label_type_t label_1("test");

	str = label_1;
	ASSERT_EQ(str, "test");
	ASSERT_EQ(str, label_1.str());

	util::string_view sv = label_1;
	ASSERT_EQ(sv, "test");
	ASSERT_EQ(sv, label_1);
}

TEST_F(ConstrainedStringTest, ConstraintCheckTest)
{
	short_label_type_t label_1{ "abcd" };
	short_label_type_t label_2{ "test" };
	short_label_type_t label_3{ "test1234" };
	version_revision_type_t version_1("999");

	ASSERT_EQ(label_1, "abcd");
	ASSERT_EQ(label_2, "test");
	ASSERT_EQ(label_3, "test");

	label_2 = "abcd1234";
	ASSERT_EQ(label_2, "abcd");

	label_2 = version_1;
	ASSERT_EQ(label_2, "999");
	ASSERT_EQ(version_1, "999");

	version_1 = label_1;
	ASSERT_EQ(version_1, "999");
	ASSERT_EQ(label_1, "abcd");

	version_1 = "0111";
	ASSERT_EQ(version_1, "999");

	version_1 = "111";
	ASSERT_EQ(version_1, "111");

	min_label_type_t min_label{ "test" };
	ASSERT_EQ(min_label, "test");

	min_label = "abc";
	ASSERT_EQ(min_label, "abc-");
}