/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef IAAS_REFERABLE_TYPE_H
#define IAAS_REFERABLE_TYPE_H

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
				struct IAASReferableType
				{
					struct AttrNames
					{
						static constexpr const char BrowseText[] = "IAASReferableType";
						static constexpr const char DisplayName[] = "IAASReferableType";
						static constexpr const char Description[] = "IAASReferableType";
						static constexpr const char NodeHandle[] = "IAASReferableType";

						static constexpr const char BrowseText_Category[] = "Category";
						static constexpr const char DisplayName_Category[] = "Category";
						static constexpr const char Description_Category[] = "IAASReferableType::Category";
						static constexpr const char NodeHandle_Category[] = "IAASReferableType::Category";

						static constexpr const char BrowseText_IdShort[] = "IdShort";
						static constexpr const char DisplayName_IdShort[] = "IdShort";
						static constexpr const char Description_IdShort[] = "IAASReferableType::IdShort";
						static constexpr const char NodeHandle_IdShort[] =  "IAASReferableType::IdShort";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_connector);
				};

				template<typename CONNECTOR_TYPE>
				inline UA_StatusCode IAASReferableType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{

					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId cateory(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Category);
					NodeId idShort(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_IdShort);

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
						cateory,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_Category),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_Category, AttrNames::Description_Category, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(cateory, UA_NODECLASS_VARIABLE);

					status = services.addVariableNode(
						idShort,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_IdShort),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_IdShort, AttrNames::Description_IdShort, "en-US")
					);

					return services.addForwardReferenceModellingRuleMandatory(idShort, UA_NODECLASS_VARIABLE);
				}
			}
		}
	}
}


#endif
