/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_ASSET_TYPE_H
#define AAS_ASSET_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/aas/metamodel/IAASIdentifiableType.h>
#include <BaSyx/opcua/aas/metamodel/AASSubmodelType.h>
#include <BaSyx/opcua/aas/metamodel/AASReferenceType.h>
#include <BaSyx/opcua/aas/metamodel/AASReference.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct AASAssetType
				{
					struct AttrNames
					{
						static constexpr const char InstanceName[] = "Asset";
						static constexpr const char BrowseText[] = "AASAssetType";
						static constexpr const char DisplayName[] = "AASAssetType";
						static constexpr const char Description[] = "AASAssetType";
						static constexpr const char NodeHandle[] = "AASAssetType";

						static constexpr const char BrowseText_PropertyAssetKind[] = "PropertyType::AssetKind";
						static constexpr const char DisplayName_PropertyAssetKind[] = "AssetKind";
						static constexpr const char Description_PropertyAssetKind[] = "AASAssetType::PropertyType::AssetKind";
						static constexpr const char NodeHandle_PropertyAssetKind[] = "AssetKind";

						static constexpr const char BrowseText_AASRefIdentSubmodel[] = "AASReferenceType::AssetIdentificationModel";
						static constexpr const char DisplayName_AASRefIdentSubmodel[] = "AASReferenceType::AssetIdentificationModel";
						static constexpr const char Description_AASRefIdentSubmodel[] = "Identification submodel reference";
						static constexpr const char NodeHandle_AASRefIdentSubmodel[] = "AssetIdentificationModelReference";

						static constexpr const char BrowseText_IdentSubmodel[] = "AASSubmodelType::<Submodel>";
						static constexpr const char DisplayName_IdentSubmodel[] = "AASSubmodelType";
						static constexpr const char Description_IdentSubmodel[] = "Identification submodel";
						static constexpr const char NodeHandle_IdentSubmodel[] = "AssetIndentificationModel";

						static constexpr const char BrowseText_AASRefBomSubmodel[] = "AASSubmodelType::BillOfMaterial";
						static constexpr const char DisplayName_AASRefBomSubmodel[] = "AASReferenceType::BillOfMaterial";
						static constexpr const char Description_AASRefBomSubmodel[] = "Bill of material reference";
						static constexpr const char NodeHandle_AASRefBomSubmodel[] = "BillOfMaterialReference";

						static constexpr const char BrowseText_BomSubmodel[] = "AASSubmodelType::<Submodel>";
						static constexpr const char DisplayName_BomSubmodel[] = "AASSubmodelType";
						static constexpr const char Description_BomSubmodel[] = "Boll of materail submodel";
						static constexpr const char NodeHandle_BomSubmodel[] = "BillOfMaterial";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_connector);
				};

				template<typename CONNECTOR_TYPE>
				inline UA_StatusCode AASAssetType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					Services<CONNECTOR_TYPE> services(t_connector);

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					NodeId assetKind(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_PropertyAssetKind);
					NodeId identSubmodelRef(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_AASRefIdentSubmodel);
					NodeId identSubmodel(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_IdentSubmodel);
					NodeId bomSubmodelRef(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_AASRefBomSubmodel);
					NodeId bomSubmodel(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_BomSubmodel);
					NodeId aasReference = AASReference::getNodeId(t_ns);

					/* AssetType Node*/
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

					/* Indentifiable interface */
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

					/* AssetKind Node*/
					status = services.addVariableNode(
						assetKind,
						getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASPROPERTY),
						NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText_PropertyAssetKind),
						VariableAttributes(UA_TYPES_STRING, AttrNames::DisplayName_PropertyAssetKind, AttrNames::Description_PropertyAssetKind, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(assetKind, UA_NODECLASS_VARIABLE);


					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					/* Identification Submodel Reference*/
					status = services.addObjectNode(
						identSubmodelRef,
						getNodeId(t_ns),
						AASReferenceType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_AASRefIdentSubmodel),
						ObjectAttributes(AttrNames::DisplayName_AASRefIdentSubmodel, AttrNames::Description_AASRefIdentSubmodel, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(identSubmodelRef, UA_NODECLASS_OBJECT);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					/* Identification Submodel*/
					status = services.addObjectNode(
						identSubmodel,
						identSubmodelRef,
						AASSubmodelType::getNodeId(t_ns),
						aasReference,
						QualifiedName(t_ns, AttrNames::BrowseText_IdentSubmodel),
						ObjectAttributes(AttrNames::DisplayName_IdentSubmodel, AttrNames::Description_IdentSubmodel, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleOptional(identSubmodel, UA_NODECLASS_OBJECT);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					/* Bill of materials Submodel Reference*/
					status = services.addObjectNode(
						bomSubmodel,
						bomSubmodelRef,
						AASReferenceType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_AASRefBomSubmodel),
						ObjectAttributes(AttrNames::DisplayName_AASRefBomSubmodel, AttrNames::Description_AASRefBomSubmodel, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(bomSubmodel, UA_NODECLASS_OBJECT);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					/* Identification Submodel*/
					status = services.addObjectNode(
						bomSubmodel,
						getNodeId(t_ns),
						AASSubmodelType::getNodeId(t_ns),
						aasReference,
						QualifiedName(t_ns, AttrNames::BrowseText_BomSubmodel),
						ObjectAttributes(AttrNames::DisplayName_BomSubmodel, AttrNames::Description_BomSubmodel, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleOptional(bomSubmodel, UA_NODECLASS_OBJECT);

				}
			}
		}
	}
}


#endif