#include <basyx/enums/ReferableElements.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

using enum_pair_t = std::pair<const char*, ReferableElements>;

static const std::array<enum_pair_t, 18> string_to_enum = 
{
    std::make_pair("AccessPermissionRule,", ReferableElements::AccessPermissionRule),
	std::make_pair("AnnotatedRelationshipElemenBasicEvent,", ReferableElements::AnnotatedRelationshipElemenBasicEvent),
	std::make_pair("Blob,", ReferableElements::Blob),
	std::make_pair("Capability,", ReferableElements::Capability),
	std::make_pair("ConceptDictionary,", ReferableElements::ConceptDictionary),
	std::make_pair("DataElement,", ReferableElements::DataElement),
	std::make_pair("File,", ReferableElements::File),
	std::make_pair("Entity,", ReferableElements::Entity),
	std::make_pair("Event,", ReferableElements::Event),
	std::make_pair("MultiLanguageProperty,", ReferableElements::MultiLanguageProperty),
	std::make_pair("Operation,", ReferableElements::Operation),
	std::make_pair("Property,", ReferableElements::Property),
	std::make_pair("Range,", ReferableElements::Range),
	std::make_pair("ReferenceElement,", ReferableElements::ReferenceElement),
	std::make_pair("RelationshipElement,", ReferableElements::RelationshipElement),
	std::make_pair("SubmodelElement,", ReferableElements::SubmodelElement),
	std::make_pair("SubmodelElementList", ReferableElements::SubmodelElementList),
	std::make_pair("SubmodelElementStruct", ReferableElements::SubmodelElementStruct)
};

ReferableElements ReferableElements_::from_string(util::string_view name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * ReferableElements_::to_string(ReferableElements value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

