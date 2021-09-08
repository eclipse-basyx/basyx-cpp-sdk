#ifndef BASYX_SUBMODEL_ENUMERATIONS_KEYELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_KEYELEMENTS_H

#include <util/string_view/string_view.hpp>

namespace basyx {

enum class KeyElements {
    GlobalReference,
    FragmentReference,
    AccessPermissionRule,
    AnnotatedRelationshipElement,
    BasicEvent,
    Blob,
    Capability,
    ConceptDictionary,
    DataElement,
    Entity,
    Event,
    File,
    MultiLanguageProperty,
    Operation,
    OperationVariable,
    Property,
    Range,
    ReferenceElement,
    RelationshipElement,
    SubmodelElement,
    SubmodelElementCollection,
    View,
    Unknown,
    Asset,
    AssetAdministrationShell,
    ConceptDescription,
    Submodel,
};

class KeyElements_
{
public:
    static KeyElements from_string(util::string_view name);
    static const char * to_string(KeyElements value);
};

}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_KEYELEMENTS_H */
