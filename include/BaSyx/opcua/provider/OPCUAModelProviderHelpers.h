/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef OPCUA_MODEL_PROVIDER_HELPERS_H
#define OPCUA_MODEL_PROVIDER_HELPERS_H

#include <BaSyx/shared/object.h>
#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/typesmap/TypesMap.h>
#include <BaSyx/opcua/typesmap/TypesTransformer.h>

namespace basyx
{
    namespace opcua
    {
        namespace provider
        {

            template<typename CONNECTOR_TYPE>
            class OPCUAModelProviderHelpers
            {
            public:
                template<typename TYPE>
                static UA_StatusCode createVariable(CONNECTOR_TYPE& t_connector,
                    const NodeId& t_parentNode,
                    const NodeId& t_typeNodeId,
                    const BrowsePath& t_path,
                    TYPE t_value,
                    NodeId& t_outNode)
                {
                    UA_StatusCode status;

                    Services<CONNECTOR_TYPE>services(t_connector);

                    auto path = t_path;

                    if (t_parentNode.isNull())
                    {
                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    auto name = path.getLeafElement().getText();

                    status = services.addVariableNode(
                        t_parentNode,
                        NodeId::numeric(UA_NS0ID_HASPROPERTY),
                        NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                        QualifiedName(t_connector.getNamespaceIndexDefault(), name),
                        VariableAttributes(t_typeNodeId, name, name, "en-US"),
                        t_outNode
                    );

                    if (status != UA_STATUSCODE_GOOD) {
                        return status;
                    }

                    return services.template writeValue<TYPE>(t_outNode, t_value);
                }

                template<typename TYPE>
                static UA_StatusCode createVariableList(CONNECTOR_TYPE& t_connector,
                    const NodeId& t_parentNode,
                    const NodeId& t_typeNodeId,
                    const BrowsePath& t_path,
                    std::vector<TYPE> t_values,
                    NodeId& t_outNode)
                {
                    Services<CONNECTOR_TYPE> services(t_connector);
                    auto path = t_path;

                    if (t_parentNode.isNull())
                    {
                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    auto name = path.getLeafElement().getText();

                    return services.template addVariableNode(
                        t_parentNode,
                        NodeId::numeric(UA_NS0ID_HASPROPERTY),
                        NodeId::numeric(UA_NS0ID_PROPERTYTYPE),
                        VariableAttributes(UA_TYPES_STRING, name, name, "en-US"),
                        QualifiedName(services.getConnector().getNamespaceIndexDefault(), name),
                        t_outNode
                    );

                }

                template<typename TYPE>
                UA_StatusCode writeVariable(CONNECTOR_TYPE& t_connector,
                    const NodeId& t_parent,
                    const BrowsePath& t_path,
                    TYPE t_value)
                {
                    Services<CONNECTOR_TYPE> services(t_connector);

                    if (t_path.empty())
                    {
                        return UA_STATUSCODE_BADINVALIDARGUMENT;
                    }

                    if (t_parent.isNull())
                    {
                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    auto writeNode = t_connector.translateBrowsePathToNodeId(t_path);

                    if (writeNode.isNull())
                    {
                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    return services.template writeValue<TYPE>(writeNode, t_value);
                }

                static UA_StatusCode createObject(CONNECTOR_TYPE& t_connector,
                    const NodeId& t_parentNode,
                    const NodeId& t_typeNodeId,
                    const BrowsePath& t_path,
                    NodeId& t_outNode)
                {
                    auto path = t_path;

                    Services<CONNECTOR_TYPE> services(t_connector);

                    if (t_parentNode.isNull())
                    {
                        return UA_STATUSCODE_BADNODEIDINVALID;
                    }

                    auto name = path.getLeafElement().getText();

                    return services.addObjectNode(
                        t_parentNode,
                        t_typeNodeId,
                        NodeId::numeric(UA_NS0ID_HASCOMPONENT),
                        QualifiedName(t_connector.getNamespaceIndexDefault(), name),
                        ObjectAttributes(name, name, "en-US"),
                        t_outNode
                    );
                }

                static UA_StatusCode writePrimitveWithTypeMeta(CONNECTOR_TYPE& t_connector, const NodeId& t_node, basyx::object& t_object)
                {
                    NodeId outNode;
                    UA_StatusCode status;

                    Services<CONNECTOR_TYPE> services(t_connector);

                    auto valueTuple = TypesTransformer::unpackValuePair(t_object);

                    auto type = TypesMap::fromString(std::get<TypesTransformer::VALUE_TYPE_KEY_IDX>(valueTuple));

                    auto valueStr = std::get<TypesTransformer::VALUE_KEY_IDX>(valueTuple);

                    switch (type)
                    {
                    case TypesMap::Type::Boolean:
                    {
                        auto value = TypesTransformer::string_cast<bool>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::Int8:
                    {
                        auto value = TypesTransformer::string_cast<int8_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::Int16:
                    {
                        auto value = TypesTransformer::string_cast<int16_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::Int32:
                    {
                        auto value = TypesTransformer::string_cast<int32_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::Int64:
                    {
                        auto value = TypesTransformer::string_cast<int64_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }

                    case TypesMap::Type::UInt8:
                    {
                        auto value = TypesTransformer::string_cast<uint8_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::UInt16:
                    {
                        auto value = TypesTransformer::string_cast<uint16_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::UInt32:
                    {
                        auto value = TypesTransformer::string_cast<uint32_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::UInt64:
                    {
                        auto value = TypesTransformer::string_cast<uint64_t>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }

                    case TypesMap::Type::Float:
                    {
                        auto value = TypesTransformer::string_cast<float>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::Double:
                    {
                        auto value = TypesTransformer::string_cast<double>(valueStr);

                        status = services.writeValue(t_node, value);

                        break;
                    }
                    case TypesMap::Type::String:
                    {
                        status = services.writeValue(t_node, valueStr);

                        break;
                    }
                    default:
                    {
                        status = UA_STATUSCODE_BADDATATYPEIDUNKNOWN;
                    }
                    }
                    return status;
                }

                static UA_StatusCode readPrimitveWithTypeMeta(CONNECTOR_TYPE& t_connector, const NodeId & t_node, basyx::object& t_object)
                {
                    Services<CONNECTOR_TYPE> services(t_connector);

                    if (NodeId::numeric(UA_NS0ID_BOOLEAN) == services.getDataType(t_node))
                    {
                        UA_Boolean value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<bool>(value), TypesMap::Type::Boolean);
                    }
                    else if (NodeId::numeric(UA_NS0ID_SBYTE) == services.getDataType(t_node))
                    {
                        UA_SByte value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<int8_t>(value), TypesMap::Type::Int8);
                    }
                    else if (NodeId::numeric(UA_NS0ID_INT16) == services.getDataType(t_node))
                    {
                        UA_Int16 value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<int16_t>(value), TypesMap::Type::Int16);
                    }
                    else if (NodeId::numeric(UA_NS0ID_INT32) == services.getDataType(t_node))
                    {
                        UA_Int32 value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<int32_t>(value), TypesMap::Type::Int32);
                    }
                    else if (NodeId::numeric(UA_NS0ID_INT64) == services.getDataType(t_node))
                    {
                        UA_Int64 value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<int64_t>(value), TypesMap::Type::Int64);
                    }
                    else if (NodeId::numeric(UA_NS0ID_BYTE) == services.getDataType(t_node))
                    {
                        UA_Byte value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<uint8_t>(value), TypesMap::Type::UInt8);
                    }
                    else if (NodeId::numeric(UA_NS0ID_UINT16) == services.getDataType(t_node))
                    {
                        UA_UInt16 value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<uint16_t>(value), TypesMap::Type::UInt16);
                    }
                    else if (NodeId::numeric(UA_NS0ID_UINT32) == services.getDataType(t_node))
                    {
                        UA_UInt32 value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<uint32_t>(value), TypesMap::Type::UInt32);
                    }
                    else if (NodeId::numeric(UA_NS0ID_UINT64) == services.getDataType(t_node))
                    {
                        UA_UInt64 value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<uint64_t>(value), TypesMap::Type::UInt64);
                    }
                    else if (NodeId::numeric(UA_NS0ID_FLOAT) == services.getDataType(t_node))
                    {
                        UA_Float value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<float>(value), TypesMap::Type::Float);
                    }
                    else if (NodeId::numeric(UA_NS0ID_DOUBLE) == services.getDataType(t_node))
                    {
                        UA_Double value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(TypesTransformer::numeral_cast<double>(value), TypesMap::Type::Double);
                    }
                    else if (NodeId::numeric(UA_NS0ID_STRING) == services.getDataType(t_node))
                    {
                        std::string value;

                        auto status = services.readValue(t_node, value);

                        if (status != UA_STATUSCODE_GOOD)
                        {
                            return status;
                        }

                        t_object = TypesTransformer::packValuePair(value, TypesMap::Type::String);
                    }
                    return UA_STATUSCODE_GOOD;
                }
            };
        }
    }
}

#endif