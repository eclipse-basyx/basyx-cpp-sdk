/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_QUALIFIER_TYPE
#define AAS_QUALIFIER_TYPE

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/aas/metamodel/AASReferenceType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASQualifierType
				{
					struct AttrNames
					{
						static constexpr const char InstanceName[] = "Qualifier";
						static constexpr const char BrowseText[] = "AASQualifierType";
						static constexpr const char DisplayName[] = "AASQualifierType";
						static constexpr const char Description[] = "AASQualifierType";
						static constexpr const char NodeHandle[] = "AASQualifierType";

						static constexpr const char BrowseText_ValueId[] = "AASQualifierType::ValueId";
						static constexpr const char DisplayName_ValueId[] = "ValueId";
						static constexpr const char Description_ValueId[] = "AASQualifierType::ValueId";
						static constexpr const char NodeHandle_ValueId[] = "AASQualifierType::ValueId";

						static constexpr const char BrowseText_Type[] = "AASQualifierType::Type";
						static constexpr const char DisplayName_Type[] = "Type";
						static constexpr const char Description_Type[] = "AASQualifierType::Type";
						static constexpr const char NodeHandle_Type[] = "AASQualifierType::Type";

						static constexpr const char BrowseText_Value[] = "AASQualifierType::Value";
						static constexpr const char DisplayName_Value[] = "Value";
						static constexpr const char Description_Value[] = "AASQualifierType::Value";
						static constexpr const char NodeHandle_Value[] = "AASQualifierType::Value";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle).getUANode();
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASQualifierType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{

					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId type    (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Type);
					NodeId value   (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Value);
					NodeId valueId (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_ValueId);

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
						type,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_Type),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_Type, AttrNames::Description_Type, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(type, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						value,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_Value),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_Value, AttrNames::Description_Value, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(value, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addObjectNode(
						valueId,
						getNodeId(t_ns),
						AASReferenceType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_ValueId),
						ObjectAttributes(AttrNames::DisplayName_ValueId, AttrNames::Description_ValueId, "en-US")
					);

					return services.addForwardReferenceModellingRuleMandatory(valueId, UA_NODECLASS_VARIABLE);
				}
			}
		}
	}
}

#endif