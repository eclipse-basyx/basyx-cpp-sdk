/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef API_PROPERTY_H_
#define API_PROPERTY_H_

#include <BaSyx/log/log.h>
#include <BaSyx/opcua/aas/node/PropertyNodeManager.h>
#include <BaSyx/opcua/aas/api_v2/ApiHelpers.h>
#include <BaSyx/opcua/aas/api_v2/ApiMetamodelUtilities.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            template<typename CONNECTOR_TYPE>
            class ApiProperty
            {
                static constexpr const char* loggerName = "ApiProperty";
            public:
                ApiProperty(CONNECTOR_TYPE& t_connector, const NodeId& t_parent) :
                    m_logger(loggerName),
                    m_connector(t_connector),
                    m_propNodeHandler(util::make_unique<PropertyNodeManager<CONNECTOR_TYPE>>(t_connector, t_parent)){}

                // APIs
                template<typename TYPE>
                UA_StatusCode createProperty(const Property_t<TYPE>& t_property);

                UA_StatusCode createProperty(const IProperty_t& t_property);

                UA_StatusCode deleteProperty(const std::string& t_idShort);

                template<typename TYPE>
                std::unique_ptr<Property_t<TYPE>> getProperty(const std::string& t_idShort);

                std::unique_ptr<IProperty_t> getProperty(const std::string& t_idShort);

                // Propety attribute modification helpers
                template<typename TYPE>
                UA_StatusCode setValue(const std::string& t_idShort, const TYPE& t_value);

                template<typename TYPE>
                UA_StatusCode getValue(const std::string& t_idShort, TYPE& t_value);

                UA_StatusCode setValueType(const std::string& t_idShort, const std::string& t_valueTypeStr);

                UA_StatusCode getValueType(const std::string& t_idShort, std::string& t_valueTypeStr);

                UA_StatusCode setIdShort(const std::string& t_idShort, const std::string& t_idShortStr);

                UA_StatusCode getIdShort(const std::string& t_idShort, std::string& t_idShortStr);

                UA_StatusCode setKind(const std::string& t_idShort, const std::string& t_valueKindStr);

                UA_StatusCode getKind(const std::string& t_idShort, std::string& t_valueKindStr);

                UA_StatusCode setCategory(const std::string& t_idShort, const std::string& t_category);

                UA_StatusCode getCategory(const std::string& t_idShort, std::string& t_category);

                UA_StatusCode setQualifier(const std::string& t_idShort, const std::string& t_qualifier);

                UA_StatusCode getQualifier(const std::string& t_idShort, std::string& t_qualifier);

            private:

                NodeId resolveAttributeNode(const std::string& t_idShort, const BrowsePath & t_browseName);

            private:
                std::unique_ptr<PropertyNodeManager<CONNECTOR_TYPE>> m_propNodeHandler;
                CONNECTOR_TYPE& m_connector;
                basyx::log m_logger;
            };

            template<typename CONNECTOR_TYPE>template<typename TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::createProperty(const Property_t<TYPE>& t_property)
            {
                using namespace aas::metamodel;
                using namespace basyx::xsd_types;

                t_property.getDescription();

                Services<CONNECTOR_TYPE> services(m_connector);

                UA_StatusCode status = UA_STATUSCODE_BADUNKNOWNRESPONSE;

                NodeId propOutNode, valueNode;

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                status = m_propNodeHandler->retrieve(t_property.getIdShort(), propOutNode);

                // Check is the property is existing, if so delete it (UDPATE semantics)
                if ((status == UA_STATUSCODE_GOOD) && !propOutNode.isNull())
                {
                    status = m_propNodeHandler->remove(t_property.getIdShort());

                    CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Propery node already exists and cannot be removed");
                }
                

                // Create Property Node
                status = m_propNodeHandler->create(t_property.getIdShort(), propOutNode, ApiHelpers::getNodeDescription(t_property.getDescription()));
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property node cannot be created");

                // Create value node
                status = services.addVariableNode(
                    propOutNode,
                    NodeId::numeric(UA_NS0ID_HASPROPERTY),
                    NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                    QualifiedName(nsIdx, AASPropertyType::AttrNames::BrowseText_Value),
                    VariableAttributes(
                        shared::I40TypesToOpcuaMap(t_property.getValue()),
                        AASPropertyType::AttrNames::DisplayName_Value,
                        AASPropertyType::AttrNames::Description_Value,
                        "en-US"),
                    valueNode
                );

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Value node cannot be added");

                CHECK_NODE_LOG_ERR_AND_RETURN(m_logger, valueNode, "Property Value node is null");
                
                // Set idShort
                status = setIdShort(t_property.getIdShort(), t_property.getIdShort());
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property IdShort cannot be written");

                // Set the value
                status = services.writeValue(valueNode, xsd_type<TYPE>::getXSDRepresentation(t_property.getValue()));
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property cannot be written");

                // Set ValueType
                status = setValueType(t_property.getIdShort(), t_property.getValueType());
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property ValueType cannot be set");
                
                // Set category
                if (auto catorgoryStr = t_property.getCategory())
                {
                    status = setCategory(t_property.getIdShort(), *catorgoryStr);
                    CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Category cannot be set");
                }
                    
                //Set Kind
                status = setKind(t_property.getIdShort(), basyx::aas::ModelingKind_::to_string(t_property.getKind()));
                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property ValueType cannot be set");

                //t_property.get
                // TODO
                // Qaulifiers, DataSpecReference, SemanticIds
                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::createProperty(const IProperty_t & t_property)
            {
                using namespace metamodel;

                std::string valueType = t_property.getValueType();

                if (valueType == AASPropertyType::TypeName::bool_)
                {
                    if (auto prop = dynamic_cast<const Property<bool>*>(&t_property))
                        return createProperty<bool>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::int8)
                {
                    if (auto prop = dynamic_cast<const Property<int8_t>*>(&t_property))
                        return createProperty<int8_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::uint8)
                {
                    if (auto prop = dynamic_cast<const Property<uint8_t>*>(&t_property))
                        return createProperty<uint8_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::int16)
                {
                    if (auto prop = dynamic_cast<const Property<int16_t>*>(&t_property))
                        return createProperty<int16_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::uint16)
                {
                    if (auto prop = dynamic_cast<const Property<uint16_t>*>(&t_property))
                        return createProperty<uint16_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::int32)
                {
                    if (auto prop = dynamic_cast<const Property<int32_t>*>(&t_property))
                        return createProperty<int32_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::uint32)
                { 
                    if (auto prop = dynamic_cast<const Property<uint32_t>*>(&t_property))
                        return createProperty<uint32_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::int64)
                {
                    if (auto prop = dynamic_cast<const Property<int64_t>*>(&t_property))
                        return createProperty<int64_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::uint64)
                { 
                    if (auto prop = dynamic_cast<const Property<uint64_t>*>(&t_property))
                        return createProperty<uint64_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::float_)
                { 
                    if (auto prop = dynamic_cast<const Property<float>*>(&t_property))
                        return createProperty<float>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::double_)
                { 
                    if (auto prop = dynamic_cast<const Property<double>*>(&t_property))
                        return createProperty<double>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::string_)
                {
                    if (auto prop = dynamic_cast<const Property<std::string>*>(&t_property))
                        return createProperty<std::string>(*prop);
                }
                // Complex types are encoded as string
                else if (valueType == AASPropertyType::TypeName::anyUri)
                {
                    if (auto prop = dynamic_cast<const Property<AnyURI_t>*>(&t_property))
                        return createProperty<AnyURI_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::date)
                {
                    if (auto prop = dynamic_cast<const Property<Date_t>*>(&t_property))
                        return createProperty<Date_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::time)
                {
                    if (auto prop = dynamic_cast<const Property<Time_t>*>(&t_property))
                        return createProperty<Time_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::dayTimeDuration)
                {
                    if (auto prop = dynamic_cast<const Property<DayTimeDuration_t>*>(&t_property))
                        return createProperty<DayTimeDuration_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::yearMonthDuration)
                {
                    if (auto prop = dynamic_cast<const Property<YearMonthDuration_t>*>(&t_property))
                        return createProperty<YearMonthDuration_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::dateTime)
                {
                    if (auto prop = dynamic_cast<const Property<DateTime_t>*>(&t_property))
                        return createProperty<DateTime_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::gDay)
                {
                    if (auto prop = dynamic_cast<const Property<GDay_t>*>(&t_property))
                        return createProperty<GDay_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::gMonth)
                {
                    if (auto prop = dynamic_cast<const Property<GMonth_t>*>(&t_property))
                        return createProperty<GMonth_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::gMonthDay)
                {
                    if (auto prop = dynamic_cast<const Property<GMonthDay_t>*>(&t_property))
                        return createProperty<GMonthDay_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::gYear)
                {
                    if (auto prop = dynamic_cast<const Property<GYear_t>*>(&t_property))
                        return createProperty<GYear_t>(*prop);
                }
                else if (valueType == AASPropertyType::TypeName::gYearMonth)
                {
                    if (auto prop = dynamic_cast<const Property<GYearMonth_t>*>(&t_property))
                        return createProperty<GYearMonth_t>(*prop);
                }
                else;
                m_logger.error("Value Type - [ " + valueType + " ] unknown");

                return UA_STATUSCODE_BADUNEXPECTEDERROR;
            }


            template<typename CONNECTOR_TYPE> template<typename TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::setValue(const std::string& t_idShort, const TYPE & t_value)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASPropertyType::AttrNames::BrowseText_Value)));

                UA_StatusCode status = services.writeValue(node, t_value);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Value node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE> template<typename TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::getValue(const std::string& t_idShort, TYPE & t_value)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASPropertyType::AttrNames::BrowseText_Value)));

                UA_StatusCode status = services.readValue(node, t_value);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Value node cannot be read");

                return status;
            }

            template<typename CONNECTOR_TYPE>template<typename TYPE>
            inline std::unique_ptr<Property_t<TYPE>> ApiProperty<CONNECTOR_TYPE>::getProperty(const std::string& t_idShort)
            {
                using namespace basyx::xsd_types;
                using namespace metamodel;

                TYPE value;
                std::string valueType, kind, category;

                // Read the attributes respective OPC UA nodes
                UA_StatusCode status = getValue(t_idShort, value);
                CHECK_STATUS_LOG_ERR_AND_RETURN_NULL(m_logger, status, std::string("Property [") + t_idShort + "] Value cannot be read");

                status = getValueType(t_idShort, valueType);
                CHECK_STATUS_LOG_ERR_AND_RETURN_NULL(m_logger, status, std::string("Property [") + t_idShort + "] ValueType cannot be read");

                status = getKind(t_idShort, kind);
                CHECK_STATUS_LOG_ERR_AND_RETURN_NULL(m_logger, status, std::string("Property [") + t_idShort + "] Kind cannot be read");

                status = getCategory(t_idShort, category);
                CHECK_STATUS_LOG_ERR_AND_RETURN_NULL(m_logger, status, std::string("Property [") + t_idShort + "] Category cannot be read");

               
                // TODO : Modelling Kind=Tempalte needs to be supported int the future

                auto prop{ util::make_unique< Property_t<TYPE>>(t_idShort) };
                prop->setValue(value);
                prop->setValueType(valueType);
                prop->setCategory(category);

                return prop;
            }

            template<typename CONNECTOR_TYPE>
            inline std::unique_ptr<IProperty_t> ApiProperty<CONNECTOR_TYPE>::getProperty(const std::string& t_idShort)
            {
                using namespace metamodel;

                std::string valueType;

                // Read the attributes respective OPC UA nodes
                UA_StatusCode status = getValueType(t_idShort, valueType);

                CHECK_STATUS_LOG_ERR_AND_RETURN_NULL(m_logger, status, std::string("Property [") + t_idShort + "] ValueType cannot be read");

                // Read the PropertyType based on the meta information in ValueType
                if (valueType == AASPropertyType::TypeName::bool_)
                    return getProperty<bool>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::int8)
                    return getProperty<int8_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::uint8)
                    return getProperty<uint8_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::int16)
                    return getProperty<int16_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::uint16)
                    return getProperty<uint16_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::int32)
                    return getProperty<int32_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::uint32)
                    return getProperty<uint32_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::int64)
                    return getProperty<int64_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::uint64)
                    return getProperty<uint64_t>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::float_)
                    return getProperty<float>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::double_)
                    return getProperty<double>(t_idShort);
                else if (valueType == AASPropertyType::TypeName::string_)
                    return getProperty<std::string>(t_idShort);
                // Complex types are encoded as string in OPC UA
                else {

                    auto propertyStr = getProperty<std::string>(t_idShort);
                    std::string valueStr = propertyStr->getValue();
                    std::string categoryStr =  propertyStr->getCategory() ? *propertyStr->getCategory() : std::string();
                    auto description = propertyStr->getDescription();

                    if (valueType == AASPropertyType::TypeName::anyUri)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<AnyURI_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::date)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<Date_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::time)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<Time_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::dayTimeDuration)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<DayTimeDuration_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::yearMonthDuration)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<YearMonthDuration_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::dateTime)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<DateTime_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::gDay)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<GDay_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::gMonth)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<GMonth_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::gMonthDay)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<GMonthDay_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::gYear)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<GYear_t>(valueStr, t_idShort, categoryStr, description);
                    else if (valueType == AASPropertyType::TypeName::gYearMonth)
                        return ApiMetamodelUtilities::makeXsdPropertyWithValue<GYearMonth_t>(valueStr, t_idShort, categoryStr, description);
                    else
                        m_logger.error("Property type unknown");
                }

                return nullptr;
            }
       
            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::deleteProperty(const std::string& t_idShort)
            {
                return m_propNodeHandler->remove(t_idShort);
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::setValueType(const std::string& t_idShort, const std::string & t_valueTypeStr)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASPropertyType::AttrNames::BrowseText_ValueType)));

                UA_StatusCode status = services.writeValue(node, t_valueTypeStr);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property ValueType node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::getValueType(const std::string& t_idShort, std::string & t_valueTypeStr)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASPropertyType::AttrNames::BrowseText_ValueType)));

                UA_StatusCode status = services.readValue(node, t_valueTypeStr);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property ValueType node cannot be read");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::setIdShort(const std::string& t_idShort, const std::string & t_idShortStr)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::IAASReferableType::AttrNames::BrowseText_IdShort)));

                UA_StatusCode status = services.writeValue(node, t_idShortStr);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property IdShort node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::getIdShort(const std::string& t_idShort, std::string & t_idShortStr)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::IAASReferableType::AttrNames::BrowseText_IdShort)));

                UA_StatusCode status = services.readValue(node, t_idShortStr);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property IdShort node cannot be read");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::setKind(const std::string& t_idShort, const std::string & t_valueKindStr)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASSubmodelElementType::AttrNames::BrowseText_Kind)));

                UA_StatusCode status = services.writeValue(node, t_valueKindStr);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Kind node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::getKind(const std::string& t_idShort, std::string & t_valueKindStr)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASSubmodelElementType::AttrNames::BrowseText_Kind)));

                UA_StatusCode status = services.readValue(node, t_valueKindStr);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Kind node cannot be read");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::setCategory(const std::string& t_idShort, const std::string & t_category)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::IAASReferableType::AttrNames::BrowseText_Category)));

                UA_StatusCode status = services.writeValue(node, t_category);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Category node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::getCategory(const std::string& t_idShort, std::string & t_category)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::IAASReferableType::AttrNames::BrowseText_Category)));

                UA_StatusCode status = services.readValue(node, t_category);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Category node cannot be read");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::setQualifier(const std::string& t_idShort, const std::string & t_qualifier)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASSubmodelElementType::AttrNames::BrowseText_Qualifier)));

                UA_StatusCode status = services.writeValue(node, t_qualifier);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Qualifier node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline UA_StatusCode ApiProperty<CONNECTOR_TYPE>::getQualifier(const std::string& t_idShort, std::string & t_qualifier)
            {
                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                NodeId node = resolveAttributeNode(t_idShort, BrowsePath(BrowseName(nsIdx, metamodel::AASSubmodelElementType::AttrNames::BrowseText_Qualifier)));

                UA_StatusCode status = services.readValue(node, t_qualifier);

                CHECK_STATUS_LOG_ERR_AND_RETURN(m_logger, status, "Property Qualifier node cannot be written");

                return status;
            }

            template<typename CONNECTOR_TYPE>
            inline NodeId ApiProperty<CONNECTOR_TYPE>::resolveAttributeNode(const std::string& t_idShort, const BrowsePath & t_browsePath)
            {
                BrowsePath browsePath = t_browsePath;

                NodeId propertyNode, attrNode;

                Services<CONNECTOR_TYPE> services(m_connector);

                auto nsIdx = services.getNameSpaceIndex(opcua::shared::Namespaces::BASYX_NS_URI);

                UA_StatusCode status = m_propNodeHandler->retrieve(t_idShort, propertyNode);

                CHECK_STATUS_LOG_ERR_AND_RETURN_OBJECT(m_logger, status, NodeId::nullNode(), "Property node can be resolved");

                status = services.translateBrowsePathToNodeIdService(t_browsePath, propertyNode, attrNode);

                CHECK_NODE_LOG_ERR_AND_RETURN_NODE(m_logger,
                    attrNode,
                    std::string("Property node with BrowsePath [ ") + browsePath.toString() + std::string("] is null"));

                return attrNode;
            }

        }
    }
}

#endif