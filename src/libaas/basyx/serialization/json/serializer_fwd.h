#pragma once

#include <nlohmann/json.hpp>

namespace basyx
{
	class Key;
	class Reference;
	class langstringset_t;
	class HasSemantics;
	class HasKind;
	class Referable;
	class modeltype_base;
	class MultiLanguageProperty;
	class SubmodelElementCollection;
	class SubmodelElement;
	class Submodel;

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
	inline void serialize_helper(json_t & json, const HasKind & hasKind);
	inline void serialize_helper(json_t & json, const Referable & referable);
	inline void serialize_helper(json_t & json, const modeltype_base & modelType);
	void serialize_helper(json_t & json, const Submodel & submodel);
	void serialize_helper(json_t & json, const MultiLanguageProperty & multiLangProperty);
	void serialize_helper(json_t & json, const SubmodelElementCollection & collection);
	//void serialize_helper(json_t & json, const SubmodelElement & submodelElement);
	
	template<typename T>
	void serialize_helper(json_t & json, const Property<T> & t);
};