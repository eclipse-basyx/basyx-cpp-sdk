/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef API_HELPERS_H
#define API_HELPERS_H

#include <BaSyx/log/log.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/node/AssetAdministrationShellNodeManager.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            class ApiHelpers
            {
                static constexpr const char* loggerName = "AASApiProperty";
                using LangStringSet = basyx::aas::map::LangStringSet;
            public:
                enum idadKeys : uint8_t {ID = 0, ID_TYPE, VER, REV};
                
                static BrowsePath getAdminVerBrowsePath(int32_t nsIdx);

                static BrowsePath getAdminRevBrowsePath(int32_t nsIdx);

                static BrowsePath getIdentIdBrowsePath(int32_t nsIdx);

                static BrowsePath getIdentIdTypeBrowsePath(int32_t nsIdx);

                static LocalizedText getNodeDescription(const LangStringSet& t_descriptions);

                static LangStringSet getMetamodelDescription(const LocalizedText& t_text);

                /* Retrieves the Identification and Administration Node ids */
                template<typename CONNECTOR_TYPE>
                static const std::tuple<NodeId, NodeId, NodeId, NodeId> getAdminIdentNodeIds(CONNECTOR_TYPE& t_connector, const NodeId& t_aasNode)
                {
                    NodeId idNode, idTypeNode, versionNode, revisionNode;

                    UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                    Services<CONNECTOR_TYPE> services(t_connector);

                    auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                    basyx::log logger(loggerName);

                    auto nullNodesTuple = std::make_tuple(NodeId::nullNode(), NodeId::nullNode(), NodeId::nullNode(), NodeId::nullNode());

                    // Translate paths to node ids of Administration and Identification Nodes
                    status = services.translateBrowsePathToNodeIdService(getAdminVerBrowsePath(nsIdx), t_aasNode, versionNode);
                    CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(logger, status, nullNodesTuple, "Failed to resolve Admin Version node ");

                    status = services.translateBrowsePathToNodeIdService(getAdminRevBrowsePath(nsIdx), t_aasNode, revisionNode);
                    CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(logger, status, nullNodesTuple, "Failed to resolve Admin Revision node");

                    status = services.translateBrowsePathToNodeIdService(getIdentIdBrowsePath(nsIdx), t_aasNode, idNode);
                    CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(logger, status, nullNodesTuple, "Failed to resolve Identification Id node");

                    status = services.translateBrowsePathToNodeIdService(getIdentIdTypeBrowsePath(nsIdx), t_aasNode, idTypeNode);
                    CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(logger, status, nullNodesTuple, "Failed to resolve Identification IdType node");

                    return std::make_tuple(idNode, idTypeNode, versionNode, revisionNode);
                }

                template<typename CONNECTOR_TYPE>
                static UA_StatusCode writeAdminIdent(CONNECTOR_TYPE& t_connector,
                    const NodeId& t_node,
                    const std::string& t_loggerName,
                    const std::string& t_admVer,
                    const std::string& t_admRev,
                    const std::string& t_idType,
                    const std::string& t_id)
                {

                    Services<CONNECTOR_TYPE> services(t_connector);

                    basyx::log logger(t_loggerName);

                    UA_StatusCode status = UA_STATUSCODE_GOOD;

                    auto idadNodes = ApiHelpers::getAdminIdentNodeIds(t_connector, t_node);

                    // Write Administration and Identifications
                    status  = services.writeValue(std::get<ApiHelpers::idadKeys::VER>(idadNodes), t_admVer);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to write Version node");

                    status  = services.writeValue(std::get<ApiHelpers::idadKeys::REV>(idadNodes), t_admRev);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to write Revision node");

                    status = services.writeValue(std::get<ApiHelpers::idadKeys::ID>(idadNodes), t_id);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to write Id node");

                    status = services.writeValue(std::get<ApiHelpers::idadKeys::ID_TYPE>(idadNodes), t_idType);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to write IdType node");

                    return UA_STATUSCODE_GOOD;
                }

                template<typename CONNECTOR_TYPE>
                static UA_StatusCode readAdminIdent(CONNECTOR_TYPE& t_connector,
                    const NodeId& t_node,
                    std::string& t_loggerName,
                    std::string& t_admVer,
                    std::string& t_admRev,
                    std::string& t_idType,
                    std::string& t_id)
                {
                    Services<CONNECTOR_TYPE> services(t_connector);

                    basyx::log logger(t_loggerName);

                    UA_StatusCode status = UA_STATUSCODE_GOOD;

                    auto idadNodes = ApiHelpers::getAdminIdentNodeIds(t_connector, t_node);

                    // Read Administration and Identifications
                    status = services.readValue(std::get<ApiHelpers::idadKeys::ID>(idadNodes), t_id);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to read Id node");

                    status = services.readValue(std::get<ApiHelpers::idadKeys::ID_TYPE>(idadNodes), t_idType);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to read IdType node");

                    status = services.readValue(std::get<ApiHelpers::idadKeys::REV>(idadNodes), t_admRev);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to read Revision node");

                    status = services.readValue(std::get<ApiHelpers::idadKeys::VER>(idadNodes), t_admVer);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(logger, status, "Failed to read Version node");

                    return UA_STATUSCODE_GOOD;
                }
            };
        }
    }
}

#endif