#include <gtest/gtest.h>

#include <basyx/util/algorithm/string.hpp>

#include <string>

using namespace basyx;

class AlgorithmTest : public ::testing::Test
{
protected:
	// Test variables

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{

	}
};

TEST_F(AlgorithmTest, StringSplit_1)
{
	std::vector<std::string> test_strings = {
		"test/string/asdf",
		"/test/string/asdf",
		"test/string/asdf/",
		"/test/string/asdf/",
		"test//string/asdf",
		"test//string///asdf",
		"///test//string/asdf///",
	};

	auto test_split = [this](const std::string & test_str) {
		auto split = util::algorithm::string::split(test_str, '/');

		ASSERT_EQ(split.size(), 3);

		ASSERT_EQ(split[0], "test");
		ASSERT_EQ(split[1], "string");
		ASSERT_EQ(split[2], "asdf");
	};

	for (const auto& str : test_strings)
		test_split(str);
};

TEST_F(AlgorithmTest, StringSplit_2)
{
	std::vector<std::string> test_strings = {
		"a/b/c",
		"a/b/c/",
		"/a/b/c",
		"/a/b/c/",
		"//a/b//c//",
	};

	auto test_split = [this](const std::string& test_str) {
		auto split = util::algorithm::string::split(test_str, '/');

		ASSERT_EQ(split.size(), 3);

		ASSERT_EQ(split[0], "a");
		ASSERT_EQ(split[1], "b");
		ASSERT_EQ(split[2], "c");
	};

	for (const auto& str : test_strings)
		test_split(str);
};

TEST_F(AlgorithmTest, StringViewSplit_1)
{
	std::vector<std::string> test_strings = {
		"a/b/c",
		"a/b/c/",
		"/a/b/c",
		"/a/b/c/",
		"//a/b//c//",
	};

	auto test_split = [this](const std::string& test_str) {
		util::string_view sv{ test_str };
		auto split = util::algorithm::string::split(sv, '/');

		ASSERT_EQ(split.size(), 3);

		ASSERT_EQ(split[0], "a");
		ASSERT_EQ(split[1], "b");
		ASSERT_EQ(split[2], "c");
	};

	for (const auto& str : test_strings)
		test_split(str);
};