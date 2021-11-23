#include <basyx/enums/SubmodelElements.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

using enum_pair_t = std::pair<const char*, SubmodelElements>;

static const std::array<enum_pair_t, 22> string_to_enum = 
{
    std::make_pair("AccessPermissionRule,",  SubmodelElements::AccessPermissionRule),
	std::make_pair("AnnotatedRelationshipElement,",  SubmodelElements::AnnotatedRelationshipElement),
	std::make_pair("Asset,",  SubmodelElements::Asset),
	std::make_pair("AssetAdministrationShell,",  SubmodelElements::AssetAdministrationShell),
	std::make_pair("BasicEvent,",  SubmodelElements::BasicEvent),
	std::make_pair("Blob,",  SubmodelElements::Blob),
	std::make_pair("Capability,",  SubmodelElements::Capability),
	std::make_pair("ConceptDescription,",  SubmodelElements::ConceptDescription),
	std::make_pair("DataElement,",  SubmodelElements::DataElement),
	std::make_pair("Entity,",  SubmodelElements::Entity),
	std::make_pair("Event,",  SubmodelElements::Event),
	std::make_pair("File,",  SubmodelElements::File),
	std::make_pair("MultiLanguageProperty,",  SubmodelElements::MultiLanguageProperty),
	std::make_pair("Operation,",  SubmodelElements::Operation),
	std::make_pair("Property,",  SubmodelElements::Property),
	std::make_pair("Range,",  SubmodelElements::Range),
	std::make_pair("ReferenceElement,",  SubmodelElements::ReferenceElement),
	std::make_pair("RelationshipElement,",  SubmodelElements::RelationshipElement),
	std::make_pair("Submodel,",  SubmodelElements::Submodel),
	std::make_pair("SubmodelElement,",  SubmodelElements::SubmodelElement),
	std::make_pair("SubmodelElementList,",  SubmodelElements::SubmodelElementList),
	std::make_pair("SubmodelElementStruct",  SubmodelElements::SubmodelElementStruct),
};

SubmodelElements SubmodelElements_::from_string(util::string_view name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * SubmodelElements_::to_string(SubmodelElements value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

