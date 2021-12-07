/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_RANGE_TYPE_H
#define AAS_RANGE_TYPE_H

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
				struct AASRangeType
				{
					
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASRangeType";
						static constexpr const char DisplayName[] = "AASRangeType";
						static constexpr const char Description[] = "AASRangeType";
						static constexpr const char NodeHandle[] = "AASRangeType";

						static constexpr const char BrowseText_Min[] = "AASRangeType::Min";
						static constexpr const char DisplayName_Min[] = "Min";
						static constexpr const char Description_Min[] = "AASRangeType::Min";
						static constexpr const char NodeHandle_Min[] = "AASRangeType::Min";

						static constexpr const char BrowseText_Max[] = "AASRangeType::Max";
						static constexpr const char DisplayName_Max[] = "Max";
						static constexpr const char Description_Max[] = "AASRangeType::Max";
						static constexpr const char NodeHandle_Max[] = "AASRangeType::Max";

						static constexpr const char BrowseText_ValType[] = "AASRangeType::ValueType";
						static constexpr const char DisplayName_ValType[] = "ValueType";
						static constexpr const char Description_ValType[] = "AASRangeType::ValueType";
						static constexpr const char NodeHandle_ValType[] = "AASRangeType::ValueType";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASRangeType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId min_      (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Min);
					NodeId max_      (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Max);
					NodeId valueType (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_ValType);

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
						min_,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_Min),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_Min, AttrNames::Description_Min, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(min_, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						max_,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_Max),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_Max, AttrNames::Description_Max, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(max_, UA_NODECLASS_VARIABLE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						valueType,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_ValType),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_ValType, AttrNames::Description_ValType, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(valueType, UA_NODECLASS_VARIABLE);
				};
			}
		}
	}
}

#endif