#ifndef BASYX_SUBMODEL_ENUMERATIONS_REFERABLEELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_REFERABLEELEMENTS_H

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {

enum class ReferableElements {
    AccessPermissionRule,
    AnnotatedRelationshipElemenBasicEvent,
    Blob,
    Capability,
    ConceptDictionary,
    DataElement,
    File,
    Entity,
    Event,
    MultiLanguageProperty,
    Operation,
    Property,
    Range,
    ReferenceElement,
    RelationshipElement,
    SubmodelElement,
	SubmodelElementList,
	SubmodelElementStruct
};

class ReferableElements_
{
public:
    static ReferableElements from_string(util::string_view name);
    static const char * to_string(ReferableElements value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_REFERABLEELEMENTS_H */
