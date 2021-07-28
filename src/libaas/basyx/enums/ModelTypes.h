#ifndef BASYX_SUBMODEL_ENUMERATIONS_MODELTYPES_H
#define BASYX_SUBMODEL_ENUMERATIONS_MODELTYPES_H

#include <string>

namespace basyx {

enum class ModelTypes {
    Asset,
    AssetAdministrationShell,
    ConceptDescription,
    Submodel,
    AccessPermissionRule,
    AnnotatedRelationshipElement,
    BasicEvent,
    Blob,
    Capability,
    ConceptDictionary,
    DataElement,
    File,
    Entity,
    Event,
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
    GlobalReference,
    FragmentReference,
    Constraint,
    Formula,
    Qualifier,
};

class ModelTypes_
{
public:
    static ModelTypes from_string(const std::string & name);
    static const char * to_string(ModelTypes value);
};


}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_MODELTYPES_H */
