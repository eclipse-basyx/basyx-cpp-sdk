/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/typesmap/TypesMap.h>

namespace basyx
{
	namespace opcua
	{
		constexpr char TypesMap::AttrNames::BasyxMap[];
		constexpr char TypesMap::AttrNames::BasyxObjectCollection[];
		constexpr char TypesMap::AttrNames::BasyxIntCollection[];
		constexpr char TypesMap::AttrNames::BasyxBooleanCollection[];
		constexpr char TypesMap::AttrNames::BasyxDoubleCollection[];
		constexpr char TypesMap::AttrNames::BasyxStringCollection[];
		constexpr char TypesMap::TypeKeys::Value[];
		constexpr char TypesMap::TypeKeys::ValueType[];

		NodeId TypesMap::BasyxInt()
		{
			return NodeId::numeric(UA_NS0ID_INT32);
		}

		NodeId TypesMap::BasyxDouble()
		{
			return NodeId::numeric(UA_NS0ID_DOUBLE);
		}

		NodeId TypesMap::BasyxBool()
		{
			return NodeId::numeric(UA_NS0ID_BOOLEAN);
		}

		NodeId TypesMap::BasyxString()
		{
			return NodeId::numeric(UA_NS0ID_STRING);
		}

		NodeId TypesMap::NonVABUInt8()
		{
			return NodeId::numeric(UA_NS0ID_BYTE);
		}

		NodeId TypesMap::NonVABInt8()
		{
			return NodeId::numeric(UA_NS0ID_SBYTE);
		}

		NodeId TypesMap::NonVABUInt16()
		{
			return NodeId::numeric(UA_NS0ID_UINT16);
		}

		NodeId TypesMap::NonVABInt16()
		{
			return NodeId::numeric(UA_NS0ID_INT16);
		}

		NodeId TypesMap::NonVABUInt32()
		{
			return NodeId::numeric(UA_NS0ID_UINT32);
		}

		NodeId TypesMap::NonVABInt32()
		{
			return NodeId::numeric(UA_NS0ID_INT32);
		}

		NodeId TypesMap::NonVABUInt64()
		{
			return NodeId::numeric(UA_NS0ID_UINT64);
		}

		NodeId TypesMap::NonVABInt64()
		{
			return NodeId::numeric(UA_NS0ID_INT64);
		}

		NodeId TypesMap::NonVABFloat()
		{
			return NodeId::numeric(UA_NS0ID_FLOAT);
		}

		NodeId TypesMap::NonVABDouble()
		{
			return NodeId::numeric(UA_NS0ID_DOUBLE);
		}

		NodeId TypesMap::PropertyType()
		{
			return NodeId::numeric(UA_NS0ID_PROPERTYTYPE);
		}

		bool TypesMap::isBasyxTypeNode(const NodeId & t_node, int32_t t_ns)
		{
			return ((BasyxMap(t_ns) == t_node)
				||
				(BasyxIntCollection(t_ns) == t_node)
				||
				(BasyxDoubleCollection(t_ns) == t_node)
				||
				(BasyxStringCollection(t_ns) == t_node)
				||
				(BasyxBooleanCollection(t_ns) == t_node)
				||
				(BasyxObjectCollection(t_ns) == t_node)
				||
				(BasyxInt() == t_node)
				||
				(BasyxBool() == t_node)
				||
				(BasyxDouble() == t_node)
				||
				(BasyxString() == t_node)
			);
		}


		TypesMap::Type TypesMap::getType(UA_UInt32 t_opcuaTypeId)
		{
			for (const auto& ele : TypesMap::TypeMetaMap::map())
			{
				if (ele.first == t_opcuaTypeId)
					return ele.second;
			}

			return TypesMap::Type::Unknown;
		}

		std::string TypesMap::toString(TypesMap::Type t_type)
		{
			
			for (const auto& ele : TypesMap::TypesStringMap::map())
			{
				if (ele.first == t_type)
					return ele.second;
			}

			return TypesMap::TypesStringMap::map().at(TypesMap::Type::Unknown);
		}

		TypesMap::Type TypesMap::fromString(const std::string & t_type)
		{
			for (const auto& ele : TypesMap::TypesStringMap::map())
			{
				if (ele.second == t_type)
					return ele.first;
			}

			return TypesMap::Type::Unknown;
		}

		UA_UInt32 TypesMap::getOPCUATypeId(TypesMap::Type t_type)
		{
			for (const auto& ele : TypesMap::TypeMetaMap::map())
			{
				if (ele.second == t_type)
					return ele.first;
			}
			return 0;
		}

		NodeId TypesMap::BasyxMap(int32_t t_ns)
		{
			return NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxMap);
		}

		NodeId TypesMap::BasyxIntCollection(int32_t t_ns)
		{
			return NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxIntCollection);
		}

		NodeId TypesMap::BasyxBooleanCollection(int32_t t_ns)
		{
			return NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxBooleanCollection);
		}

		NodeId TypesMap::BasyxDoubleCollection(int32_t t_ns)
		{
			return NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxDoubleCollection);
		}

		NodeId TypesMap::BasyxStringCollection(int32_t t_ns)
		{
			return NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxStringCollection);
		}

		NodeId TypesMap::BasyxObjectCollection(int32_t t_ns)
		{
			return NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxObjectCollection);
		}

		NodeId TypesMap::BasyxParentChildReference()
		{
			return NodeId::numeric(UA_NS0ID_HASCOMPONENT);
		}

		template<>
		NodeId TypesMap::BasyxCollection<bool>(int32_t t_ns)
		{
			return BasyxBooleanCollection(t_ns);
		}

		template<>
		NodeId TypesMap::BasyxCollection<int>(int32_t t_ns)
		{
			return BasyxIntCollection(t_ns);
		}

		template<>
		NodeId TypesMap::BasyxCollection<double>(int32_t t_ns)
		{
			return BasyxDoubleCollection(t_ns);
		}

		template<>
		NodeId TypesMap::BasyxCollection<std::string>(int32_t t_ns)
		{
			return BasyxStringCollection(t_ns);
		}
	}
}