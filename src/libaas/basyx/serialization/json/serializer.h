#pragma once

#include <basyx/serialization/json/types.h>

#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/property.h>

#include <basyx/serialization/json/serializer_fwd.h>

#include <basyx/haskind.h>

namespace basyx::serialization::json
{
	using json_t = nlohmann::json;

	template <typename T>
	inline json_t serialize(const T& t)
	{
		json_t json;

		if constexpr (std::is_base_of<serializable_base, T>::value)
		{
			auto & serializable = static_cast<const serializable_base&>(t);
			serializable.serialize_json(json);
		}
		else
		{
			serialize_helper(json, t);
		}

		return json;
	};

	void serialize_helper(json_t & json, const MultiLanguageProperty & multiLangProperty);

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

	inline void serialize_helper(json_t & json, const HasSemantics & hasSemantics)
	{
		if(hasSemantics.getSemanticId())
			json["semanticId"] = serialize(*hasSemantics.getSemanticId());
	};

	inline void serialize_helper(json_t & json, const HasKind & hasKind)
	{
		json["kind"] = ModelingKind_::to_string( hasKind.kind );
	};

	inline void serialize_helper(json_t & json, const modeltype_base & modelType)
	{
		json["modeltype"] = json_t{ {"name", ModelTypes_::to_string(modelType.get_model_type()) } };
	};


	template<typename T, typename U>
	inline void serialize_helper_h(json_t & json, const U & element)
	{
		serialize_helper(json, static_cast<const T&>(element));
	}

	inline void serialize_submodelelement_helper(json_t & json, const SubmodelElement & submodelElement)
	{
		serialize_helper_h<Referable>(json, submodelElement);
		serialize_helper_h<HasSemantics>(json, submodelElement);
		serialize_helper_h<modeltype_base>(json, submodelElement);
	};

	template<typename T>
	inline void serialize_helper(json_t & json, const Property<T> & property)
	{
		serialize_submodelelement_helper(json, property);
		//serialize_helper(json, static_cast<const SubmodelElement&>(multiLangProperty));

		if (property.get_value())
			json["value"] = *property.get_value();

		if (property.get_value_id())
			json["valueId"] = serialize(*property.get_value_id());

		json["valueType"] = property.get_value_type().to_string();
	};


	inline json_t serialize(const serializable_base & serializable)
	{
		json_t json;

		serializable.serialize_json(json);

		return json;
	};
};