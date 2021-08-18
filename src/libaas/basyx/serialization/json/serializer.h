#pragma once

#include <nlohmann/json.hpp>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/property.h>

#include <basyx/reference.h>
#include <basyx/key.h>

namespace basyx::serialization::json
{
	using json_t = nlohmann::json;

	template<typename T>
	inline json_t serialize(const T& t);


	inline void serialize_helper(json_t & json, const Key & key)
	{
		json["type"] = key.get_type();
		json["idType"] = static_cast<int>(key.get_id_type());
		json["local"] = true;
		json["value"] = key.get_value();
	};

	inline void serialize_helper(json_t & json, const Reference & reference)
	{
		auto keyList = json_t::array();

		for (std::size_t i = 0; i < reference.size(); ++i)
		{
			keyList.emplace_back(serialize(reference.get_key(i)));
		};

		json["keys"] = std::move(keyList);
	};

	inline void serialize_helper(json_t & json, const langstringset_t & langstrings)
	{
		json = json_t::array();

		for (const auto langstring : langstrings) {
			json.emplace_back(json_t{ 
				{"language", langstring.get_code().to_string() },
				{"text", langstring.get_value().to_string() }
			});
		}
	};

	template<typename T>
	inline void serialize_helper(json_t & json, const T & t) {};

	template<>
	inline void serialize_helper(json_t & json, const HasSemantics & hasSemantics)
	{
		if(hasSemantics.semanticId)
			json["semanticId"] = serialize(*hasSemantics.semanticId);
	};

	template<>
	inline void serialize_helper(json_t & json, const Referable & referable)
	{
		json["idShort"] = referable.get_id_short().to_string();

		if (referable.get_category())
			json["category"] = *referable.get_category();

		if (referable.get_description())
			json["description"] = serialize(*referable.get_description());

		if (referable.get_displayname())
			json["displayName"] = serialize(*referable.get_displayname());
	};

	template<>
	inline void serialize_helper(json_t & json, const modeltype_base & modelType)
	{
		json["modeltype"] = json_t{ {"name", ModelTypes_::to_string(modelType.get_model_type()) } };
	};


	inline void serialize_submodelelement_helper(json_t & json, const SubmodelElement & submodelElement)
	{
		serialize_helper<Referable>(json, submodelElement);
		serialize_helper<HasSemantics>(json, submodelElement);
		serialize_helper<modeltype_base>(json, submodelElement);
	};

	template<>
	inline void serialize_helper(json_t & json, const MultiLanguageProperty & multiLangProperty)
	{
		serialize_submodelelement_helper(json, multiLangProperty);
		//serialize_helper(json, static_cast<const SubmodelElement&>(multiLangProperty));
		
		if(!multiLangProperty.get_value().empty())
			json["value"] = serialize( multiLangProperty.get_value() );

		if (multiLangProperty.get_value_id())
			json["valueId"] = serialize(*multiLangProperty.get_value_id());
	};

	template<typename T>
	inline void serialize_helper_property(json_t & json, const Property<T> & property)
	{
		serialize_submodelelement_helper(json, property);
		//serialize_helper(json, static_cast<const SubmodelElement&>(multiLangProperty));

		if (property.get_value())
			json["value"] = *property.get_value();

		if (property.get_value_id())
			json["valueId"] = serialize(*property.get_value_id());

		json["valueType"] = property.get_value_type().to_string();
	};

	template<>
	inline void serialize_helper(json_t & json, const SubmodelElementCollection & collection)
	{
		serialize_submodelelement_helper(json, collection);

		json_t value = json_t::array();

		//auto & heh = collection.begin();

		for (const auto & element : collection) {
			value.emplace_back(serialize(*element));
		};

		if (value.size() > 0)
			json["value"] = value;
	};

	template<typename T>
	inline void serialize_submodelelement(json_t & json, const SubmodelElement & submodelElement)
	{
		serialize_helper<T>(json, static_cast<const T&>(submodelElement));
	};

	inline void serialize_helper(json_t & json, const SubmodelElement & submodelElement)
	{
		auto modeltype = submodelElement.get_model_type();

		switch (modeltype)
		{
		case ModelTypes::MultiLanguageProperty:
			return serialize_submodelelement<MultiLanguageProperty>(json, submodelElement);
		case ModelTypes::Property:
			//submodelElement.serialize_json(json);
			return;
		case ModelTypes::SubmodelElementCollection:
			return serialize_submodelelement<SubmodelElementCollection>(json, submodelElement);

			//return serialize_helper<MultiLanguageProperty>(json, static_cast<const MultiLanguageProperty&>(submodelElement));
		};
	};

	template <typename T>
	inline json_t serialize(const T& t)
	{
		json_t json;
		serialize_helper(json, t);

		return json;
	}
};