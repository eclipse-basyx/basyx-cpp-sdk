/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_REFERENCE_TYPE_H
#define AAS_REFERENCE_TYPE_H

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
				struct AASReferenceType
				{
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASReferenceType";
						static constexpr const char DisplayName[] = "AASReferenceType";
						static constexpr const char Description[] = "AASReferenceType";
						static constexpr const char NodeHandle[] = "AASReferenceType";

						static constexpr const char BrowseText_Keys[] = "AASReferenceType::Keys";
						static constexpr const char DisplayName_Keys[] = "Keys";
						static constexpr const char Description_Keys[] = "AASReferenceType::Keys";
						static constexpr const char NodeHandle_Keys[] = "AASReferenceType::keys";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASReferenceType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId aasKeys(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Keys);

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
						aasKeys,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_Keys),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_Keys, AttrNames::Description_Keys, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleOptional(aasKeys, UA_NODECLASS_VARIABLE);
				}
			}
		}
	}
}
#endif
