#ifndef BASYX_SUBMODEL_ENUMERATIONS_SUBMODELELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_SUBMODELELEMENTS_H

#include <util/string_view/string_view.hpp>

namespace basyx {

enum class SubmodelElements {
	AccessPermissionRule,
	AnnotatedRelationshipElement,
	Asset,
	AssetAdministrationShell,
	BasicEvent,
	Blob,
	Capability,
	ConceptDescription,
	DataElement,
	Entity,
	Event,
	File,
	MultiLanguageProperty,
	Operation,
	Property,
	Range,
	ReferenceElement,
	RelationshipElement,
	Submodel,
	SubmodelElement,
	SubmodelElementList,
	SubmodelElementStruct
};

class SubmodelElements_
{
public:
    static SubmodelElements from_string(util::string_view name);
    static const char * to_string(SubmodelElements value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_SUBMODELELEMENTS_H */
