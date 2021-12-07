/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_REFERENCE_ELEMENT_TYPE_H
#define AAS_REFERENCE_ELEMENT_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>
#include <BaSyx/opcua/aas/metamodel/AASReferenceType.h>



namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASReferenceElementType
				{
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASReferenceElementType";
						static constexpr const char DisplayName[] = "AASReferenceElementType";
						static constexpr const char Description[] = "AASReferenceElementType";
						static constexpr const char NodeHandle[] = "AASReferenceElementType";

						static constexpr const char BrowseText_Reference[] = "AASReferenceType::Value";
						static constexpr const char DisplayName_Reference[] = "Value";
						static constexpr const char Description_Reference[] = "AASReferenceElementType::AASReferenceType::Value";
						static constexpr const char NodeHandle_Reference[] = "AASReferenceElementType::AASReferenceType::Value";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASReferenceElementType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId referenceValueId(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Reference);

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

					status = services.addObjectNode(
						referenceValueId,
						getNodeId(t_ns),
						AASReferenceType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_Reference),
						ObjectAttributes(AttrNames::DisplayName_Reference, AttrNames::Description_Reference, "en-US")
					);


					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(referenceValueId, UA_NODECLASS_VARIABLE);
				}
			}
		}
	}
}

#endif
