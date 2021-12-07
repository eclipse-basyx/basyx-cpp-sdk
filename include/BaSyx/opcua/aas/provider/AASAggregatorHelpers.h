/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_AGGREGATOR_HELPERS_H
#define AAS_AGGREGATOR_HELPERS_H

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/opcua/aas/provider/AASObjectDeserializer.h>
#include <BaSyx/opcua/aas/api_v2/ApiAssetAdminstrationShell.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class AASAggregatorHelpers
            {
            public:
                AASAggregatorHelpers(CONNECTOR_TYPE& t_connector, const NodeId& t_parent): 
                    m_connector(t_connector), m_parent(t_parent){}

                basyx::object getShells();

                basyx::object getShellsAasId(const std::string& t_identifier);

                basyx::object::error putShellsAasId(const std::string& t_identifier, basyx::object t_aasObject);

                basyx::object::error deleteShellsAasId(const std::string& t_identifier);

                basyx::object getShellsAasidAasSubmodels(const std::string& t_identifier);

            private:
                CONNECTOR_TYPE& m_connector;
                NodeId m_parent;
            };

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASAggregatorHelpers<CONNECTOR_TYPE>::getShells()
            {
                ApiAssetAdminstrationShell<CONNECTOR_TYPE> aasApi(m_connector, m_parent);

                basyx::object aasList = basyx::object::make_list<basyx::object>();
                for (const auto& shell : aasApi.getAllAssetAdministrationShells())
                    aasList.insert<basyx::object>(shell->getMap());
                return aasList;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASAggregatorHelpers<CONNECTOR_TYPE>::getShellsAasId(const std::string & t_identifier)
            {
                ApiAssetAdminstrationShell<CONNECTOR_TYPE> aasApi(m_connector, m_parent);

                auto aas = aasApi.getAssetAdministrationShell(t_identifier);
                if (aas)
                    return aas->getMap();
                return basyx::object::make_error(basyx::object::error::PropertyNotFound);
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASAggregatorHelpers<CONNECTOR_TYPE>::putShellsAasId(const std::string & t_identifier,
                basyx::object t_aasObject)
            {
                ApiAssetAdminstrationShell<CONNECTOR_TYPE> aasApi(m_connector, m_parent);

                auto aasInst = AASObjectDeserializer::makeAssetAdministrationShell(t_aasObject);
                UA_StatusCode status = aasApi.createAssetAdministrationShell(*aasInst);
                if (status != UA_STATUSCODE_GOOD)
                    return basyx::object::error::ProviderException;
                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASAggregatorHelpers<CONNECTOR_TYPE>::deleteShellsAasId(const std::string & t_identifier)
            {
                ApiAssetAdminstrationShell<CONNECTOR_TYPE> aasApi(m_connector, m_parent);

                UA_StatusCode status = aasApi.deleteAssetAdministrationShell(t_identifier);
                if (status != UA_STATUSCODE_GOOD)
                    return basyx::object::error::ProviderException;
                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASAggregatorHelpers<CONNECTOR_TYPE>::getShellsAasidAasSubmodels(const std::string & t_identifier)
            {
                ApiAssetAdminstrationShell<CONNECTOR_TYPE> aasApi(m_connector, m_parent);

                auto submodels = aasApi.getAllSubmodels(t_identifier);

                basyx::object smList = basyx::object::make_list<basyx::object>();

                std::for_each(submodels.begin(), submodels.end(),[&](std::unique_ptr<Submodel_t> & t_sm) {
                    smList.insert(t_sm->getMap());
                });
                return smList;
            }
        }
    }
}
#endif