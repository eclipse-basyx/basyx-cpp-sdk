/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_OPERATION_TYPE_H
#define AAS_OPERATION_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>

#include <BaSyx/opcua/aas/metamodel/AASSubmodelElementType.h>
#include <BaSyx/opcua/aas/metamodel/IAASIdentifiableType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASOperationType
				{
					struct AttrNames
					{
						static constexpr const char InstanceName[] = "Operation";
						static constexpr const char BrowseText[] = "AASOperationType";
						static constexpr const char DisplayName[] = "AASOperationType";
						static constexpr const char Description[] = "AASOperationType";
						static constexpr const char NodeHandle[] = "AASOperationType";

						static constexpr const char BrowseText_Operation[] = "Operation";
						static constexpr const char DisplayName_Operation[] = "Operation";
						static constexpr const char Description_Operation[] = "AASOperationType::Operation";
						static constexpr const char NodeHandle_Operation[] = "AASOperationType::Operation";

						static constexpr const char BrowseText_InputArguments[] = "PropertyType::InputArguments";
						static constexpr const char DisplayName_InputArguments[] = "InputArguments";
						static constexpr const char Description_InputArguments[] = "AASOperationType::Operation::PropertyType::InputArguments";
						static constexpr const char NodeHandle_InputArguments[] = "AASOperationType::Operation::PropertyType::InputArguments";

						static constexpr const char BrowseText_OutputArguments[] = "PropertyType::OutputArguments";
						static constexpr const char DisplayName_OutputArguments[] = "OutputArguments";
						static constexpr const char Description_OutputArguments[] = "AASOperationType::Operation::PropertyType::OutputArguments";
						static constexpr const char NodeHandle_OutputArguments[] = "AASOperationType::Operation::PropertyType::OutputArguments";

						static constexpr const char OperationInputVariables[] = "OperationInputVariables";
						static constexpr const char OperationOutputVariables[] = "OperationOutputVariables";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASOperationType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					UA_StatusCode status;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId operation       (UA_NodeIdType::UA_NODEIDTYPE_STRING,t_ns, AttrNames::NodeHandle_Operation);
					NodeId inputArguments  (UA_NodeIdType::UA_NODEIDTYPE_STRING,t_ns, AttrNames::NodeHandle_InputArguments);
					NodeId outputArguments (UA_NodeIdType::UA_NODEIDTYPE_STRING,t_ns, AttrNames::NodeHandle_OutputArguments);


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

					status = services.addMethodNode(
						operation,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_Operation),
						MethodAttributes(AttrNames::DisplayName_Operation, AttrNames::Description_Operation, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReference(
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASINTERFACE),
						ExpandedNodeId::string(t_ns, IAASReferableType::AttrNames::NodeHandle),
						UA_NODECLASS_OBJECTTYPE);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(operation, UA_NODECLASS_METHOD);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addVariableNode(
						inputArguments,
						operation,
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_InputArguments),
						VariableAttributes(UA_TYPES_ARGUMENT, AttrNames::DisplayName_InputArguments, AttrNames::Description_InputArguments, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addVariableNode(
						outputArguments,
						operation,
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_OutputArguments),
						VariableAttributes(UA_TYPES_ARGUMENT, AttrNames::DisplayName_OutputArguments, AttrNames::Description_OutputArguments, "en-US")
					);
				}
			}
		}
	}
}
#endif