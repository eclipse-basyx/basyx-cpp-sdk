#include "deserializer.h"

namespace basyx::serialization::json
{
	ModelTypes extract_modeltype(const json_t & json)
	{
		return ModelTypes_::from_string(json["modelType"]["name"]);
	};


	Key deserialize_key(const json_t & json)
	{
		std::string id_type = json["idType"];
		std::string key_element = json["type"];
		std::string value = json["value"];

		return Key{KeyElements_::from_string(key_element), value, KeyType_::from_string(id_type)};
	};

	Reference deserialize_reference(const json_t & json)
	{
		Reference::keyList_t keyList;

		for (const auto & key : json["keys"]) {
			keyList.emplace_back(deserialize_key(key));
		}

		return Reference{ std::move(keyList) };
	};

	langstringset_t deserialize_langstrings(const json_t & json)
	{
		langstringset_t langstrings;

		for (const auto & entry : json) {
			std::string lang = entry["language"];
			std::string value = entry["text"];
			langstrings.add(lang, value);
		};

		return langstrings;
	};

	Identifier deserialize_identifier(const json_t & json)
	{
		std::string identifier = json["id"];
		std::string idType = json["idType"];

		return Identifier{KeyType_::from_string(idType), identifier};
	};

	template<typename Obj>
	void deserialize_referable(const json_t & json, Obj & obj)
	{
		if(json.contains("category"))
			obj.setCategory((std::string)json["category"]);
	
		if(json.contains("description"))
			obj.setDescription(deserialize_langstrings(json["description"]));
	};

	MultiLanguageProperty deserialize_multilang_prop(const json_t & json)
	{
		std::string idShort = json["idShort"];
		auto mlp = MultiLanguageProperty{ std::move(idShort) };
		mlp.set_value(deserialize_langstrings(json["value"]));
		deserialize_referable(json, mlp);

		return mlp;
	};

	template<typename value_t>
	std::unique_ptr<property_base> build_property(std::string idShort, const json_t & value) {
			return nullptr;
	};

	template<>
	std::unique_ptr<property_base> build_property<int>(std::string idShort, const json_t & value) {
		if (value.is_number())
			return std::make_unique<Property<int>>(std::move(idShort), value);
		else if (value.is_string())
			return std::make_unique<Property<int>>(std::move(idShort), std::stoi(value.get<std::string>()));
		else
			return nullptr;
	};

	template<>
	std::unique_ptr<property_base> build_property<std::string>(std::string idShort, const json_t & value) {
		if (value.is_string())
			return std::make_unique<Property<std::string>>(std::move(idShort), value);
		else
			return nullptr;
	};

	std::unique_ptr<property_base> deserialize_property(const json_t & json)
	{
		std::string idShort = json["idShort"];
		const auto & value = json["value"];
		std::string valueType = json["valueType"];

		std::unique_ptr<property_base> prop;

		if (valueType == "integer")	{
			prop = build_property<int>(std::move(idShort), value);
		}
		else if (valueType == "string") {
			prop = build_property<std::string>(std::move(idShort), value);
		}
		else {
			return nullptr;
		};

		deserialize_referable(json, *prop);

		return prop;
	};

	std::unique_ptr<SubmodelElement> deserialize_submodelelement(const json_t & json)
	{
		auto modelType = extract_modeltype(json);

		std::unique_ptr<SubmodelElement> element;

		switch (modelType)
		{
		case ModelTypes::Property:
			element = deserialize_property(json);
			break;
		case ModelTypes::MultiLanguageProperty:
			element = std::make_unique<MultiLanguageProperty>(deserialize_multilang_prop(json));
			break;
		case ModelTypes::SubmodelElementCollection:
			element = std::make_unique<SubmodelElementCollection>(deserialize_submodelelement_collection(json));
			break;
		};
		
		return element;
	};

	SubmodelElementCollection deserialize_submodelelement_collection(const json_t & json)
	{
		std::string idShort = json["idShort"];

		SubmodelElementCollection col(idShort);
		
		for (const auto & value : json["value"]) {
			auto element = deserialize_submodelelement(value);
			col.getSubmodelElements().add(std::move(element));
		};

		return col;
	};

	Submodel deserialize_submodel(const json_t & json)
	{
		std::string idShort = json["idShort"];
		auto identifier = deserialize_identifier(json["identification"]);

		Submodel submodel(std::move(idShort), std::move(identifier));

		deserialize_referable(json, submodel);

		for (const auto & element : json["submodelElements"]) {
			submodel.getSubmodelElements().add(deserialize_submodelelement(element));
		};

		return submodel;
	};

	AssetAdministrationShell deserialize_aas(const json_t & json)
	{
		std::string idShort = json["idShort"];
		auto identifier = deserialize_identifier(json["identification"]);

		AssetAdministrationShell aas(idShort, identifier, basyx::AssetInformation(AssetKind::Instance));

		deserialize_referable(json, aas);

		for (const auto & submodel : json["submodels"]) {
			aas.getSubmodels().add(deserialize_submodel(submodel));
		};

		return aas;
	};
};
