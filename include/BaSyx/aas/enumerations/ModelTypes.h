/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_ENUMERATIONS_MODELTYPES_H
#define BASYX_SUBMODEL_ENUMERATIONS_MODELTYPES_H

#include <string>

namespace basyx {
namespace aas {

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
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_MODELTYPES_H */
