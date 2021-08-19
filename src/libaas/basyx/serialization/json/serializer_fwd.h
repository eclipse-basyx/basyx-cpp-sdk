#pragma once

#include <nlohmann/json.hpp>

namespace basyx
{
	class Key;
	class Reference;
	class langstringset_t;
	class HasSemantics;
	class Referable;
	class modeltype_base;
	class MultiLanguageProperty;
	class SubmodelElementCollection;
	class SubmodelElement;

	template<typename T>
	class Property;
};


namespace basyx::serialization::json
{
	using json_t = nlohmann::json;

	inline void serialize_helper(json_t & json, const Key & key);
	inline void serialize_helper(json_t & json, const Reference & reference);
	inline void serialize_helper(json_t & json, const langstringset_t & langstrings);
	inline void serialize_helper(json_t & json, const HasSemantics & hasSemantics);
	inline void serialize_helper(json_t & json, const Referable & referable);
	inline void serialize_helper(json_t & json, const modeltype_base & modelType);
	inline void serialize_helper(json_t & json, const MultiLanguageProperty & multiLangProperty);
	inline void serialize_helper(json_t & json, const SubmodelElementCollection & collection);
	inline void serialize_helper(json_t & json, const SubmodelElement & submodelElement);
	
	template<typename T>
	void serialize_helper(json_t & json, const Property<T> & t);
};