/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef API_SUBMODEL_H_
#define API_SUBMODEL_H_

#include <BaSyx/log/log.h>
#include <BaSyx/opcua/aas/node/SubmodelNodeManager.h>
#include <BaSyx/opcua/aas/api_v2/ApiHelpers.h>
#include <BaSyx/opcua/aas/api_v2/ApiProperty.h>
#include <BaSyx/opcua/aas/api_v2/ApiMetamodelUtilities.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class ApiSubmodel
            {
                static constexpr const char* loggerName = "ApiSubmodel";
            public:
                ApiSubmodel(CONNECTOR_TYPE& t_connector, const NodeId& t_parent) :
                    m_logger(loggerName),
                    m_connector(t_connector),
                    m_smNode(util::make_unique<SubmodelNodeManager<CONNECTOR_TYPE>>(t_connector, t_parent)){}

                UA_StatusCode createSubmodel(const Submodel_t& t_sm);

                UA_StatusCode deleteSubmodel(const std::string& t_idShort);

                std::unique_ptr<Submodel> getSubmodel(const std::string& t_idShort);

                std::vector<std::unique_ptr<IProperty_t>> getAllProperties(const std::string& t_idShort);

            private:
                UA_StatusCode setSubmodelKind(const std::string& t_idShort, const std::string& t_valueKindStr);

                UA_StatusCode getSubmodelKind(const std::string& t_idShort, std::string& t_valueKindStr);

                UA_StatusCode retrieveSubmodelKindNode(const std::string & t_idShort, NodeId& t_node);

                std::unique_ptr<Submodel_t> constructSubmodel(const NodeId & t_smNode);

                void addPropertiesFromOpcua(Submodel_t& t_submodel);

                void addPropertiesToOpcua(const Submodel_t& t_submodel, const NodeId& t_submodelNode);
            private:
                std::unique_ptr<SubmodelNodeManager<CONNECTOR_TYPE>> m_smNode;
                CONNECTOR_TYPE& m_connector;
                basyx::log m_logger;
            };

            /* Creates the Submodel in OPC UA server according to the model data */
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiSubmodel<CONNECTOR_TYPE>::createSubmodel(const Submodel_t & t_sm)
            {

                using namespace aas::metamodel;

                Services<CONNECTOR_TYPE> services(m_connector);

                UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                NodeId smOutNode;

                std::string verVal = t_sm.getAdministrativeInformation().getVersion() ? *t_sm.getAdministrativeInformation().getVersion() : std::string();
                std::string revVal = t_sm.getAdministrativeInformation().getRevision() ? *t_sm.getAdministrativeInformation().getRevision() : std::string();
                std::string idVal = t_sm.getIdentification().getId();
                std::string idTypeVal = aas::KeyType_::to_string(t_sm.getIdentification().getIdType());

                /* Check if Submodel is already existing, if so delete it (UPDATE semantics) */
                status = m_smNode->retrieve(t_sm.getIdShort(), smOutNode);

                if ((status == UA_STATUSCODE_GOOD) && !smOutNode.isNull())
                {
                   status = m_smNode->remove(idVal);

                   CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Submodel node already exists and cannot be removed");
                }
                // Create SMNode
                status = m_smNode->create(t_sm.getIdShort(), smOutNode, ApiHelpers::getNodeDescription(t_sm.getDescription()));
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Submodel node cannot be created");
                // Write Administration and Identification
                status = ApiHelpers::writeAdminIdent(m_connector, smOutNode, loggerName, verVal, revVal, idTypeVal, idVal);
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Failed to wirte Submodel Administration and Identification nodes");
                // Write SubmodelKind
                status = setSubmodelKind(t_sm.getIdShort(), basyx::aas::ModelingKind_::to_string(t_sm.getKind()));
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Failed to write Submodel Kind node");
                // Handle SumodelElements
                // Add Propeties
                addPropertiesToOpcua(t_sm, smOutNode);
                // TODO : Other SubmodelElement types

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiSubmodel<CONNECTOR_TYPE>::deleteSubmodel(const std::string & t_idShort)
            {
                return m_smNode->remove(t_idShort);
            }

            template<typename CONNECTOR_TYPE>
            inline std::unique_ptr<Submodel> ApiSubmodel<CONNECTOR_TYPE>::getSubmodel(const std::string & t_idShort)
            {
                NodeId smNode;

                UA_StatusCode status = m_smNode->retrieve(t_idShort, smNode);

                CHECK_STATUS_LOG_ERR_AND_RETURN_NULL(m_logger, status, "Failed to retrieve submodel node");

                return constructSubmodel(smNode);
            }

            /* Build the SM in OPC UA Server and fills the attributes */
            template<typename CONNECTOR_TYPE>
            inline std::unique_ptr<Submodel_t> ApiSubmodel<CONNECTOR_TYPE>::constructSubmodel(const NodeId & t_smNode)
            {
                std::string idShort, idVal, idTypeVal, admVer, admRev, loggName;

                NodeId idNode, idTypeNode;

                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                loggName = loggerName;

                idShort = shared::string::getInstanceName(services.getBrowseNameFromNodeId(t_smNode).getText());

                auto idadNodes = ApiHelpers::getAdminIdentNodeIds(m_connector, t_smNode);

                UA_StatusCode status = services.translateBrowsePathToNodeIdService(ApiHelpers::getIdentIdBrowsePath(nsIdx), t_smNode, idNode);

                status = ApiHelpers::readAdminIdent(m_connector, t_smNode, loggName, admVer, admRev, idTypeVal, idVal);

                CHECK_STATUS_AND_RETURN_NULL(status);

                auto sm = util::make_unique<Submodel>(idShort, Identifier_t(aas::KeyType_::from_string(idTypeVal), idVal));

                sm->setAdministrativeInformation(aas::map::AdministrativeInformation(admVer, admRev));

                // Add SubmodelElements
                addPropertiesFromOpcua(*sm.get());
                // TODO: Other SubmodelElement types

                return std::move(sm);
            }

            /* Adds Properties to the passed submodel which are read from the OPC UA server */
            template<typename CONNECTOR_TYPE>
            inline void ApiSubmodel<CONNECTOR_TYPE>::addPropertiesFromOpcua(Submodel_t & t_submodel)
            {
                using namespace metamodel;

                for (std::unique_ptr<IProperty_t>& property : getAllProperties(t_submodel.getIdShort()))
                    t_submodel.submodelElements().addElement(std::move(property));

            }

            /* Adds Properties to the the OPC UA Server */
            template<typename CONNECTOR_TYPE>
            inline void ApiSubmodel<CONNECTOR_TYPE>::addPropertiesToOpcua(const Submodel_t & t_submodel, const NodeId& t_submodelNode)
            {
                // Handle different SubmodelElement Types
                for (int i = 0; i < t_submodel.submodelElements().size(); ++i)
                {
                    const auto& subModelElement = t_submodel.submodelElements().getElement(i);

                    // Property types
                    if (auto prop{ dynamic_cast<const IProperty_t*>(subModelElement) })
                    {
                        auto apiProp = util::make_unique<ApiProperty<CONNECTOR_TYPE>>(m_connector, t_submodelNode);

                        UA_StatusCode status = apiProp->createProperty(*prop);

                        CHECK_STATUS_LOG_ERR(m_logger, status, std::string("Property [") + prop->getIdShort() + std::string("] cannot be added "));

                    }
                    // TODO : Handling other SubmodelElement types
                }
            }

            template<typename CONNECTOR_TYPE>
            std::vector<std::unique_ptr<IProperty_t>> ApiSubmodel<CONNECTOR_TYPE>::getAllProperties(const std::string& t_idShort)
            {

                NodeId smNode;
                
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                // Get the Submodel node
                UA_StatusCode status = m_smNode->retrieve(t_idShort, smNode);

                std::vector<std::unique_ptr<basyx::aas::api::IProperty>> ret;

                CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(m_logger,
                    status, ret, std::string("Submodel node [") + t_idShort + std::string("] could not be retrieved"));

                // Property API 
                ApiProperty<CONNECTOR_TYPE> api(m_connector, smNode);

                // Get all Property Type nodes with idShort list
                std::vector<NodeId> propertyNodes = services.getChildReferencesWithType(
                    smNode, metamodel::AASPropertyType::getNodeId(nsIdx), NodeId::numeric(UA_NS0ID_HASCOMPONENT)
                );

                for (const NodeId& propertyNode : propertyNodes)
                {
                    // TODO : To do read IdShort of Property, read from 
                    // the idShort node in the future
                    // Here the idShort is derrived from the Browsename
                    auto propBrowseName = services.getBrowseNameFromNodeId(propertyNode);
                    auto propIdShort    = shared::string::getInstanceName(propBrowseName.getText());

                    if (auto property{ api.getProperty(propIdShort) })
                        ret.emplace_back(std::move(property));
                }

                return ret;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiSubmodel<CONNECTOR_TYPE>::setSubmodelKind(const std::string & t_idShort, const std::string & t_valueKindStr)
            {
                NodeId kindNode;
                Services<CONNECTOR_TYPE> services(m_connector);

                UA_StatusCode status = retrieveSubmodelKindNode(t_idShort, kindNode);
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Submodel Kind node cannot be retrieved");

                return services.writeValue(kindNode, t_valueKindStr);
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiSubmodel<CONNECTOR_TYPE>::getSubmodelKind(const std::string & t_idShort, std::string & t_valueKindStr)
            {
                NodeId kindNode;
                Services<CONNECTOR_TYPE> services(m_connector);

                UA_StatusCode status = retrieveSubmodelKindNode(t_idShort, kindNode);
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Submodel Kind node cannot be retrieved");

                return services.readValue(kindNode, t_valueKindStr);
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiSubmodel<CONNECTOR_TYPE>::retrieveSubmodelKindNode(const std::string & t_idShort, NodeId & t_node)
            {
                using namespace metamodel;

                NodeId smOutNode;
                Services<CONNECTOR_TYPE> services(m_connector);
                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                UA_StatusCode status = m_smNode->retrieve(t_idShort, smOutNode);
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Submodel node cannot be retrieved");

                return services.translateBrowsePathToNodeIdService(
                    BrowsePath(BrowseName(nsIdx, AASSubmodelType::AttrNames::BrowseText_PropertyKind)), smOutNode, t_node);

            }
        }
    }
}
#endif