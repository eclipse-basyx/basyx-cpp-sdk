#include <gtest/gtest.h>

#include <util/optional/optional.hpp>

#include <string>

using namespace basyx;

class destructor_observer
{
private:
	bool & destructor_called;
public:
	destructor_observer(bool & signal) : destructor_called(signal) { destructor_called = false; };
	~destructor_observer() { destructor_called = true; };
};

class OptionalTest : public ::testing::Test
{
protected:
	// Test settings
	bool destructor_called = false;

	// Test variables

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{

	}
};

TEST_F(OptionalTest, Constructor1)
{
	util::optional<int> i;

	ASSERT_FALSE(i.has_value());
	ASSERT_FALSE(i);
	ASSERT_EQ(i, util::nullopt);
};

TEST_F(OptionalTest, Constructor2)
{
	util::optional<int> i = {};

	ASSERT_FALSE(i.has_value());
	ASSERT_FALSE(i);
	ASSERT_EQ(i, util::nullopt);
};

TEST_F(OptionalTest, Constructor3)
{
	util::optional<int> i = 2;

	ASSERT_TRUE(i.has_value());
	ASSERT_TRUE(i);
	ASSERT_EQ(*i, 2);
};

TEST_F(OptionalTest, Constructor4)
{
	std::string val = "test";

	util::optional<std::string> str = std::move(val);

	ASSERT_TRUE(str.has_value());
	ASSERT_TRUE(str);
	ASSERT_EQ(*str, "test");
};

TEST_F(OptionalTest, Constructor5)
{
	util::optional<std::string> str("test");

	ASSERT_TRUE(str.has_value());
	ASSERT_TRUE(str);
	ASSERT_EQ(*str, "test");
};

TEST_F(OptionalTest, ConstructorAssignment1)
{
	util::optional<std::string> str = "test";

	ASSERT_TRUE(str.has_value());
	ASSERT_TRUE(str);
	ASSERT_EQ(*str, "test");

	// Assign from temporary
	std::string temp = "temp";
	util::optional<std::string> str2 = std::move(temp);
	
	ASSERT_TRUE(str2.has_value());
	ASSERT_TRUE(str2);
	ASSERT_EQ(*str2, "temp");
};

TEST_F(OptionalTest, Assignment1)
{
	util::optional<int> i;
	i = 5;

	ASSERT_TRUE(i.has_value());
	ASSERT_TRUE(i);
	ASSERT_EQ(*i, 5);
};

TEST_F(OptionalTest, Assignment2)
{
	util::optional<std::string> str;
	str = "test";

	ASSERT_TRUE(str.has_value());
	ASSERT_TRUE(str);
	ASSERT_EQ(*str, "test");
};

TEST_F(OptionalTest, MoveAssignment)
{
	util::optional<std::string> str("test");
	auto str2 = std::move(str);

	ASSERT_FALSE(str.has_value());
	ASSERT_TRUE(str2.has_value());
	ASSERT_TRUE(str2);
	ASSERT_EQ(*str2, "test");
};

TEST_F(OptionalTest, EmplaceTrivial)
{
	constexpr int val = 2;

	util::optional<int> i;

	ASSERT_FALSE(i.has_value());
	ASSERT_FALSE(i);
	ASSERT_EQ(i, util::nullopt);

	i.emplace(val);

	ASSERT_TRUE(i.has_value());
	ASSERT_TRUE(i);
	ASSERT_NE(i, util::nullopt);

	ASSERT_EQ(*i, val);
};

TEST_F(OptionalTest, EmplaceNonTrivial)
{
	const std::string val = "test";

	util::optional<std::string> str;

	ASSERT_FALSE(str.has_value());
	ASSERT_FALSE(str);
	ASSERT_EQ(str, util::nullopt);

	str.emplace("test");

	ASSERT_TRUE(str.has_value());
	ASSERT_TRUE(str);
	ASSERT_NE(str, util::nullopt);

	ASSERT_EQ(val, *str);
};

TEST_F(OptionalTest, ValueAccess)
{
	constexpr int val = 2;

	util::optional<int> i;
	i.emplace(val);

	ASSERT_EQ(i.value(), val);
	ASSERT_EQ(*i, val);
};

TEST_F(OptionalTest, ArrowOperator)
{
	util::optional<std::string> opt = "test";
	ASSERT_EQ(opt->empty(), false);
	ASSERT_EQ(opt->size(), 4);
};

TEST_F(OptionalTest, EqualOperators)
{
	util::optional<std::string> str1 = "test";
	util::optional<std::string> str2 = "value";
	util::optional<std::string> empty;

	ASSERT_NE(str1, str2);
	ASSERT_NE(str1, empty);

	ASSERT_EQ(str1, "test");
	ASSERT_NE(str1, "value");

	ASSERT_EQ("test", str1);
	ASSERT_NE("value", str1);
};

TEST_F(OptionalTest, Reset)
{
	constexpr int val = 2;

	util::optional<int> i;

	ASSERT_FALSE(i.has_value());
	ASSERT_FALSE(i);

	i.emplace(val);

	ASSERT_TRUE(i.has_value());
	ASSERT_TRUE(i);

	i.reset();

	ASSERT_FALSE(i.has_value());
	ASSERT_FALSE(i);
};

TEST_F(OptionalTest, DestructorTest)
{
	util::optional<destructor_observer> opt;
	opt.emplace(this->destructor_called);
	ASSERT_FALSE(this->destructor_called);
	
	opt.reset();
	ASSERT_TRUE(this->destructor_called);
}

