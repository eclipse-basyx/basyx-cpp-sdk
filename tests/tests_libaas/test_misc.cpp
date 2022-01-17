#include <gtest/gtest.h>

#include <basyx/util/string_view/string_view.hpp>
#include <basyx/util/algorithm/string.hpp>

using namespace basyx;

class MiscTest : public ::testing::Test
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

TEST_F(MiscTest, SplitPath)
{
	using namespace basyx::util::algorithm;

	util::string_view path_1 = "submodel";
	util::string_view path_2 = "submodel/";
	util::string_view path_3 = "/submodel/";
	util::string_view path_4 = "/submodel";
	util::string_view path_5 = "///submodel///";
	util::string_view path_6 = "/submodel/test/";
	util::string_view path_7 = "submodel///test";
	util::string_view path_8 = "/submodel/test/test2/";
	util::string_view path_9 = "submodel/test/test2";

	auto pathlist_1 = string::split(path_1, '/');
	auto pathlist_2 = string::split(path_2, '/');
	auto pathlist_3 = string::split(path_3, '/');
	auto pathlist_4 = string::split(path_4, '/');
	auto pathlist_5 = string::split(path_5, '/');
	auto pathlist_6 = string::split(path_6, '/');
	auto pathlist_7 = string::split(path_7, '/');
	auto pathlist_8 = string::split(path_8, '/');
	auto pathlist_9 = string::split(path_9, '/');

	ASSERT_EQ(pathlist_1.size(), 1);
	ASSERT_EQ(pathlist_2.size(), 1);
	ASSERT_EQ(pathlist_3.size(), 1);
	ASSERT_EQ(pathlist_4.size(), 1);
	ASSERT_EQ(pathlist_5.size(), 1);
	ASSERT_EQ(pathlist_6.size(), 2);
	ASSERT_EQ(pathlist_7.size(), 2);
	ASSERT_EQ(pathlist_8.size(), 3);
	ASSERT_EQ(pathlist_9.size(), 3);
};