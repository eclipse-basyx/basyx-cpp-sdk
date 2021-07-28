#ifndef BASYX_SUBMODEL_ENUMERATIONS_REFERABLEELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_REFERABLEELEMENTS_H

#include <string>

namespace basyx {
namespace submodel {

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
    SubmodelElementCollection,
    View,
};

class ReferableElements_
{
public:
    static ReferableElements from_string(const std::string & name);
    static const char * to_string(ReferableElements value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_REFERABLEELEMENTS_H */
