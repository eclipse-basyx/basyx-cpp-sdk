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
	class Identifiable;
	class Identifier;
	class modeltype_base;
	class MultiLanguageProperty;
	class ReferenceElement;
	class AdministrativeInformation;
	class SubmodelElementCollection;
	class RelationshipElement;
	class AnnotatedRelationshipElement;
	class Capability;
	class SubmodelElement;
	class BasicEvent;
	class Submodel;
	class File;
	class Blob;

	template<typename T>
	class Property;
};


namespace basyx::serialization::json
{
	using json_t = nlohmann::json;

	void serialize_helper(json_t & json, const Key &);
	void serialize_helper(json_t & json, const Reference &);
	inline void serialize_helper(json_t & json, const langstringset_t &);
	inline void serialize_helper(json_t & json, const HasSemantics &);
	inline void serialize_helper(json_t & json, const HasKind &);
	inline void serialize_helper(json_t & json, const modeltype_base &);
	void serialize_helper(json_t & json, const Identifier &);
	void serialize_helper(json_t & json, const AdministrativeInformation&);
	void serialize_helper(json_t & json, const Referable&);
	void serialize_helper(json_t & json, const Identifiable&);
	void serialize_helper(json_t & json, const Submodel&);
	void serialize_helper(json_t & json, const ReferenceElement&);
	void serialize_helper(json_t & json, const RelationshipElement&);
	void serialize_helper(json_t & json, const AnnotatedRelationshipElement&);
	void serialize_helper(json_t & json, const MultiLanguageProperty&);
	void serialize_helper(json_t & json, const Capability&);
	void serialize_helper(json_t & json, const File&);
	void serialize_helper(json_t & json, const BasicEvent&);
	void serialize_helper(json_t & json, const Blob&);
	void serialize_helper(json_t & json, const SubmodelElementCollection&);
	
	template<typename T>
	void serialize_helper(json_t & json, const Property<T>& prop);
};