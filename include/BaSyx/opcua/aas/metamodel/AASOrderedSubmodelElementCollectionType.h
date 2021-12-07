/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_SUBMODEL_ORDERED_ELEMENT_COLLECTION_TYPE_H
#define AAS_SUBMODEL_ORDERED_ELEMENT_COLLECTION_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>

#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementCollectionType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				class AASOrderedSubmodelElementCollectionType
				{
				public:
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASOrderedSubmodelElementCollectionType";
						static constexpr const char DisplayName[] = "AASOrderedSubmodelElementCollectionType";
						static constexpr const char Description[] = "AASOrderedSubmodelElementCollectionType";
						static constexpr const char NodeHandle[] = "AASOrderedSubmodelElementCollectionType";

						static constexpr const char BrowseText_AllowDuplicates[] = "PropertyType::AllowDuplicates";
						static constexpr const char DisplayName_AllowDuplicates[] = "AllowDuplicates";
						static constexpr const char Description_AllowDuplicates[] = "AASOrderedSubmodelElementCollectionType::PropertyType::AllowDuplicates";
						static constexpr const char NodeHandle_AllowDuplicates[] = "AASOrderedSubmodelElementCollectionType::PropertyType::AllowDuplicates";

						static constexpr const char BrowseText_SubmodelElement[] = "AASSubmodelElementType::SubmodelElement";
						static constexpr const char DisplayName_SubmodelElement[] = "SubmodelElement";
						static constexpr const char Description_SubmodelElement[] = "AASOrderedSubmodelElementCollectionType::AASSubmodelElementType::SubmodelElement";
						static constexpr const char NodeHandle_SubmodelElement[] = "AASOrderedSubmodelElementCollectionType::AASSubmodelElementType::SubmodelElement";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASOrderedSubmodelElementCollectionType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					UA_StatusCode status;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId allowDuplicates(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_AllowDuplicates);
					NodeId subModelElement(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_SubmodelElement);

					status = services.addObjectTypeNode(
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
						NodeId::numeric(UA_NS0ID_HASSUBTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText),
						ObjectTypeAttributes(AttrNames::DisplayName, AttrNames::Description, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						allowDuplicates,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_AllowDuplicates),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_AllowDuplicates, AttrNames::Description_AllowDuplicates, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(allowDuplicates, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						subModelElement,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_SubmodelElement),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_SubmodelElement, AttrNames::Description_SubmodelElement, "en-US")
					);

					if (UA_STATUSCODE_GOOD != status) {
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(subModelElement, UA_NODECLASS_VARIABLE);
				}
			}
		}
	}
}
#endif