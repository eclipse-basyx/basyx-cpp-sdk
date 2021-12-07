/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_2_OPCUA_HANDLERS_H
#define VAB_2_OPCUA_HANDLERS_H

#include <BaSyx/shared/object.h>
#include <BaSyx/log/log.h>
#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/opcua/provider/OPCUAModelProviderHelpers.h>
#include <BaSyx/opcua/typesmap/TypesMap.h>
#include <BaSyx/opcua/typesmap/TypesTransformer.h>

namespace basyx
{
    namespace opcua
    {
        namespace provider
        {
            template<typename CONNECTOR_TYPE>
            class VAB2OPCUAHandlers
            {
            public:
                VAB2OPCUAHandlers() = default;

                VAB2OPCUAHandlers(CONNECTOR_TYPE& t_connector, bool t_embedTypeMeta) :
                    m_connector(t_connector),
                    m_services(Services<CONNECTOR_TYPE>(t_connector)),
                    m_embedTypeMeta(t_embedTypeMeta) {}

                ~VAB2OPCUAHandlers() = default;

                UA_StatusCode createObject(const NodeId& t_parent,
                    const BrowsePath& t_path,
                    basyx::object t_object);

                UA_StatusCode createPrimitive(const NodeId& t_parent,
                    const BrowsePath& t_path,
                    object t_object);

                UA_StatusCode createMap(const NodeId& t_parent,
                    const BrowsePath& t_path,
                    basyx::object::object_map_t t_map);

                UA_StatusCode createList(const NodeId& t_parent,
                    const BrowsePath& t_path,
                    basyx::object::object_list_t t_list);

                UA_StatusCode createPrimitiveType(const NodeId& t_parent,
                    const BrowsePath& t_path,
                    basyx::object t_object);

                UA_StatusCode createPrimitveWithTypeMeta(const NodeId& t_parent,
                    const BrowsePath& t_path,
                    TypesMap::Type t_type,
                    const std::string& t_value);

                NodeId translateVABPathToNodeId(const std::string& t_vabPath);

                BrowsePath translateVABPathToBrowsePath(const std::string& t_vabPath,
                    uint16_t t_namespaceIndex);

                bool isObjectPrimitiveList(basyx::object& t_object);

                bool isObjectPrimitiveVariable(basyx::object& t_object);

                bool isNodePrimitive(const NodeId& t_node);

