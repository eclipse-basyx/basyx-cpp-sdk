/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_ASSET_ADMINISTRATION_TYPE_H
#define AAS_ASSET_ADMINISTRATION_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/aas/metamodel/AASAssetType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASAssetAdministrationShellType
				{
					struct AttrNames
					{
						static constexpr const char InstanceName[] = "AssetAdministrationShell";
						static constexpr const char BrowseText[] = "AASAssetAdministrationShellType";
						static constexpr const char DisplayName[] = "AASAssetAdministrationShellType";
						static constexpr const char Description[] = "AASAssetAdministrationShellType";
						static constexpr const char NodeHandle[] = "AASAssetAdministrationShellType";

						static constexpr const char BrowseText_Submodel[] = "AASSubmodelType::<Submodel>";
						static constexpr const char DisplayName_Submodel[] = "<Submodel>";
						static constexpr const char Description_Submodel[] = "AASSubmodelType::Submodel";
						static constexpr const char NodeHandle_Submodel[] = "AASSubmodelType::Submodel";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_connector);
				};

				template<typename CONNECTOR_TYPE>
				inline UA_StatusCode AASAssetAdministrationShellType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{

					using namespace basyx::opcua;

					Services<CONNECTOR_TYPE> services(t_connector);

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					NodeId Submodel(UA_NodeIdType::UA_NODEIDTYPE_STRING,t_ns, AttrNames::NodeHandle_Submodel);

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

					status = services.addForwardReference(
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASINTERFACE),
						ExpandedNodeId::string(t_ns, IAASIdentifiableType::AttrNames::NodeHandle),
						UA_NODECLASS_OBJECTTYPE
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addObjectNode(
						Submodel,
						getNodeId(t_ns),
						AASSubmodelType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_Submodel),
						ObjectAttributes(AttrNames::DisplayName_Submodel, AttrNames::Description_Submodel, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleOptional(Submodel, UA_NODECLASS_OBJECT);
				}
			}
		}
	}
}

#endif