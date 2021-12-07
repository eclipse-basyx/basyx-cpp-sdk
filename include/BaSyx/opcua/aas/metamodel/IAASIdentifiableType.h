/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef IAAS_IDENTIFIABLE_TYPE_H
#define IAAS_IDENTIFIABLE_TYPE_H

#include <BaSyx/opcua/common/NodeId.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/QualifiedName.h>
#include <BaSyx/opcua/common/ObjectAttributes.h>
#include <BaSyx/opcua/common/ObjectTypeAttributes.h>
#include <BaSyx/opcua/aas/metamodel/AASIdentifierType.h>
#include <BaSyx/opcua/aas/metamodel/IAASReferableType.h>
#include <BaSyx/opcua/aas/metamodel/AASAdministrativeInformationType.h>

namespace basyx
{
	namespace opcua
	{
		namespace aas
		{
			namespace metamodel
			{
				struct IAASIdentifiableType
				{
					struct AttrNames
					{
						static constexpr const char InstanceName[] = "Identifiable";
						static constexpr const char BrowseText[] = "IAASIdentifiableType";
						static constexpr const char DisplayName[] = "IAASIdentifiableType";
						static constexpr const char Description[] = "IAASIdentifiableType";
						static constexpr const char NodeHandle[] = "IAASIdentifiableType";

						static constexpr const char BrowseText_Identification[] = "Identification";
						static constexpr const char DisplayName_Identification[] = "Identification";
						static constexpr const char Description_Identification[] = "IAASIdentifiableType::Identification";
						static constexpr const char NodeHandle_Identification[] = "IAASIdentifiableType::Identification";

						static constexpr const char BrowseText_Administration[] = "Administration";
						static constexpr const char DisplayName_Administration[] = "Administration";
						static constexpr const char Description_Administration[] = "IAASIdentifiableType::Administration";
						static constexpr const char NodeHandle_Administration[] = "IAASIdentifiableType::Administration";
					};

					static basyx::opcua::NodeId getNodeId(int32_t t_ns)
					{
						return basyx::opcua::NodeId::string(t_ns, AttrNames::NodeHandle);
					}

					template<typename CONNECTOR_TYPE>
					static BrowsePath getAdministrationPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId& t_parentNode);

					template<typename CONNECTOR_TYPE>
					static BrowsePath getAdministrationVersionPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId& t_parentNode);

					template<typename CONNECTOR_TYPE>
					static BrowsePath getAdministrationRevisionPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId& t_parentNode);

					template<typename CONNECTOR_TYPE>
					static BrowsePath getIdentificationPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId& t_parentNode);

					template<typename CONNECTOR_TYPE>
					static BrowsePath getIdentificationIdPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId& t_parentNode);

					template<typename CONNECTOR_TYPE>
					static BrowsePath getIdentificationIdTypePath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId& t_parentNode);

					template<typename CONNECTOR_TYPE>
					static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_client);
				};

				template<typename CONNECTOR_TYPE>
				inline BrowsePath IAASIdentifiableType::getAdministrationPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId & t_parentNode)
				{
					Services<CONNECTOR_TYPE> services(t_connector);

					return { {services.getBrowseNameFromNodeId(t_parentNode)},
							{BrowseName(t_ns, IAASIdentifiableType::AttrNames::BrowseText_Administration)}
					};
				}

				template<typename CONNECTOR_TYPE>
				inline BrowsePath IAASIdentifiableType::getAdministrationVersionPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId & t_parentNode)
				{
					Services<CONNECTOR_TYPE> services(t_connector);

					return { {services.getBrowseNameFromNodeId(t_parentNode)},
							{BrowseName(t_ns, IAASIdentifiableType::AttrNames::BrowseText_Administration)},
							{BrowseName(t_ns, AASAdministrativeInformationType::AttrNames::BrowseText_Version)}
					};
				}

				template<typename CONNECTOR_TYPE>
				inline BrowsePath IAASIdentifiableType::getAdministrationRevisionPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId & t_parentNode)
				{
					Services<CONNECTOR_TYPE> services(t_connector);

					return { {services.getBrowseNameFromNodeId(t_parentNode)},
							{BrowseName(t_ns, IAASIdentifiableType::AttrNames::BrowseText_Administration)},
							{BrowseName(t_ns, AASAdministrativeInformationType::AttrNames::BrowseText_Revision)}
					};
				}

				template<typename CONNECTOR_TYPE>
				inline BrowsePath IAASIdentifiableType::getIdentificationPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId & t_parentNode)
				{
					Services<CONNECTOR_TYPE> services(t_connector);

					return { {services.getBrowseNameFromNodeId(t_parentNode)},
							{BrowseName(t_ns, IAASIdentifiableType::AttrNames::BrowseText_Identification)}
					};
				}

				template<typename CONNECTOR_TYPE>
				inline BrowsePath IAASIdentifiableType::getIdentificationIdPath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId & t_parentNode)
				{
					Services<CONNECTOR_TYPE> services(t_connector);

					return { {services.getBrowseNameFromNodeId(t_parentNode)},
							{BrowseName(t_ns, IAASIdentifiableType::AttrNames::BrowseText_Identification)},
							{BrowseName(t_ns, AASIdentifierType::AttrNames::BrowseText_ID)}
					};
				}

				template<typename CONNECTOR_TYPE>
				inline BrowsePath IAASIdentifiableType::getIdentificationIdTypePath(int32_t t_ns, CONNECTOR_TYPE & t_connector, const NodeId & t_parentNode)
				{
					Services<CONNECTOR_TYPE> services(t_connector);

					return { {services.getBrowseNameFromNodeId(t_parentNode)},
							{BrowseName(t_ns, IAASIdentifiableType::AttrNames::BrowseText_Identification)},
							{BrowseName(t_ns, AASIdentifierType::AttrNames::BrowseText_IdType)}
					};
				}



				template<typename CONNECTOR_TYPE>
				UA_StatusCode IAASIdentifiableType::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
				{
					using namespace basyx::opcua;

					UA_StatusCode status = UA_STATUSCODE_GOOD;

					Services<CONNECTOR_TYPE> services(t_connector);

					NodeId identification(UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Identification);
					NodeId adminstration (UA_NodeIdType::UA_NODEIDTYPE_STRING, t_ns, AttrNames::NodeHandle_Administration);

					status = services.addObjectTypeNode(
						getNodeId(t_ns),
						IAASReferableType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASSUBTYPE),
						QualifiedName(t_ns, AttrNames::BrowseText),
						ObjectTypeAttributes(AttrNames::DisplayName, AttrNames::Description, "en-US")
					);

					if (basyx::opcua::shared::diag::isStatusBad(status))
					{
						return status;
					}

					status = services.addObjectNode(
						identification,
						getNodeId(t_ns),
						AASIdentifierType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_Identification),
						ObjectAttributes(AttrNames::DisplayName_Identification, AttrNames::Description_Identification, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addForwardReferenceModellingRuleMandatory(identification, UA_NODECLASS_OBJECT);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					status = services.addObjectNode(
						adminstration,
						getNodeId(t_ns),
						AASAdministrativeInformationType::getNodeId(t_ns),
						NodeId::numeric(UA_NS0ID_HASCOMPONENT),
						QualifiedName(t_ns, AttrNames::BrowseText_Administration),
						ObjectAttributes(AttrNames::DisplayName_Administration, AttrNames::Description_Administration, "en-US")
					);

					if (status != UA_STATUSCODE_GOOD)
					{
						return status;
					}

					return services.addForwardReferenceModellingRuleMandatory(adminstration, UA_NODECLASS_OBJECT);
				};

			};
		}
	}
}
#endif