                template <typename TYPE>
                UA_StatusCode createPrimitive(const NodeId& t_parent, const BrowsePath& t_path, TYPE t_value) {

                    NodeId outNode;

                    if (t_parent.isNull())
                    {
                        basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                            "handlePrimitive() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                        );

                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    return OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(
                        m_connector,
                        t_parent,
                        TypesMap::BasyxPrimitiveType<TYPE>(t_value),
                        t_path,
                        t_value,
                        outNode
                    );

                }

                template<typename TYPE>
                UA_StatusCode createPrimitiveList(const NodeId& t_parent, const BrowsePath& t_path, basyx::object::list_t<TYPE> t_list)
                {
                    UA_StatusCode status;
                    NodeId newNode;

                    if (t_parent.isNull())
                    {
                        basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                            "handleList() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                        );

                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    auto collectionTypeNodeId = TypesMap::BasyxCollection<TYPE>(m_connector.getNamespaceIndexDefault());

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createObject(
                        m_connector,
                        t_parent,
                        collectionTypeNodeId,
                        t_path,
                        newNode
                    );

                    if (status != UA_STATUSCODE_GOOD) {
                        return status;
                    }

                    size_t idx(0);
                    for (const auto& item : t_list)
                    {
                        auto path = BrowsePath(t_path) + BrowsePath({ BrowseName(m_connector.getNamespaceIndexDefault(),
                            "idx_" + std::to_string(idx)) });

                        status = createPrimitive(newNode, path, item);

                        if (status != UA_STATUSCODE_GOOD) {
                            return status;
                        }

                        idx++;
                    }
                    return UA_STATUSCODE_GOOD;

                }
            private:
                CONNECTOR_TYPE& m_connector;
                Services<CONNECTOR_TYPE> m_services;
                bool m_embedTypeMeta;
            };

            template<typename CONNECTOR_TYPE>
            UA_StatusCode VAB2OPCUAHandlers<CONNECTOR_TYPE>::createObject(const NodeId& t_parent,
                const BrowsePath& t_path,
                basyx::object t_object)
            {
                UA_StatusCode status;

                if (t_parent.isNull())
                {
                    basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                        "handleObject() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                    );
                    return UA_STATUSCODE_BADNODEIDINVALID;
                }
                else if (//(t_object.GetObjectType() == basyx::type::objectType::Primitive) ||
                    (m_embedTypeMeta && TypesTransformer::isTypeEncapsulated(t_object)))
                {
                    status = createPrimitive(t_parent, t_path, t_object);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_object.GetObjectType() == basyx::type::objectType::Map)
                {
                    NodeId newNode;

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createObject(
                        m_connector,
                        t_parent,
                        TypesMap::BasyxMap(m_connector.getNamespaceIndexDefault()),
                        t_path,
                        newNode
                    );

                    if (status != UA_STATUSCODE_GOOD) {
                        return status;
                    }

                    if (!newNode.isNull())
                    {
                        status = createMap(newNode, t_path, object::object_cast<object::object_map_t>(t_object));

                        if (status != UA_STATUSCODE_GOOD) {
                            return status;
                        }
                    }
                }
                else if (t_object.GetObjectType() == basyx::type::objectType::List)
                {
                    NodeId newNode;

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createObject(
                        m_connector,
                        t_parent,
                        TypesMap::BasyxObjectCollection(m_connector.getNamespaceIndexDefault()),
                        t_path,
                        newNode
                    );

                    if (status != UA_STATUSCODE_GOOD) {
                        return status;
                    }

                    if (!newNode.isNull())
                    {
                        status = createList(newNode, t_path, object::object_cast<object::object_list_t>(t_object));

                        if (status != UA_STATUSCODE_GOOD) {
                            return status;
                        }
                    }
                }
                return UA_STATUSCODE_GOOD;
            }

            template<typename CONNECTOR_TYPE>
            UA_StatusCode VAB2OPCUAHandlers<CONNECTOR_TYPE>::createPrimitive(const NodeId& t_parent,
                const BrowsePath& t_path,
                object t_object)
            {
                UA_StatusCode status;

                if (t_parent.isNull())
                {
                    basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                        "handlePrimitive() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                    );

                    return UA_STATUSCODE_BADNODEIDINVALID;
                }

                /* Dealing with special OPCUA Types the are not specified in VAB */
                if ((m_embedTypeMeta && TypesTransformer::isTypeEncapsulated(t_object)))
                {
                    auto valuTuple = TypesTransformer::unpackValuePair(t_object);//TypesMap::fromString("");

                    auto valueString = std::get<0>(valuTuple);

                    auto type = TypesMap::fromString(std::get<1>(valuTuple));

                    return createPrimitveWithTypeMeta(t_parent, t_path, type, valueString);
                }

                if (t_object.GetValueType() == basyx::type::valueType::Bool)
                {
                    status = createPrimitiveType(t_parent, t_path, t_object);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::Float)
                {
                    status = createPrimitiveType(t_parent, t_path, t_object);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::Int)
                {
                    status = createPrimitiveType(t_parent, t_path, t_object);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::String)
                {
                    status = createPrimitiveType(t_parent, t_path, t_object);

                    if (status != UA_STATUSCODE_GOOD)
                    {
                        return status;
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::Null)
                {
                }
                return UA_STATUSCODE_GOOD;
            }

            template<typename CONNECTOR_TYPE>
            UA_StatusCode VAB2OPCUAHandlers<CONNECTOR_TYPE>::createMap(const NodeId& t_parent,
                const BrowsePath& t_path,
                basyx::object::object_map_t t_map)
            {
                UA_StatusCode status;

                if (t_parent.isNull())
                {
                    basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                        "handleMap() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                    );

                    return UA_STATUSCODE_BADNODEIDINVALID;
                }

                for (const auto& ele : t_map)
                {
                    auto path = BrowsePath(t_path) + BrowsePath({ BrowseName(m_connector.getNamespaceIndexDefault(), ele.first) });

                    if (basyx::type::valueType::Object == ele.second.GetValueType())
                    {
                        status = createObject(t_parent, path, ele.second);

                        if (status != UA_STATUSCODE_GOOD) {
                            return status;
                        }
                    }
                    else
                    {
                        status = createPrimitive(t_parent, path, ele.second);

                        if (status != UA_STATUSCODE_GOOD) {
                            return status;
                        }
                    }
                }
                return UA_STATUSCODE_GOOD;
            }

            template<typename CONNECTOR_TYPE>
            UA_StatusCode VAB2OPCUAHandlers<CONNECTOR_TYPE>::createList(const NodeId& t_parent,
                const BrowsePath& t_path,
                basyx::object::object_list_t t_list)
            {
                UA_StatusCode status;

                if (t_parent.isNull())
                {
                    basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                        "handleList() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                    );

                    return UA_STATUSCODE_BADNODEIDINVALID;
                }

                size_t idx(0);
                for (const auto& item : t_list)
                {
                    auto path = BrowsePath(t_path) + BrowsePath({ BrowseName(m_connector.getNamespaceIndexDefault(),
                        "idx_" + std::to_string(idx)) });

                    if (basyx::type::valueType::Object == item.GetValueType())
                    {
                        status = createObject(t_parent, path, item);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                    else
                    {
                        status = createPrimitive(t_parent, path, item);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                    idx++;
                }
                return UA_STATUSCODE_GOOD;
            }

            template<typename CONNECTOR_TYPE>
            UA_StatusCode VAB2OPCUAHandlers<CONNECTOR_TYPE>::createPrimitiveType(const NodeId& t_parent,
                const BrowsePath& t_path,
                basyx::object t_object)
            {
                UA_StatusCode status;

                if (t_parent.isNull())
                {
                    basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                        "handlePrimitiveType() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                    );

                    return UA_STATUSCODE_BADNODEIDINVALID;
                }

                if (t_object.GetValueType() == basyx::type::valueType::Bool)
                {
                    if (t_object.InstanceOf<basyx::object::list_t<bool>>())
                    {
                        status = createPrimitiveList(t_parent, t_path, basyx::object::object_cast<basyx::object::list_t<bool>>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                    }
                    else
                    {
                        status = createPrimitive(t_parent, t_path, object::object_cast<bool>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::Float)
                {
                    if (t_object.InstanceOf<basyx::object::list_t<double>>())
                    {
                        status = createPrimitiveList(t_parent, t_path, basyx::object::object_cast<basyx::object::list_t<double>>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                    else
                    {
                        status = createPrimitive(t_parent, t_path, object::object_cast<double>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::Int)
                {
                    if (t_object.InstanceOf<basyx::object::list_t<int>>())
                    {
                        status = createPrimitiveList(t_parent, t_path, basyx::object::object_cast<basyx::object::list_t<int>>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                    else
                    {
                        status = createPrimitive(t_parent, t_path, object::object_cast<int>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                }
                else if (t_object.GetValueType() == basyx::type::valueType::String)
                {
                    if (t_object.InstanceOf<basyx::object::list_t<std::string>>())
                    {
                        status = createPrimitiveList(t_parent, t_path, basyx::object::object_cast<basyx::object::list_t<std::string>>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                    else
                    {
                        status = createPrimitive(t_parent, t_path, object::object_cast<std::string>(t_object));

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }
                    }
                }
                return UA_STATUSCODE_GOOD;
            }

            template<typename CONNECTOR_TYPE>
            NodeId VAB2OPCUAHandlers<CONNECTOR_TYPE>::translateVABPathToNodeId(const std::string& t_vabPath)
            {
                auto basyxNameSpace = m_connector.getNameSpaceIndex(shared::Namespaces::BASYX_NS_URI);

                if (basyxNameSpace == Client::NAMESPACE_UNKOWN)
                {
                    return NodeId::nullNode();
                }

                auto browsePath = BrowsePath::build(basyxNameSpace, t_vabPath);

                return m_connector.translateBrowsePathToNodeId(browsePath);
            }

            template<typename CONNECTOR_TYPE>
            BrowsePath VAB2OPCUAHandlers<CONNECTOR_TYPE>::translateVABPathToBrowsePath(const std::string& t_vabPath,
                uint16_t t_namespaceIndex)
            {
                return BrowsePath::build(t_namespaceIndex, t_vabPath);
            }

            template<typename CONNECTOR_TYPE>
            UA_StatusCode VAB2OPCUAHandlers<CONNECTOR_TYPE>::createPrimitveWithTypeMeta(const NodeId& t_parent,
                const BrowsePath& t_path,
                TypesMap::Type t_type,
                const std::string& t_value)
            {
                NodeId outNode;
                UA_StatusCode status;

                if (t_parent.isNull())
                {
                    basyx::log::topic("basyx::opcua::provider::VAB2OPCUAHandlers").error(
                        "handlePrimitive() - Path = " + BrowsePath(t_path).toString() + " parent NodeId is null"
                    );

                    return UA_STATUSCODE_BADNODEIDINVALID;
                }

                NodeId typeNode(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, TypesMap::getOPCUATypeId(t_type));

                switch (t_type)
                {
                case TypesMap::Type::Boolean:
                {
                    auto value = TypesTransformer::string_cast<bool>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::Int8:
                {
                    auto value = TypesTransformer::string_cast<int8_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::Int16:
                {
                    auto value = TypesTransformer::string_cast<int16_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::Int32:
                {
                    auto value = TypesTransformer::string_cast<int32_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::Int64:
                {
                    auto value = TypesTransformer::string_cast<int64_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }

                case TypesMap::Type::UInt8:
                {
                    auto value = TypesTransformer::string_cast<uint8_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::UInt16:
                {
                    auto value = TypesTransformer::string_cast<uint16_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::UInt32:
                {
                    auto value = TypesTransformer::string_cast<uint32_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::UInt64:
                {
                    auto value = TypesTransformer::string_cast<uint64_t>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }

                case TypesMap::Type::Float:
                {
                    float value = TypesTransformer::string_cast<float>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::Double:
                {
                    double value = TypesTransformer::string_cast<double>(t_value);

                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, value, outNode);

                    break;
                }
                case TypesMap::Type::String:
                {
                    status = OPCUAModelProviderHelpers<CONNECTOR_TYPE>::createVariable(m_connector, t_parent, typeNode, t_path, t_value, outNode);

                    break;
                }
                default:
                {
                    status = UA_STATUSCODE_BADDATATYPEIDUNKNOWN;
                }
                }
                return status;
            }

            template<typename CONNECTOR_TYPE>
            bool VAB2OPCUAHandlers<CONNECTOR_TYPE>::isObjectPrimitiveList(basyx::object& t_object)
            {
                return ((t_object.InstanceOf<basyx::object::list_t<bool>>()) ||
                    (t_object.InstanceOf<basyx::object::list_t<int32_t>>()) ||
                    (t_object.InstanceOf<basyx::object::list_t<double>>()) ||
                    (t_object.InstanceOf<basyx::object::list_t<std::string>>())
                    );
            }

            template<typename CONNECTOR_TYPE>
            bool VAB2OPCUAHandlers<CONNECTOR_TYPE>::isObjectPrimitiveVariable(basyx::object& t_object)
            {
                return ((t_object.InstanceOf<bool>()) ||
                    (t_object.InstanceOf<int32_t>()) ||
                    (t_object.InstanceOf<double>()) ||
                    (t_object.InstanceOf<std::string>())
                    );
            }

            template<typename CONNECTOR_TYPE>
            bool VAB2OPCUAHandlers<CONNECTOR_TYPE>::isNodePrimitive(const NodeId & t_node)
            {
                const NodeId dataType(m_services.getDataType(t_node));

                return ((TypesMap::BasyxBool() == dataType) ||
                    (TypesMap::BasyxInt() == dataType) ||
                    (TypesMap::BasyxDouble() == dataType) ||
                    (TypesMap::BasyxString() == dataType));
            }
        }
    }
}
#endif
