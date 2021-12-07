/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_2_VAB_HANDLERS_H
#define OPCUA_2_VAB_HANDLERS_H

#include <BaSyx/log/log.h>
#include <BaSyx/shared/object.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/typesmap/TypesMap.h>
#include <BaSyx/opcua/typesmap/TypesTransformer.h>
#include <BaSyx/opcua/provider/OPCUAModelProviderHelpers.h>


namespace basyx
{
    namespace opcua
    {
        namespace provider
        {
            template<typename CONNECTOR_TYPE>
            class OPCUA2VabHandlers {
            public:
                OPCUA2VabHandlers() = default;

                OPCUA2VabHandlers(CONNECTOR_TYPE& t_connector, bool t_embedTypeMeta) :
                    m_connector(t_connector),
                    m_embedTypeMeta(t_embedTypeMeta),
                    m_services(Services<CONNECTOR_TYPE>(t_connector)) {}

                ~OPCUA2VabHandlers() = default;

                basyx::object::object_map_t getBasyxMap(const NodeId& t_mapNode);

                basyx::object::object_list_t getBasyxObjectCollection(const NodeId& t_objectListNode);

                basyx::object getBasyxObject(const NodeId& t_node);

                UA_StatusCode writePrimitive(const NodeId& t_node, basyx::object t_value);

                template<typename TYPE>
                basyx::object::list_t<TYPE> handleBasyxCollection(const NodeId& t_primiliveList)
                {
                    basyx::object retList = basyx::object::make_list<TYPE>({});

                    for (const auto& child : m_services.getChildReferences(
                        t_primiliveList,
                        NodeId::numeric(UA_NS0ID_HASPROPERTY)))
                    {
                        auto valueObj = readPrimiviteValue<TYPE>(child.getUANode());

                        auto valueType = m_services.getHasTypeDefinition(child);

                        retList.insert(std::move(basyx::object::object_cast<TYPE>(valueObj)));
                    }

                    return std::move(basyx::object::object_cast<basyx::object::list_t<TYPE>>(retList));
                }

                template<typename TYPE>
                basyx::object readPrimiviteValue(const NodeId& t_node)
                {
                    TYPE val;
                    //TODO status not handled
                    auto status = m_services.template readValue<TYPE>(t_node, val);

                    if (status != UA_STATUSCODE_GOOD)
                        return basyx::object::make_error(
                            basyx::object::error::ProviderException, shared::diag::getErrorString(status)
                        );

                    return basyx::object(val);
                }
            private:
                CONNECTOR_TYPE& m_connector;
                bool m_embedTypeMeta;
                Services<CONNECTOR_TYPE> m_services;
            };

            template<typename CONNECTOR_TYPE>
            basyx::object::object_map_t OPCUA2VabHandlers<CONNECTOR_TYPE>::getBasyxMap(const NodeId& t_mapNode)
            {
                auto name = m_services.getBrowseNameFromNodeId(t_mapNode).getText();

                auto retMap = basyx::object::make_map();

                for (const NodeId& child : m_services.getAllChildReferences(t_mapNode))
                {
                    if (!(child.isNull() ||
                        m_services.isNodeObjectType(child) ||
                        (NodeId::numeric(UA_NS0ID_MODELLINGRULE_MANDATORY) == child)))
                    {
                        auto type = m_services.getHasTypeDefinition(child);

                        auto childName = m_services.getBrowseNameFromNodeId(child).getText();

                        retMap.insertKey(childName, std::move(getBasyxObject(child.getUANode())));
                    }
                }
                return std::move(basyx::object::object_cast<basyx::object::object_map_t>(retMap));
            }

