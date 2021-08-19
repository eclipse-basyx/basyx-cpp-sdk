#include <gtest/gtest.h>

#include <spdlog/spdlog.h>

#include <basyxpp-http/httpHandler.h>

#include <util/string_view/string_view.hpp>


using namespace basyx;

class HttpMiscTest : public ::testing::Test
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


TEST_F(HttpMiscTest, SplitPath)
{
	util::string_view path_1 = "submodel";
	util::string_view path_2 = "submodel/";
	util::string_view path_3 = "/submodel/";
	util::string_view path_4 = "/submodel";
	util::string_view path_5 = "///submodel///";
	util::string_view path_6 = "/submodel/test/";
	util::string_view path_7 = "submodel///test";
	util::string_view path_8 = "/submodel/test/test2/";
	util::string_view path_9 = "submodel/test/test2";

	basyx::CREST::httpHandler handler("127.0.0.1", 80);

	auto pathlist_1 = handler.splitPath(path_1, '/');
	auto pathlist_2 = handler.splitPath(path_2, '/');
	auto pathlist_3 = handler.splitPath(path_3, '/');
	auto pathlist_4 = handler.splitPath(path_4, '/');
	auto pathlist_5 = handler.splitPath(path_5, '/');
	auto pathlist_6 = handler.splitPath(path_6, '/');
	auto pathlist_7 = handler.splitPath(path_7, '/');
	auto pathlist_8 = handler.splitPath(path_8, '/');
	auto pathlist_9 = handler.splitPath(path_9, '/');

	ASSERT_EQ(pathlist_1.size(), 1);
	ASSERT_EQ(pathlist_2.size(), 1);
	ASSERT_EQ(pathlist_3.size(), 1);
	ASSERT_EQ(pathlist_4.size(), 1);
	ASSERT_EQ(pathlist_5.size(), 1);
	ASSERT_EQ(pathlist_6.size(), 2);
	ASSERT_EQ(pathlist_7.size(), 2);
	ASSERT_EQ(pathlist_8.size(), 3);
	ASSERT_EQ(pathlist_9.size(), 3);

	int j = 2;
};