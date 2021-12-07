/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_MULTI_LANGUAGE_PROPERTY_TYPE_H
#define AAS_MULTI_LANGUAGE_PROPERTY_TYPE_H

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

				struct AASMultiLanguagePropertyType
				{
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "AASMultiLanguagePropertyType";
						static constexpr const char DisplayName[] = "AASMultiLanguagePropertyType";
						static constexpr const char Description[] = "AASMultiLanguagePropertyType";
						static constexpr const char NodeHandle[] = "AASMultiLanguagePropertyType";

						static constexpr const char BrowseName_Value[] = "PropertyType::Value";
						static constexpr const char DisplayName_Value[] = "Value";
						static constexpr const char Description_Value[] = "AASMultiLanguagePropertyType::Value";
						static constexpr const char NodeHandle_Value[] = "AASMultiLanguagePropertyType::Value";

						static constexpr const char BrowseName_ReferenceValueId[] = "PropertyType::ValueId";
						static constexpr const char DisplayName_ReferenceValueId[] = "ValueId";
						static constexpr const char Description_ReferenceValueId[] = "AASMultiLanguagePropertyType::AASReferenceType::ValueId";
						static constexpr const char NodeHandle_ReferenceValueId[] = "AASMultiLanguagePropertyType::AASReferenceType::ValueId";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				UA_StatusCode AASMultiLanguagePropertyType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status;

					Services<CONNECTOR_TYPE> services(t_connector);


					NodeId referenceValueId(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_ReferenceValueId);
					NodeId value           (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Value);


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
						value,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseName_Value),
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
						referenceValueId,
						getNodeId(t_ns),
						AASReferenceType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseName_ReferenceValueId),
						ObjectAttributes(AttrNames::DisplayName_ReferenceValueId, AttrNames::Description_ReferenceValueId, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(referenceValueId, UA_NODECLASS_OBJECT);

					return status;
				}
			}
		}
	}
}
#endif