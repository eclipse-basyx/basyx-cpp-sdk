#include <gtest/gtest.h>

#include <util/string_view/string_view.hpp>

#include <string>

using namespace basyx;

class StringViewTest : public ::testing::Test
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

TEST_F(StringViewTest, Constructor1)
{
	util::basic_string_view<char> sv;
	ASSERT_TRUE(sv.empty());
	ASSERT_EQ(sv.size(), 0);
}

TEST_F(StringViewTest, Constructor2)
{
	const char * c_str = "test1234";
	util::basic_string_view<char> sv(c_str, 4);
	ASSERT_FALSE(sv.empty());
	ASSERT_EQ(sv.size(), 4);
}

TEST_F(StringViewTest, Constructor3)
{
	const char * c_str = "test1234";
	util::basic_string_view<char> sv(c_str);
	ASSERT_FALSE(sv.empty());
	ASSERT_EQ(sv.size(), 8);
}

TEST_F(StringViewTest, Constructor4)
{
	std::string str("test1234");
	util::basic_string_view<char> sv(str);
	ASSERT_FALSE(sv.empty());
	ASSERT_EQ(sv.size(), 8);
}

TEST_F(StringViewTest, Compare)
{
	util::basic_string_view<char> sv1("test1234");
	util::basic_string_view<char> sv2("test");

	std::string str("test1234");
	util::basic_string_view<char> sv3(str);

	ASSERT_EQ(sv1.compare(sv1), 0);
	ASSERT_EQ(sv3.compare(sv3), 0);

	ASSERT_LT(sv2.compare(sv1), 0);
	ASSERT_GT(sv1.compare(sv2), 0);
}

TEST_F(StringViewTest, EqualsOperator)
{
	util::basic_string_view<char> sv1("test1234");
	util::basic_string_view<char> sv2("test");

	std::string str("test1234");
	util::basic_string_view<char> sv3(str);

	ASSERT_TRUE(sv1 == sv1);
	ASSERT_FALSE(sv1 != sv1);

	ASSERT_FALSE(sv1 == sv2);
	ASSERT_TRUE(sv1 != sv2);

	ASSERT_TRUE(sv1 == "test1234");
	ASSERT_TRUE(sv2 != "test1234");
	ASSERT_TRUE(sv1 == str);
}
