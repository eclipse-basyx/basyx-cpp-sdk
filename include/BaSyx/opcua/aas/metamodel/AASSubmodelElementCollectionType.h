/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_SUBMODEL_ELEMENT_COLLECTION_TYPE_H
#define AAS_SUBMODEL_ELEMENT_COLLECTION_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>

#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASSubmodelElementCollectionType
				{
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASSubmodelElementCollectionType";
						static constexpr const char DisplayName[] = "AASSubmodelElementCollectionType";
						static constexpr const char Description[] = "AASSubmodelElementCollectionType";
						static constexpr const char NodeHandle[] = "AASSubmodelElementCollectionType";

						static constexpr const char BrowseText_AllowDuplicates[] = "PropertyType::AllowDuplicates";
						static constexpr const char DisplayName_AllowDuplicates[] = "AllowDuplicates";
						static constexpr const char Description_AllowDuplicates[] = "AASSubmodelElementCollectionType::PropertyType::AllowDuplicates";
						static constexpr const char NodeHandle_AllowDuplicates[] = "AASSubmodelElementCollectionType::PropertyType::AllowDuplicates";

						static constexpr const char BrowseText_SubmodelElement[] = "AASSubmodelElementType::SubmodelElement";
						static constexpr const char DisplayName_SubmodelElement[] = "SubmodelElement";
						static constexpr const char Description_SubmodelElement[] = "AASSubmodelElementCollectionType::AASSubmodelElementType::SubmodelElement";
						static constexpr const char NodeHandle_SubmodelElement[] = "AASSubmodelElementCollectionType::AASSubmodelElementType::SubmodelElement";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASSubmodelElementCollectionType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId allowDuplicates(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_AllowDuplicates);
					NodeId subModelElement(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_SubmodelElement);

					status = services.addObjectTypeNode(
						getNodeId(t_ns),
						AASSubmodelElementType::getNodeId(t_ns),
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
						VariableAttributes(UA_TYPES_STRING, AttrNames::Description_AllowDuplicates, AttrNames::Description_AllowDuplicates, "en-US")
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
						VariableAttributes(UA_TYPES_STRING, AttrNames::Description_SubmodelElement, AttrNames::Description_SubmodelElement, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(subModelElement, UA_NODECLASS_OBJECT);
				}
			}
		}
	}
}
#endif