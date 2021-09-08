#include <gtest/gtest.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <type_traits>

#include <pugixml.hpp>

#include <basyx/submodelelement/multilanguageproperty.h>

#include <util/string_view/string_view.hpp>

using namespace basyx;

class XmlTestMLP : public ::testing::Test
{
protected:
	using xml_node_t = pugi::xml_node;
protected:
	// Test settings

	// Test variables

	basyx::Key key_from_xml(const xml_node_t & node)
	{
		util::string_view keyElement = node.attribute("type").value();
		util::string_view idType = node.attribute("idType").value();
		util::string_view value = node.child_value();

		return Key{
			KeyElements_::from_string(keyElement),
			value,
			KeyType_::from_string(idType)
		};
	};

	basyx::Reference reference_from_xml(const xml_node_t & node)
	{
		Reference::keyList_t keyList;

		for (const auto & entry : node.child("aas:keys").children()) {
			keyList.emplace_back(key_from_xml(entry));
		};

		return Reference(std::move(keyList));
	};

	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(XmlTestMLP, Test_MultiLanguageProperty)
{
	std::string xml = R"(<?xml version="1.0" encoding="UTF-8"?>
                <aas:multiLanguageProperty>
                  <aas:idShort>mlp</aas:idShort>
                  <aas:category>CONSTANT</aas:category>
                  <aas:kind>Instance</aas:kind>
                  <aas:semanticId>
                    <aas:keys>
                      <aas:key type="ConceptDescription" local="false" idType="IRDI">0173-1#02-AAO677#002</aas:key>
                    </aas:keys>
                  </aas:semanticId>
                  <aas:value>
                    <aas:langString lang="en">example</aas:langString>
                    <aas:langString lang="de">beispiel</aas:langString>
                  </aas:value>
                  <aas:valueId>
                    <aas:keys />
                  </aas:valueId>
                </aas:multiLanguageProperty>
)";
	util::string_view view = xml;
	pugi::xml_document doc;
	auto result = doc.load_buffer_inplace((void*)view.data(), view.size());

	auto root = doc.first_child();
	ASSERT_TRUE(root);
	ASSERT_EQ( util::string_view( root.name() ), "aas:multiLanguageProperty");

	util::string_view idShort = root.child("aas:idShort").child_value();

	basyx::MultiLanguageProperty mlp(idShort);

	// Extract values

	for (const auto & entry : root.child("aas:value").children()) {
		util::string_view lang = entry.attribute("lang").value();
		util::string_view text = entry.child_value();

		mlp.get_value().add(lang, text);
	}

	auto ref = reference_from_xml(root.child("aas:semanticId"));

	mlp.setSemanticId(std::move(ref));

	int j = 2;
};


