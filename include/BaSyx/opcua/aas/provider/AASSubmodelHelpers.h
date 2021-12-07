/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_SUBMODEL_HELPERS_H
#define AAS_SUBMODEL_HELPERS_H

#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/opcua/aas/provider/AASObjectDeserializer.h>
#include <BaSyx/opcua/aas/api_v2/ApiSubmodel.h>
#include <BaSyx/opcua/aas/api_v2/ApiProperty.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class AASSubmodelHelpers
            {
            public:
                AASSubmodelHelpers(CONNECTOR_TYPE& t_connector, const NodeId& t_parent)
                    : m_connector(t_connector), m_parent(t_parent) {}

                basyx::object getSubmodel(const std::string& t_smIdShort);

                basyx::object getSubmodelValues(const std::string& t_smIdShort);

                basyx::object::error putSubmodel(basyx::object t_submodelObject);

                basyx::object::error deleteSubmodel(const std::string& t_smIdShort);

                basyx::object  getSubmodelSubmodelElements(const std::string& t_smIdShort);

                basyx::object  getSubmodelSubmodelElement(const std::string& t_smIdShort,
                    const std::string& t_smeIdShort);

                basyx::object::error  putSubmodelSubmodelElement(const std::string& t_smIdShort,
                    const std::string& t_smeIdShort, basyx::object t_sme);

                basyx::object::error  deleteSubmodelSubmodelElement(const std::string& t_smIdShort,
                    const std::string& t_smeIdShort);

                basyx::object  getSubmodelSubmodelElementValue(const std::string& t_smIdShort,
                    const std::string& t_smeIdShort);

                basyx::object::error  putSubmodelSubmodelElementValue(const std::string& t_smIdShort,
                    const std::string& t_smeIdShort, basyx::object t_value);

            private:
                NodeId getSubmodelNode(const std::string& t_idShort);

                basyx::object::error putProperty(const std::string& t_smIdShort,
                    const std::string& t_valueType,
                    basyx::object t_propObject);

                template<typename TYPE>
                basyx::object::error createProperty(const std::string& t_smIdShort,
                    basyx::object t_propObject);
            private:
                CONNECTOR_TYPE& m_connector;
                NodeId m_parent;
            };

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelHelpers<CONNECTOR_TYPE>::getSubmodel(const std::string & t_smIdShort)
            {
                ApiSubmodel<CONNECTOR_TYPE> smApi(m_connector, m_parent);

                auto sm = smApi.getSubmodel(t_smIdShort);
                if (sm)
                    return sm->getMap();
                return basyx::object::make_error(basyx::object::error::PropertyNotFound);
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelHelpers<CONNECTOR_TYPE>::getSubmodelValues(const std::string & t_smIdShort)
            {
                ApiSubmodel<CONNECTOR_TYPE> smApi(m_connector, m_parent);
                basyx::object list_body = basyx::object::make_list<basyx::object>();

                basyx::object smEles = getSubmodelSubmodelElements(t_smIdShort);
                if (smEles.IsError())
                    return smEles;

                for (auto& smEle : smEles.template Get<basyx::object::object_map_t>())
                {
                    auto idShort = smEle.first;
                    auto value = smEle.second.getProperty(Element::value);
                    if (!value.IsError())
                    {
                        auto values_map = basyx::object::make_map();
                        values_map.insertKey(Element::idShort, idShort);
                        values_map.insertKey(Element::value, value);
                        values_map.insertKey(Element::valueType, smEle.second.getProperty(Element::valueType));
                        list_body.insert(std::move(values_map));
                    }
                }
                return list_body;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::putSubmodel(basyx::object t_submodelObject)
            {
                ApiSubmodel<CONNECTOR_TYPE> smApi(m_connector, m_parent);

                auto smInst = AASObjectDeserializer::makeSubmodel(t_submodelObject);
                UA_StatusCode status = smApi.createSubmodel(*smInst);
                if (status != UA_STATUSCODE_GOOD)
                    return basyx::object::error::ProviderException;
                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::deleteSubmodel(const std::string & t_smIdShort)
            {
                ApiSubmodel<CONNECTOR_TYPE> smApi(m_connector, m_parent);

                UA_StatusCode status = smApi.deleteSubmodel(t_smIdShort);
                if (status != UA_STATUSCODE_GOOD)
                    return basyx::object::error::ProviderException;
                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelHelpers<CONNECTOR_TYPE>::getSubmodelSubmodelElements(const std::string & t_smIdShort)
            {
                auto smObj = getSubmodel(t_smIdShort);
                if (smObj.IsError())
                    return smObj;
                return smObj.getProperty(Element::submodelElements);
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelHelpers<CONNECTOR_TYPE>::getSubmodelSubmodelElement(const std::string & t_smIdShort,
                const std::string & t_smeIdShort)
            {
                basyx::object smeObj = getSubmodelSubmodelElements(t_smIdShort);
                
                if (smeObj.IsError())
                    return smeObj;
                return smeObj.getProperty(t_smeIdShort);
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::putSubmodelSubmodelElement(const std::string & t_smIdShort,
                const std::string & t_smeIdShort, basyx::object t_sme)
            {

                auto modelType = t_sme.getProperty(Element::modelType);
                auto valueType = t_sme.getProperty(Element::valueType);

                if (!modelType.IsError())
                {
                    auto name = modelType.getProperty(Element::name);
                    if (!name.IsError())
                    {
                        auto nameValue = name.Get<std::string>();
                        if (nameValue == Element::property)
                            return putProperty(t_smIdShort, valueType.Get<std::string>(), t_sme);
                        // TODO: Remaining Submodelelements needs to be handled
                    }
                }
                return modelType.getError();
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::deleteSubmodelSubmodelElement(const std::string & t_smIdShort,
                const std::string & t_smeIdShort)
            {
                // TODO: Remaining Submodelelements needs to be handled
                ApiProperty<CONNECTOR_TYPE> propApi(m_connector, getSubmodelNode(t_smIdShort));

                UA_StatusCode status = propApi.deleteProperty(t_smeIdShort);
                if (status != UA_STATUSCODE_GOOD)
                    return basyx::object::error::ProviderException;
                return basyx::object::error::None;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object AASSubmodelHelpers<CONNECTOR_TYPE>::getSubmodelSubmodelElementValue(const std::string & t_smIdShort,
                const std::string & t_smeIdShort)
            {
                auto smEleObj = getSubmodelSubmodelElement(t_smIdShort, t_smeIdShort);

                return smEleObj.getProperty(Element::value);
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::putSubmodelSubmodelElementValue(const std::string & t_smIdShort,
                const std::string & t_smeIdShort, basyx::object t_value)
            {
                basyx::object smeObj = getSubmodelSubmodelElement(t_smIdShort, t_smeIdShort);

                if (smeObj.IsError())
                    return smeObj.getError();
                // Write the new value
                smeObj.insertKey(Element::value, t_value);
                // TODO : Needs to be optimized in future. Only value attribute should
                // be written, not the entire property
                return putSubmodelSubmodelElement(t_smIdShort, t_smeIdShort, smeObj);
            }

            template<typename CONNECTOR_TYPE>
            inline NodeId AASSubmodelHelpers<CONNECTOR_TYPE>::getSubmodelNode(const std::string& t_idShort)
            {
                NodeId smNode;

                SubmodelNodeManager<CONNECTOR_TYPE> nodeMgr(m_connector, m_parent);

                UA_StatusCode status = nodeMgr.retrieve(t_idShort, smNode);

                if ((status != UA_STATUSCODE_GOOD) || (smNode.isNull()))
                    return NodeId::nullNode();

                return smNode;
            }

            template<typename CONNECTOR_TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::putProperty(const std::string& t_smIdShort,
                const std::string& t_valueType,
                basyx::object t_propObject)
            {
                using namespace metamodel;
                // Read the PropertyType based on the meta information in ValueType
                if (t_valueType == AASPropertyType::TypeName::bool_)
                    return createProperty<bool>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::int8)
                    return createProperty<int8_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::uint8)
                    return createProperty<uint8_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::int16)
                    return createProperty<int16_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::uint16)
                    return createProperty<uint16_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::int32)
                    return createProperty<int32_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::uint32)
                    return createProperty<uint32_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::int64)
                    return createProperty<int64_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::uint64)
                    return createProperty<uint64_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::float_)
                    return createProperty<float>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::double_)
                    return createProperty<double>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::string_)
                    return createProperty<std::string>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::anyUri)
                    return createProperty<AnyURI_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::date)
                    return createProperty<Date_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::time)
                    return createProperty<Time_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::dayTimeDuration)
                    return createProperty<DayTimeDuration_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::yearMonthDuration)
                    return createProperty<YearMonthDuration_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::dateTime)
                    return createProperty<YearMonthDuration_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::gDay)
                    return createProperty<GDay_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::gMonth)
                    return createProperty<GMonth_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::gMonthDay)
                    return createProperty<GMonthDay_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::gYear)
                    return createProperty<GYear_t>(t_smIdShort, t_propObject);
                else if (t_valueType == AASPropertyType::TypeName::gYearMonth)
                    return createProperty<GYearMonth_t>(t_smIdShort, t_propObject);
                else;

                return basyx::object::error::ProviderException;
            }

            template<typename CONNECTOR_TYPE>template<typename TYPE>
            inline basyx::object::error AASSubmodelHelpers<CONNECTOR_TYPE>::createProperty(const std::string& t_smIdShort,
                basyx::object t_propObject)
            {
                ApiProperty<CONNECTOR_TYPE> propApi(m_connector, getSubmodelNode(t_smIdShort));

                auto propInst = AASObjectDeserializer::makeProperty<TYPE>(t_propObject);
                if (propInst)
                {
                    UA_StatusCode status = propApi.createProperty(*propInst.get());
                    if (status == UA_STATUSCODE_GOOD)
                        return basyx::object::error::None;
                }
                return basyx::object::error::ProviderException;
            }
        }
    }
}

#endif