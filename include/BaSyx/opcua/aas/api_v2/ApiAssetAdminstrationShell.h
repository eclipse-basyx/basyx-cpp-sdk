/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef API_ASSET_ADMINISTRATION_SHELL_H_
#define API_ASSET_ADMINISTRATION_SHELL_H_

#include <BaSyx/log/log.h>
#include <BaSyx/opcua/aas/node/AssetAdministrationShellNodeManager.h>
#include <BaSyx/opcua/aas/api_v2/ApiHelpers.h>
#include <BaSyx/opcua/aas/api_v2/ApiSubmodel.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class ApiAssetAdminstrationShell
            {
                static constexpr const char* loggerName = "ApiAssetAdminstrationShell";
            public:
                // t_parent is the node at which the AAS will be creatred as child (hasComponent reference)
                ApiAssetAdminstrationShell(CONNECTOR_TYPE& t_connector, const NodeId& t_parent) :
                    m_logger(loggerName),
                    m_connector(t_connector),
                    m_aasNodeMgr(util::make_unique<AssetAdministrationShellNodeManager<CONNECTOR_TYPE>>(t_connector, t_parent)){}

                virtual ~ApiAssetAdminstrationShell() = default;

                UA_StatusCode createAssetAdministrationShell(const AssetAdministrationShell_t& t_aas);

                UA_StatusCode deleteAssetAdministrationShell(const std::string& t_aasIdentifier);

                std::unique_ptr<AssetAdministrationShell_t> getAssetAdministrationShell(const std::string& t_identifier);

                std::vector<std::unique_ptr<AssetAdministrationShell_t>> getAllAssetAdministrationShells();

                UA_StatusCode addSubmodel(const std::string& t_aasIdentifier, const Submodel_t& t_submodel);

                UA_StatusCode deleteSubmodel(const std::string& t_aasIdentifier, const std::string& t_idShort);

                std::vector<std::unique_ptr<Submodel_t>> getAllSubmodels(const std::string& t_identifer);

            private:
                std::unique_ptr<AssetAdministrationShell_t> constructAssetAdministrationShell(const NodeId& t_aasNode);

            private:
                std::unique_ptr<AssetAdministrationShellNodeManager<CONNECTOR_TYPE>> m_aasNodeMgr;
                CONNECTOR_TYPE& m_connector;
                basyx::log m_logger;
            };

        	/* Creates an AAS in the OPC UA Server*/
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiAssetAdminstrationShell<CONNECTOR_TYPE>::createAssetAdministrationShell(const AssetAdministrationShell_t & t_aas)
            {
                using namespace aas::metamodel;

                Services<CONNECTOR_TYPE> services(m_connector);

                UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                NodeId aasOutNode, idNode, idTypeNode, versionNode, revisionNode;

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                std::string verVal = t_aas.getAdministrativeInformation().getVersion() ? *t_aas.getAdministrativeInformation().getVersion() : std::string();
                std::string revVal = t_aas.getAdministrativeInformation().getRevision() ? *t_aas.getAdministrativeInformation().getRevision() : std::string();
                std::string idVal = t_aas.getIdentification().getId();
                std::string idTypeVal = aas::KeyType_::to_string(t_aas.getIdentification().getIdType());


                //Check if AAS is already existing, if so delete it (UPDATE semantics)
                status = m_aasNodeMgr->retrieve(idVal, aasOutNode);

                if ((status == UA_STATUSCODE_GOOD) && !aasOutNode.isNull())
                {
                   status = m_aasNodeMgr->remove(idVal);

                   if (status != UA_STATUSCODE_GOOD)
                   {
                       m_logger.error(std::string("AssetAdminstrationShell node already exists and cannot be removed -") +  shared::diag::getErrorString(status));

                       return status;
                   }
                }

                // Create AASNode
                status = m_aasNodeMgr->create(t_aas.getIdShort(), aasOutNode, ApiHelpers::getNodeDescription(t_aas.getDescription()));

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger.error(std::string("Failed to create AssetAdminstrationShell node - ") + shared::diag::getErrorString(status));

                    return status;
                }

                // Write Administration and Identifications
                status = ApiHelpers::writeAdminIdent(m_connector, aasOutNode, loggerName, verVal, revVal, idTypeVal, idVal);

                return status;
            }

            /* Deletes the AAS with the given identifier from OPC UA Server */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiAssetAdminstrationShell<CONNECTOR_TYPE>::deleteAssetAdministrationShell(const std::string& t_identifier)
            {
                return m_aasNodeMgr->remove(t_identifier);
            }

            /* Retrieves the AAS with the given identifier from OPC UA Server */
            template<typename CONNECTOR_TYPE>
            std::unique_ptr<AssetAdministrationShell_t> ApiAssetAdminstrationShell<CONNECTOR_TYPE>::getAssetAdministrationShell(const std::string& t_identifier)
            {
                NodeId aasNode;

                UA_StatusCode status = m_aasNodeMgr->retrieve(t_identifier, aasNode);

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger.error(std::string("Failed to retrieve AssetAdminstrationShell node - ") + shared::diag::getErrorString(status));

                    return nullptr;
                }

                return std::move(constructAssetAdministrationShell(aasNode));
            }

            /* Build the AAS and fills the attributes */
            template<typename CONNECTOR_TYPE>
            inline std::unique_ptr<AssetAdministrationShell_t> ApiAssetAdminstrationShell<CONNECTOR_TYPE>::constructAssetAdministrationShell(const NodeId & t_aasNode)
            {
                std::string aasIdShort, idVal, idTypeVal, admVer, admRev, loggName;   
                NodeId idNode, idTypeNode;
                Services<CONNECTOR_TYPE> services(m_connector);

                loggName = loggerName;

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                aasIdShort = shared::string::getInstanceName(services.getBrowseNameFromNodeId(t_aasNode).getText());

                auto idadNodes = ApiHelpers::getAdminIdentNodeIds(m_connector, t_aasNode);

                UA_StatusCode status = services.translateBrowsePathToNodeIdService(ApiHelpers::getIdentIdBrowsePath(nsIdx), t_aasNode, idNode);

                if (status != UA_STATUSCODE_GOOD)
                {
                    m_logger.error(std::string("Failed to translate the Browsepath to NodeId - ")
                        +  " - " + ApiHelpers::getIdentIdBrowsePath(nsIdx).toString() + " - "
                        +  shared::diag::getErrorString(status));

                    return nullptr;
                }

                status = ApiHelpers::readAdminIdent(m_connector, t_aasNode, loggName, admVer, admRev, idTypeVal, idVal);

                if (status != UA_STATUSCODE_GOOD)
                    return nullptr;

                // TODO : Asset has to be handled
                auto aas = util::make_unique<AssetAdministrationShell_t>(
                    aasIdShort, Identifier_t(aas::KeyType_::from_string(idTypeVal), idVal),
                    Asset_t(std::string(), Identifier_t::Custom(std::string()))
                );

                aas->setAdministrativeInformation(aas::map::AdministrativeInformation(admVer, admRev));

                auto submodels = getAllSubmodels(idVal);

                std::for_each(submodels.begin(), submodels.end(), [&aas](std::unique_ptr<Submodel_t>& t_sm) {
                    aas->getSubmodels().addElement(std::move(t_sm));
                });

                return std::move(aas);
            }

            template<typename CONNECTOR_TYPE>
            inline std::vector<std::unique_ptr<AssetAdministrationShell_t>> ApiAssetAdminstrationShell<CONNECTOR_TYPE>::getAllAssetAdministrationShells()
            {
                std::vector<std::unique_ptr<AssetAdministrationShell_t>> ret;
                for (const std::tuple<NodeId, std::string>& pair : m_aasNodeMgr->retrieveAll())
                {
                    auto aas = getAssetAdministrationShell(std::get<1>(pair));
                    ret.emplace_back(std::move(aas));
                }
                return ret;
            }

            template<typename CONNECTOR_TYPE>
            inline std::vector<std::unique_ptr<Submodel_t>> ApiAssetAdminstrationShell<CONNECTOR_TYPE>::getAllSubmodels(const std::string& t_identifer)
            {
                NodeId aasNodeId;
                std::vector<std::unique_ptr<Submodel_t>> ret;
                // Get the AAS NodeId
                UA_StatusCode status = m_aasNodeMgr->retrieve(t_identifer, aasNodeId);

                CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(m_logger,
                    status, ret, std::string("AAS node for [") + t_identifer + std::string("] could not be retrieved"));
                // Submodel node manager
                SubmodelNodeManager<CONNECTOR_TYPE> smnNodeMgr(m_connector, aasNodeId);
                // Submodel API
                ApiSubmodel<CONNECTOR_TYPE> api(m_connector, aasNodeId);

                for (const std::tuple<NodeId, std::string>& pair: smnNodeMgr.retrieveAll())
                {
                    auto sm = api.getSubmodel(std::get<1>(pair));
                    ret.emplace_back(std::move(sm));
                }
                return ret;
            }

            /* Add Submodel to the AAS */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiAssetAdminstrationShell<CONNECTOR_TYPE>::addSubmodel(const std::string& t_aasIdentifier, const Submodel_t& t_submodel)
            {
                // Get the AAS NodeId
                NodeId aasNodeId;
                UA_StatusCode status = m_aasNodeMgr->retrieve(t_aasIdentifier, aasNodeId);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger,
                    status, std::string("AAS node for Submodel [") + t_submodel.getIdShort() + std::string("] could not be retrieved"));

                ApiSubmodel<CONNECTOR_TYPE> api(m_connector, aasNodeId);

                return api.createSubmodel(t_submodel);
            }

            /* Remove Submodel from AAS */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiAssetAdminstrationShell<CONNECTOR_TYPE>::deleteSubmodel(const std::string& t_aasIdentifier, const std::string& t_idShort)
            {
                // Get the AAS NodeId
                NodeId aasNodeId;
                UA_StatusCode status = m_aasNodeMgr->retrieve(t_aasIdentifier, aasNodeId);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger,
                    status, std::string("AAS node for Submodel [") + t_idShort + std::string("] could not be retrieved"));

                ApiSubmodel<CONNECTOR_TYPE> api(m_connector, aasNodeId);

                return api.deleteSubmodel(t_idShort);
            }
        }
    }
}
#endif