/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef SUBMODEL_PROVIDER_H
#define SUBMODEL_PROVIDER_H

#include <BaSyx/shared/object.h>
#include <BaSyx/log/log.h>
#include <BaSyx/shared/types.h>
#include <BaSyx/vab/core/IModelProvider.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/provider/AASSubmodelHelpers.h>
#include <BaSyx/opcua/aas/provider/AASProviderApiParseHelpers.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class AASSubmodelProvider : public vab::core::IModelProvider
            {
                static constexpr const char loggerName[] = "AASSubmodelProvider";
            public:

                AASSubmodelProvider(CONNECTOR_TYPE& t_connector, const NodeId& t_rootNode)
                    : m_connector(t_connector), m_rootNode(t_rootNode), m_logger(basyx::log(loggerName)) {}

                /* REST GET */
                virtual basyx::object getModelPropertyValue(const std::string& t_path) override
                {
                    return parseGet(t_path);
                }

                /* REST PUT */
                virtual basyx::object::error setModelPropertyValue(const std::string& t_path, const basyx::object t_newValue) override
                {
                    return parsePut(t_path, t_newValue);
                }

                /* REST POST */
                virtual basyx::object::error createValue(const std::string& t_path, const basyx::object t_newValue) override
                {
                    return basyx::object::error::None;
                }

                /* IGNORED */
                virtual basyx::object::error deleteValue(const std::string& t_path, basyx::object t_deletedValue) override
                {
                    return basyx::object::error::None;
                }

                /* REST DELETE */
                virtual basyx::object::error deleteValue(const std::string& t_path) override
                {
                    return parseDelete(t_path);
                }

                /* REST POST */
                virtual basyx::object invokeOperation(const std::string& t_path, basyx::object t_parameters) override
                {
                    return basyx::object::make_null();
                }

            private:
                basyx::object parseGet(const std::string& t_path);
                basyx::object::error parsePut(const std::string& t_path, basyx::object t_value);
                basyx::object::error parseDelete(const std::string& t_path);
                basyx::object invoke(const std::string& t_path, basyx::object t_parameters);
            private:
                CONNECTOR_TYPE& m_connector;
                NodeId m_rootNode;
                basyx::log m_logger;
            };

            template<typename CONNECTOR_TYPE>
            constexpr char AASSubmodelProvider<CONNECTOR_TYPE>::loggerName[];

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelProvider<CONNECTOR_TYPE>::parseGet(const std::string & t_path)
            {
                vab::core::VABPath path{ t_path };
                auto ids{ AASProviderApiParseHelpers::parseIdentifiers(vab::core::VABPath(t_path)) };
                AASSubmodelHelpers<CONNECTOR_TYPE> smHelper(m_connector, m_rootNode);

                /* GET : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort}/value */
                if (AASProviderApiParseHelpers::isAPISubmodelElementsValue(path))
                {
                    return smHelper.getSubmodelSubmodelElementValue(std::get<SM_ID>(ids), std::get< SM_ELE_ID>(ids));
                }
                /* GET : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort} */
                else if (AASProviderApiParseHelpers::isAPISubmodelElementsIdShort(path))
                {
                    return smHelper.getSubmodelSubmodelElement(std::get<SM_ID>(ids), std::get< SM_ELE_ID>(ids));
                }
                /* GET : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements */
                else if (AASProviderApiParseHelpers::isAPISubmodelElements(path))
                {
                    return smHelper.getSubmodelSubmodelElements(std::get<SM_ID>(ids));
                }
                /* GET : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/values */
                else if (AASProviderApiParseHelpers::isAPISubmodelValues(path))
                {
                    return smHelper.getSubmodelValues(std::get<SM_ID>(ids));
                }
                /* GET : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel */
                else if (AASProviderApiParseHelpers::isAPISubmodelsSubmodel(path))
                {
                    return smHelper.getSubmodel(std::get<SM_ID>(ids));
                }
                /* API : shells/{aasID}/aas/submodels/{submodelIdshort} */
                else if (AASProviderApiParseHelpers::isAPISubmodelsIdShort(path))
                {
                    return smHelper.getSubmodel(std::get<SM_ID>(ids));
                }
                else;

                return basyx::object::make_error(basyx::object::error::MalformedRequest, "Unknown request");
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelProvider<CONNECTOR_TYPE>::parsePut(const std::string & t_path,
                basyx::object t_value)
            {
                vab::core::VABPath path{ t_path };
                auto ids{ AASProviderApiParseHelpers::parseIdentifiers(vab::core::VABPath(t_path)) };
                AASSubmodelHelpers<CONNECTOR_TYPE> smHelper(m_connector, m_rootNode);

                /* UPDATE : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort}/value */
                if (AASProviderApiParseHelpers::isAPISubmodelElementsValue(path))
                {
                    return smHelper.putSubmodelSubmodelElementValue(std::get<SM_ID>(ids), std::get< SM_ELE_ID>(ids), t_value);
                }
                /* CREATE : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort} */
                else if (AASProviderApiParseHelpers::isAPISubmodelElementsIdShort(path))
                {
                    return smHelper.putSubmodelSubmodelElement(std::get<SM_ID>(ids), std::get< SM_ELE_ID>(ids), t_value);
                }
                /* CREATE : shells/{aasID}/aas/submodels/{submodelIdshort} */
                else if (AASProviderApiParseHelpers::isAPISubmodelsIdShort(path))
                {
                    //TODO : check identifier consistency
                    return smHelper.putSubmodel(t_value);
                }
                return basyx::object::error::PropertyNotFound;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelProvider<CONNECTOR_TYPE>::parseDelete(const std::string & t_path)
            {
                vab::core::VABPath path{ t_path };
                auto ids{ AASProviderApiParseHelpers::parseIdentifiers(vab::core::VABPath(t_path)) };
                AASSubmodelHelpers<CONNECTOR_TYPE> smHelper(m_connector, m_rootNode);

                /* DELETE : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort} */
                if (AASProviderApiParseHelpers::isAPISubmodelElementsIdShort(path))
                {
                    return smHelper.deleteSubmodelSubmodelElement(std::get<SM_ID>(ids), std::get<SM_ELE_ID>(ids));
                }
                /* API : shells/{aasID}/aas/submodels/{submodelIdshort} */
                else if (AASProviderApiParseHelpers::isAPISubmodelsIdShort(path))
                {
                    return smHelper.deleteSubmodel(std::get<SM_ID>(ids));
                }
                return basyx::object::error::MalformedRequest;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelProvider<CONNECTOR_TYPE>::invoke(const std::string & t_path, basyx::object t_parameters)
            {
                return basyx::object::make_null();
            }
        }
    }
}

#endif