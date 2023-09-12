#include <basyx/serialization/json/serializer_fwd.h>

#include <basyx/key.h>
#include <basyx/reference.h>
#include <basyx/submodel.h>
#include <basyx/assetadministrationshell.h>

#include <basyx/submodelelement/blob.h>
#include <basyx/submodelelement/file.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/capability.h>
#include <basyx/submodelelement/referenceelement.h>
#include <basyx/submodelelement/relationshipelement.h>
#include <basyx/submodelelement/entity.h>
#include <basyx/submodelelement/basicevent.h>
#include <basyx/submodelelement/annotatedrelationshipelement.h>
#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>

namespace basyx::serialization::json 
{

void serialize_helper(json_t & json, const MultiLanguageProperty & multiLangProperty)
{
	serialize_submodelelement_helper(json, multiLangProperty);

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

void serialize_helper(json_t & json, const HasSemantics & hasSemantics)
{
	if (hasSemantics.getSemanticId())
		json["semanticId"] = serialize(*hasSemantics.getSemanticId());
};

void serialize_helper(json_t & json, const HasKind & hasKind)
{
	json["kind"] = ModelingKind_::to_string(hasKind.kind);
};

void serialize_helper(json_t & json, const modeltype_base & modelType)
{
	json["modelType"] = json_t{ {"name", ModelTypes_::to_string(modelType.get_model_type()) } };
};

void serialize_helper(json_t & json, const Key & key)
{
	json["type"] = KeyElements_::to_string(key.get_type());
	json["idType"] = KeyType_::to_string(key.get_id_type());
	json["local"] = false;
	json["value"] = key.get_value();
};

void serialize_helper(json_t & json, const Reference & reference)
{
	auto keyList = json_t::array();

	for (std::size_t i = 0; i < reference.size(); ++i)
	{
		keyList.emplace_back(serialize(reference.get_key(i)));
	};

	json["keys"] = std::move(keyList);
};

void serialize_helper(json_t & json, const Entity & entity)
{
	serialize_submodelelement_helper(json, entity);

	json["statements"] = json_t::array();

	if(entity.getGlobalAssetId())
		json["globalAssetId"] = serialize(*entity.getGlobalAssetId());

	if(entity.getSpecificAssetId())
		json["specificAssetIds"] = serialize(*entity.getSpecificAssetId());

};

void serialize_helper(json_t & json, const Referable & referable)
{
	serialize_helper_h<modeltype_base>(json, referable);

	json["idShort"] = referable.getIdShort().to_string();

	if (referable.getCategory())
		json["category"] = *referable.getCategory();

	if (referable.getDescription())
		json["description"] = serialize(*referable.getDescription());

	if (referable.getDisplayname())
		json["displayName"] = serialize(*referable.getDisplayname());
};

void serialize_helper(json_t & json, const langstringset_t & langstrings)
{
	json = json_t::array();

	for (const auto & langstring : langstrings) {
		json.emplace_back(json_t{
			{"language", langstring.get_code().to_string() },
			{"text", langstring.get_value().to_string() }
			});
	}
};

void serialize_helper(json_t & json, const SpecificAssetId & kvPair)
{
	serialize_helper_h<HasSemantics>(json, kvPair);

   json["key"] = kvPair.getName();

   json["value"] = kvPair.getValue().getId();

	json["subjectId"] = json_t();
	if(kvPair.getExternalSubjectId())
		json["subjectId"] = serialize(*kvPair.getExternalSubjectId());
}

void serialize_helper(json_t & json, const AssetAdministrationShell & aas)
{
	serialize_helper_h<Identifiable>(json, aas);
	//serialize_helper_h<HasDataSpecification>(json, aas);
	//serialize_helper_h<modeltype_base>(json, aas);

	if (aas.getDerivedFrom())
		json["derivedFrom"] = serialize(*aas.getDerivedFrom());

	auto submodels = json_t::array();
	for (const auto & submodel : aas.getSubmodels()) {
		submodels.emplace_back(serialize(*submodel));
	};

	json["submodels"] = std::move(submodels);

	json["assetInformation"] = serialize(aas.getAssetInformation());

	if(aas.getSecurity())
		// actually, ToDo: 
		// json["security"] = serialize(*aas.getSecurity());
		json["security"] = *aas.getSecurity();
};

void serialize_helper(json_t & json, const Capability & capability)
{
	serialize_submodelelement_helper(json, capability);
}

void serialize_helper(json_t & json, const AdministrativeInformation & administrativeInformation)
{
	auto & version = administrativeInformation.get_version();
	auto & revision = administrativeInformation.get_revision();

	if(version)
		json["version"] = *version;

	if(revision)
		json["revision"] = *revision;
};

void serialize_helper(json_t & json, const ReferenceElement & ref_element)
{
	serialize_submodelelement_helper(json, ref_element);

	if (ref_element.getValue())
		json["value"] = serialize(*ref_element.getValue());
}

void serialize_helper(json_t & json, const RelationshipElement& rel_element)
{
	serialize_submodelelement_helper(json, rel_element);

	json["first"] = serialize(rel_element.getFirst());
	json["second"] = serialize(rel_element.getSecond());
}

void serialize_helper(json_t & json, const AnnotatedRelationshipElement& rel_element)
{
	serialize_submodelelement_helper(json, rel_element);

	json["first"] = serialize(rel_element.getFirst());
	json["second"] = serialize(rel_element.getSecond());

	auto annotations = json_t::array();

	if (rel_element.getAnnotation())
		annotations.push_back(serialize(*rel_element.getAnnotation()));
	
	json["annotation"] = annotations;
}

void serialize_helper(json_t & json, const BasicEvent & basicEvent)
{
	serialize_submodelelement_helper(json, basicEvent);

	json["observed"] = serialize(basicEvent.getObserved());
}

void serialize_helper(json_t & json, const Blob & blob)
{
	serialize_submodelelement_helper(json, blob);

	// Todo: encode blob.getBlob() in base64
	json["value"] = "";

	json["mimeType"] = blob.getMimeType();
};

void serialize_helper(json_t & json, const File & file)
{
	serialize_submodelelement_helper(json, file);

	if (file.getValue())
		json["value"] = *file.getValue();
	else
		json["value"] = "";

	json["mimeType"] = file.getMimeType();
};


void serialize_helper(json_t & json, const Identifier & identifier)
{
   json = identifier.getId();
};

void serialize_helper(json_t & json, const Identifiable & identifiable)
{
	serialize_helper_h<Referable>(json, identifiable);

	json["identification"] = serialize(identifiable.getIdentification());

	if (identifiable.getAdministration())
		json["administration"] = serialize(*identifiable.getAdministration());
};

void serialize_helper(json_t & json, const SubmodelElementCollection & collection)
{
	serialize_submodelelement_helper(json, collection);

	json_t value = json_t::array();

	for (const auto & element : collection.getSubmodelElements()) {
		value.emplace_back(serialize(*element));
	};

	if (value.size() > 0)
		json["value"] = std::move(value);
};

void serialize_helper(json_t & json, const Submodel & submodel)
{
	serialize_helper_h<Identifiable>(json, submodel);
	serialize_helper_h<HasSemantics>(json, submodel);
	serialize_helper_h<HasKind>(json, submodel);

	json_t submodelElements = json_t::array();

	for (const auto & element : submodel.getSubmodelElements()) {
		submodelElements.emplace_back(serialize(*element));
	};

	if (submodelElements.size() > 0)
		json["submodelElements"] = submodelElements;
};


void serialize_helper(json_t & json, const AssetInformation & assetInf)
{
	json["assetKind"] = AssetKind_::to_string(assetInf.getAssetKind());
	
	if (assetInf.getGlobalAssetId())
		json["globalAssetId"] = serialize(*assetInf.getGlobalAssetId());

	auto specificAssetIds = json_t::array();
	for (const auto & assetId : assetInf.getSpecificAssetIds())
		specificAssetIds.emplace_back(serialize(assetId));
	json["specificAssetIds"] = specificAssetIds;

	if(assetInf.getDefaultThumbnail())
		json["thumbnail"] = serialize(*assetInf.getDefaultThumbnail());
}




};
