#ifndef BASYX_SUBMODEL_ENUMERATIONS_CONVERSIONS_H
#define BASYX_SUBMODEL_ENUMERATIONS_CONVERSIONS_H

#include <BaSyx/submodel/enumerations/KeyElements.h>
#include <BaSyx/submodel/enumerations/ModelTypes.h>

namespace basyx {
namespace submodel {
namespace enums {

inline KeyElements convert_modeltype_to_keyelement(const ModelTypes modelType)
{
    switch (modelType) {
    case ModelTypes::Asset:
        return KeyElements::Asset;
    case ModelTypes::AssetAdministrationShell:
        return KeyElements::AssetAdministrationShell;
    case ModelTypes::ConceptDescription:
        return KeyElements::ConceptDescription;
    case ModelTypes::Submodel:
        return KeyElements::Submodel;
    case ModelTypes::AccessPermissionRule:
        return KeyElements::AccessPermissionRule;
    case ModelTypes::AnnotatedRelationshipElement:
        return KeyElements::AnnotatedRelationshipElement;
    case ModelTypes::BasicEvent:
        return KeyElements::BasicEvent;
    case ModelTypes::Blob:
        return KeyElements::Blob;
    case ModelTypes::Capability:
        return KeyElements::Capability;
    case ModelTypes::ConceptDictionary:
        return KeyElements::ConceptDictionary;
    case ModelTypes::DataElement:
        return KeyElements::DataElement;
    case ModelTypes::File:
        return KeyElements::File;
    case ModelTypes::Entity:
        return KeyElements::Entity;
    case ModelTypes::Event:
        return KeyElements::Event;
    case ModelTypes::MultiLanguageProperty:
        return KeyElements::MultiLanguageProperty;
    case ModelTypes::Operation:
        return KeyElements::Operation;
    case ModelTypes::OperationVariable:
        return KeyElements::OperationVariable;
    case ModelTypes::Property:
        return KeyElements::Property;
    case ModelTypes::Range:
        return KeyElements::Range;
    case ModelTypes::ReferenceElement:
        return KeyElements::ReferenceElement;
    case ModelTypes::RelationshipElement:
        return KeyElements::RelationshipElement;
    case ModelTypes::SubmodelElement:
        return KeyElements::SubmodelElement;
    case ModelTypes::SubmodelElementCollection:
        return KeyElements::SubmodelElementCollection;
    case ModelTypes::View:
        return KeyElements::View;
    case ModelTypes::GlobalReference:
        return KeyElements::GlobalReference;
    case ModelTypes::FragmentReference:
        return KeyElements::FragmentReference;
    case ModelTypes::Constraint:
        return KeyElements::Unknown;
    case ModelTypes::Formula:
        return KeyElements::Unknown;
    case ModelTypes::Qualifier:
        return KeyElements::Unknown;
    };
};

}
}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_CONVERSIONS_H */