            template<typename CONNECTOR_TYPE>
            basyx::object::object_list_t OPCUA2VabHandlers<CONNECTOR_TYPE>::getBasyxObjectCollection(const NodeId& t_objectListNode)
            {
                auto name = m_services.getBrowseNameFromNodeId(t_objectListNode).getText();

                basyx::object retList = basyx::object::make_list<basyx::object>({});

                for (const auto& item : m_services.getAllChildReferences(t_objectListNode))
                {
                    auto type = m_services.getHasTypeDefinition(item);

                    if (!(item.isNull() || TypesMap::isBasyxTypeNode(item.getUANode(), m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI))))
                    {
                        retList.insert(std::move(getBasyxObject(item.getUANode())));
                    }
                }
                return basyx::object::object_cast<basyx::object::object_list_t>(retList);
            }

            template<typename CONNECTOR_TYPE>
            basyx::object OPCUA2VabHandlers<CONNECTOR_TYPE>::getBasyxObject(const NodeId& t_node)
            {
                auto type = m_services.getHasTypeDefinition(t_node).getUANode();

                if (TypesMap::PropertyType() == type)
                {
                    auto dataTypeNode = m_services.getDataType(t_node).getUANode();

                    if (m_embedTypeMeta)
                    {
                        basyx::object retObject;

                        auto status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::readPrimitveWithTypeMeta(m_connector, t_node.getUANode(), retObject);

                        return retObject;

                    }
                    else if (TypesMap::BasyxBool() == dataTypeNode)
                    {
                        return readPrimiviteValue<UA_Boolean>(t_node);
                    }
                    else if (TypesMap::BasyxInt() == dataTypeNode)
                    {
                        return readPrimiviteValue<UA_Int32>(t_node);
                    }
                    else if (TypesMap::BasyxDouble() == dataTypeNode)
                    {
                        return readPrimiviteValue<UA_Double>(t_node);
                    }
                    else if (TypesMap::BasyxString() == dataTypeNode)
                    {
                        return readPrimiviteValue<std::string>(t_node);
                    }
                }
                else if (TypesMap::BasyxMap(m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI)) == type)
                {
                    return getBasyxMap(t_node);
                }
                else if (TypesMap::BasyxObjectCollection(m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI)) == type)
                {
                    return getBasyxObjectCollection(t_node);
                }
                else if (TypesMap::BasyxBooleanCollection(m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI)) == type)
                {
                    return handleBasyxCollection<bool>(t_node.getUANode());
                }
                else if (TypesMap::BasyxIntCollection(m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI)) == type)
                {
                    return handleBasyxCollection<int>(t_node.getUANode());
                }
                else if (TypesMap::BasyxDoubleCollection(m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI)) == type)
                {
                    return handleBasyxCollection<double>(t_node.getUANode());
                }
                else if (TypesMap::BasyxStringCollection(m_services.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI)) == type)
                {
                    return handleBasyxCollection<std::string>(t_node.getUANode());
                }
                /* This is for existing NonVAB OPCUA models */
                else if (m_services.isNodeObject(t_node))
                {
                    return getBasyxMap(t_node);
                }
                return basyx::object::make_error(basyx::object::error::MalformedRequest, "Object type cannot be deduced");
            }

            template<typename CONNECTOR_TYPE>
            UA_StatusCode OPCUA2VabHandlers<CONNECTOR_TYPE>::writePrimitive(const NodeId & t_node, basyx::object t_value)
            {
                if (m_embedTypeMeta && TypesTransformer::isTypeEncapsulated(basyx::object(t_value)))
                {
                    return OPCUAModelProviderHelpers<CONNECTOR_TYPE>::writePrimitveWithTypeMeta(m_connector, t_node.getUANode(), t_value);
                }
                else if (t_value.InstanceOf<bool>())
                {
                    auto status = m_services.writeValue(t_node, basyx::object::object_cast<bool>(t_value));

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_value.InstanceOf<int32_t>())
                {
                    auto status = m_services.writeValue(t_node, basyx::object::object_cast<int>(t_value));

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_value.InstanceOf<double>())
                {
                    auto status = m_services.writeValue(t_node, basyx::object::object_cast<double>(t_value));

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else
                {
                    auto status = m_services.writeValue(t_node, basyx::object::object_cast<std::string>(t_value));

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                return UA_STATUSCODE_GOOD;
            }
        }
    }
}
#endif