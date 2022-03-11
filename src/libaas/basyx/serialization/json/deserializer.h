#pragma once

#include <basyx/serialization/json/types.h>

#include <basyx/assetadministrationshell.h>
#include <basyx/submodel.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/submodelelement.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/multilanguageproperty.h>

#include <basyx/referable.h>
#include <basyx/identifier.h>

//#include <basyx/serialization/json/serializer_fwd.h>

#include <basyx/haskind.h>
#include <basyx/key.h>

namespace basyx::serialization::json
{
	using json_t = nlohmann::json;

	Key deserialize_key(const json_t & json);
	Reference deserialize_reference(const json_t & json);
	langstringset_t deserialize_langstrings(const json_t & json);
	Identifier deserialize_identifier(const json_t & json);
	MultiLanguageProperty deserialize_multilang_prop(const json_t & json);
	std::unique_ptr<property_base> deserialize_property(const json_t & json);
	std::unique_ptr<SubmodelElement> deserialize_submodelelement(const json_t & json);
	SubmodelElementCollection deserialize_submodelelement_collection(const json_t & json);
	Submodel deserialize_submodel(const json_t & json);
	AssetAdministrationShell deserialize_aas(const json_t & json);
};