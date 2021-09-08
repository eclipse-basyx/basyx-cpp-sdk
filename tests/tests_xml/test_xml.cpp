#include <gtest/gtest.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <type_traits>

#include <pugixml.hpp>

#include <util/string_view/string_view.hpp>

using namespace basyx;

class XmlTest : public ::testing::Test
{
protected:
	// Test settings

	// Test variables
	std::string xml = R"( 
<?xml version="1.0" encoding="UTF-8"?>
<root test="1234">
    <nodes>
        <node id="1">
          <content int="5" float="2.34" string="test">node1234</content>
        </node>
        <node id="2" int="1234" float="5.43">
        </node>
		<extranode id="3" extra="extra" />
    </nodes>
</root> )";

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};


TEST_F(XmlTest, Test_1)
{
	util::string_view view = xml;
	pugi::xml_document doc;
	auto result = doc.load_buffer_inplace((void*)view.data(), view.size());

	util::string_view test_val = doc.child("root").attribute("test").value();
	ASSERT_EQ(test_val, "1234");

	auto nodes = doc.child("root").child("nodes");

	ASSERT_FALSE(nodes.empty());
};

TEST_F(XmlTest, ForLoop)
{
	util::string_view view = xml;
	pugi::xml_document doc;
	auto result = doc.load_buffer_inplace((void*)view.data(), view.size());

	auto nodes = doc.child("root").child("nodes");

	// Range based for
	{
		int n = 0;
		for (const auto & node : nodes.children()) { 
			spdlog::info("Node: {} Id: {}", node.name(), node.attribute("id").value());
			if (node.child("content")) {
				auto content = node.child("content");
				spdlog::info("    Content: int: {} float: {} string: {} text: {}",
					content.attribute("int").as_int(),
					content.attribute("float").as_float(),
					content.attribute("string").as_string(),
					content.child_value()
				);
			}
			++n; 
		};
		ASSERT_EQ(n, 3);
	}

	{
		int n = 0;
		for (const auto & node : nodes.children("node")) { 
			spdlog::info("Node: {} Id: {}", node.name(), node.attribute("id").value());
			++n; 
		};
		ASSERT_EQ(n, 2);
	}
};

TEST_F(XmlTest, XPath)
{
	util::string_view view = xml;
	pugi::xml_document doc;
	auto result = doc.load_buffer_inplace((void*)view.data(), view.size());

	auto root = doc.child("root");

	auto nodes = root.select_nodes("/root/nodes/node");
	ASSERT_EQ(nodes.size(), 2);

	auto node_non_existing = root.select_node("/root/nodes/node[@id='3']");
	ASSERT_FALSE(node_non_existing);

	auto node = root.select_node("/root/nodes/node[@id='2']");
	ASSERT_TRUE(node);
	ASSERT_EQ(node.node().attribute("int").as_int(), 1234);
	int j = 2;
};


