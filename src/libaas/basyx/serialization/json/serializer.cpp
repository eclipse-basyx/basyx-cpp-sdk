#include <basyx/serialization/json/serializer_fwd.h>

#include <basyx/submodel.h>

#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>

namespace basyx::serialization::json 
{

void serialize_helper(json_t & json, const MultiLanguageProperty & multiLangProperty)
{
	serialize_submodelelement_helper(json, multiLangProperty);
	//serialize_helper(json, static_cast<const SubmodelElement&>(multiLangProperty));

	if (!multiLangProperty.get_value().empty())
		json["value"] = serialize(multiLangProperty.get_value());

	if (multiLangProperty.get_value_id())
		json["valueId"] = serialize(*multiLangProperty.get_value_id());
};

template<typename T>
inline void serialize_submodelelement(json_t & json, const SubmodelElement & submodelElement)
{
	serialize_helper(json, static_cast<const T&>(submodelElement));
};

void serialize_helper(json_t & json, const SubmodelElementCollection & collection)
{
	serialize_submodelelement_helper(json, collection);

	json_t value = json_t::array();

	for (const auto & element : collection) {
		value.emplace_back(serialize(*element));
	};

	if (value.size() > 0)
		json["value"] = value;
};


void serialize_helper(json_t & json, const Submodel & submodel)
{
	serialize_helper_h<Identifiable>(json, submodel);
	serialize_helper_h<HasSemantics>(json, submodel);
	serialize_helper_h<HasKind>(json, submodel);
	serialize_helper_h<modeltype_base>(json, submodel);

	json_t submodelElements = json_t::array();

	for (const auto & element : submodel.get_submodel_elements()) {
		submodelElements.emplace_back(serialize(*element));
	};

	if (submodelElements.size() > 0)
		json["submodelElements"] = submodelElements;
};




};