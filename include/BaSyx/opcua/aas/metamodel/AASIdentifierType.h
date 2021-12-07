/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_IDENTIFIER_TYPE_H
#define AAS_IDENTIFIER_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASIdentifierType
				{
					struct AttrNames
					{
						static constexpr const char InstanceName[] = "Identifier";
						static constexpr const char BrowseText[] = "AASIdentifierType";
						static constexpr const char DisplayName[] = "AASIdentifierType";
						static constexpr const char Description[] = "AASIdentifierType";
						static constexpr const char NodeHandle[] = "AASIdentifierType";

						static constexpr const char BrowseText_ID[] = "Id";
						static constexpr const char DisplayName_ID[] = "Id";
						static constexpr const char Description_ID[] = "AASIdentifierType::Id";
						static constexpr const char NodeHandle_ID[] = "AASIdentifierType::Id";

						static constexpr const char BrowseText_IdType[] = "IdType";
						static constexpr const char DisplayName_IdType[] = "IdType";
						static constexpr const char Description_IdType[] = "AASIdentifierType::IdType";
						static constexpr const char NodeHandle_IdType[] = "AASIdentifierType::AASIdentifierType:IdType";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASIdentifierType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId id    (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_ID);
					NodeId idType(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_IdType);

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
						id,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_ID),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_ID, AttrNames::Description_ID, "en-US")
					);


					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(id, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						idType,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_IdType),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_IdType, AttrNames::Description_IdType, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(idType, UA_NODECLASS_VARIABLE);
				}
			}
		}
	}
}
#endif
