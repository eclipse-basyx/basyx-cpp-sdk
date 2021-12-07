/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef TYPES_MAP_H
#define TYPES_MAP_H

#include <string>
#include <unordered_map>
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
	namespace opcua
	{

		class TypesMap
		{
		public:
			struct AttrNames
			{
				static constexpr const char BasyxMap[] = "BasyxObjectMap";
				static constexpr const char BasyxObjectCollection[] = "BasyxObjectCollection";
				static constexpr const char BasyxIntCollection[] = "BasyxIntCollection";
				static constexpr const char BasyxBooleanCollection[] = "BasyxBooleanCollection";
				static constexpr const char BasyxDoubleCollection[] = "BasyxDoubleCollection";
				static constexpr const char BasyxStringCollection[] = "BasyxStringCollection";
			};

			struct TypeKeys
			{
				static constexpr const char Value[] = "Value";
				static constexpr const char ValueType[] = "ValueType";
			};

			enum class Type : unsigned char
			{
				Boolean,
				Float,
				Double,
				UInt64,
				UInt32,
				UInt16,
				UInt8,
				Int64,
				Int32,
				Int16,
				Int8,
				String,
				Unknown
			};

			template<typename TYPE>
			struct VABExtendedTypeInclusion
			{
				static constexpr bool condition =
					(
						std::is_same<TYPE, int8_t>::value ||
						std::is_same<TYPE, uint8_t>::value ||
						std::is_same<TYPE, int16_t>::value ||
						std::is_same<TYPE, uint16_t>::value ||
						std::is_same<TYPE, int32_t>::value ||
						std::is_same<TYPE, uint32_t>::value ||
						std::is_same<TYPE, int64_t>::value ||
						std::is_same<TYPE, uint64_t>::value ||
						std::is_same<TYPE, float>::value ||
						std::is_same<TYPE, double>::value ||
						std::is_same<TYPE, std::string>::value
						);
			};

			template<class TYPE>
			static constexpr NodeId BasyxPrimitiveType(TYPE t_type) {
				return (typeid(t_type) == typeid(UA_Boolean)) ?
					NodeId::numeric(UA_NS0ID_BOOLEAN) : (
					(typeid(t_type) == typeid(UA_Int32) ?
						NodeId::numeric(UA_NS0ID_INT32) : (
						(typeid(t_type) == typeid(UA_Float) ?
							NodeId::numeric(UA_NS0ID_DOUBLE) : (
							(typeid(t_type) == typeid(UA_Double) ?
								NodeId::numeric(UA_NS0ID_DOUBLE) : (
								(typeid(t_type) == typeid(UA_String) ?
									NodeId::numeric(UA_NS0ID_STRING) : (
									(typeid(t_type) == typeid(std::string) ?
										NodeId::numeric(UA_NS0ID_STRING) : NodeId::nullNode()
										))))))))));
			}

			static std::string toString(TypesMap::Type t_type);

			static TypesMap::Type fromString(const std::string& t_type);

			static UA_UInt32 getOPCUATypeId(TypesMap::Type t_type);

			static TypesMap::Type getType(UA_UInt32 t_opcuaTypeId);

			struct TypeMetaMap
			{
				static std::map<UA_UInt32, TypesMap::Type> map()
				{
					const std::map<UA_UInt32, TypesMap::Type> ret
					{
						{ UA_NS0ID_BOOLEAN, TypesMap::Type::Boolean },
						{ UA_NS0ID_SBYTE,   TypesMap::Type::Int8 },
						{ UA_NS0ID_BYTE,    TypesMap::Type::UInt8 },
						{ UA_NS0ID_INT16,   TypesMap::Type::Int16 },
						{ UA_NS0ID_UINT16,  TypesMap::Type::UInt16 },
						{ UA_NS0ID_INT32,   TypesMap::Type::Int32 },
						{ UA_NS0ID_UINT32,  TypesMap::Type::UInt32 },
						{ UA_NS0ID_INT64,   TypesMap::Type::Int64 },
						{ UA_NS0ID_UINT64,  TypesMap::Type::UInt64 },
						{ UA_NS0ID_FLOAT,   TypesMap::Type::Float },
						{ UA_NS0ID_DOUBLE,  TypesMap::Type::Double },
						{ UA_NS0ID_STRING,  TypesMap::Type::String },
						{ NULL,             TypesMap::Type::Unknown }
					};
					return ret;
				}
			};

			struct TypesStringMap
			{
				static std::map<TypesMap::Type, std::string> map()
				{
					const std::map<TypesMap::Type, std::string> ret
					{
						{TypesMap::Type::Boolean, "Boolean"},
						{TypesMap::Type::Int8,    "Int8"},
						{TypesMap::Type::UInt8,   "UInt8"},
						{TypesMap::Type::Int16,   "Int16"},
						{TypesMap::Type::UInt16,  "UInt16"},
						{TypesMap::Type::Int32,   "Int32"},
						{TypesMap::Type::UInt32,  "UInt32"},
						{TypesMap::Type::Int64,   "Int64"},
						{TypesMap::Type::UInt64,  "UInt64"},
						{TypesMap::Type::Float,   "Float"},
						{TypesMap::Type::Double,  "Double"},
						{TypesMap::Type::String,  "String"},
						{TypesMap::Type::Unknown, "Unknown"}
					};
					return ret;
				}
			};

			struct NodeIds
			{
				static constexpr const int BasyxMap = 1000;
				static constexpr const int BasyxObjectCollection = 1001;
				static constexpr const int BasyxIntCollection = 1002;
				static constexpr const int BasyxBooleanCollection = 1003;
				static constexpr const int BasyxDoubleCollection = 1004;
				static constexpr const int BasyxStringCollection = 1005;
			};

			/* Maps the OPCUA Types to Basyx types */
			const std::unordered_map<UA_UInt32, std::string> OPCUA2BaSysTypeMap;


			/* Maps the Basyx Types to OPCUA  types */

			static NodeId BasyxMap(int32_t t_ns);

			template<typename TYPE>
			static NodeId BasyxCollection(int32_t t_ns);

			static NodeId BasyxIntCollection(int32_t t_ns);

			static NodeId BasyxDoubleCollection(int32_t t_ns);

			static NodeId BasyxBooleanCollection(int32_t t_ns);

			static NodeId BasyxStringCollection(int32_t t_ns);

			static NodeId BasyxObjectCollection(int32_t t_ns);

			static NodeId BasyxParentChildReference();

			static NodeId BasyxInt();

			static NodeId BasyxDouble();

			static NodeId BasyxBool();

			static NodeId BasyxString();

			static NodeId PropertyType();

			static NodeId NonVABUInt8();

			static NodeId NonVABInt8();

			static NodeId NonVABUInt16();

			static NodeId NonVABInt16();

			static NodeId NonVABUInt32();

			static NodeId NonVABInt32();

			static NodeId NonVABUInt64();

			static NodeId NonVABInt64();

			static NodeId NonVABFloat();

			static NodeId NonVABDouble();

			static bool isBasyxTypeNode(const NodeId & t_node, int32_t t_ns);

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode define(int32_t t_ns, CONNECTOR_TYPE& t_connector);

		private:

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode defineBasyxMap(int32_t t_ns, CONNECTOR_TYPE& t_connector);

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode defineBasyxObjectCollection(int32_t t_ns, CONNECTOR_TYPE& t_connector);

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode defineBasyxIntCollection(int32_t t_ns, CONNECTOR_TYPE& t_connector);

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode defineBasyxBooleanCollection(int32_t t_ns, CONNECTOR_TYPE& t_connector);

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode defineBasyxDoubleCollection(int32_t t_ns, CONNECTOR_TYPE& t_connector);

			template<typename CONNECTOR_TYPE>
			static UA_StatusCode defineBasyxStringCollection(int32_t t_ns, CONNECTOR_TYPE& t_connector);
		};

		template<>
		NodeId TypesMap::BasyxCollection<bool>(int32_t t_ns);

		template<>
		NodeId TypesMap::BasyxCollection<int32_t>(int32_t t_ns);

		template<>
		NodeId TypesMap::BasyxCollection<double>(int32_t t_ns);

		template<>
		NodeId TypesMap::BasyxCollection<std::string>(int32_t t_ns);

		template<typename CONNECTOR_TYPE>
		inline UA_StatusCode TypesMap::define(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			NodeId parentNode(UA_NodeIdType::UA_NODEIDTYPE_NUMERIC, UA_NS0ID_BASEOBJECTTYPE);

			if (!(services.doesNodeExists(
				NodeId::string(t_ns, AttrNames::BasyxMap),
				parentNode
			)))
			{
				auto status = defineBasyxMap(t_ns, t_connector);

				if (status != UA_STATUSCODE_GOOD) {
					return status;
				}
			}

			if (!(services.doesNodeExists(
				NodeId::string(t_ns, AttrNames::BasyxObjectCollection),
				parentNode
			)))
			{
				auto status = defineBasyxObjectCollection(t_ns, t_connector);

				if (status != UA_STATUSCODE_GOOD) {
					return status;
				}
			}

			if (!(services.doesNodeExists(
				NodeId::string(t_ns, AttrNames::BasyxIntCollection),
				parentNode
			)))
			{
				auto status = defineBasyxIntCollection(t_ns, t_connector);

				if (status != UA_STATUSCODE_GOOD) {
					return status;
				}
			}

			if (!(services.doesNodeExists(
				NodeId::string(t_ns, AttrNames::BasyxBooleanCollection),
				parentNode
			)))
			{
				auto status = defineBasyxBooleanCollection(t_ns, t_connector);

				if (status != UA_STATUSCODE_GOOD) {
					return status;
				}
			}

			if (!(services.doesNodeExists(
				NodeId::string(t_ns, AttrNames::BasyxDoubleCollection),
				parentNode
			)))
			{
				auto status = defineBasyxDoubleCollection(t_ns, t_connector);

				if (status != UA_STATUSCODE_GOOD) {
					return status;
				}
			}

			if (!(services.doesNodeExists(
				NodeId::string(t_ns, AttrNames::BasyxStringCollection),
				parentNode
			)))
			{
				auto status = defineBasyxStringCollection(t_ns, t_connector);

				if (status != UA_STATUSCODE_GOOD) {
					return status;
				}
			}

			basyx::log::topic("basyx::opcua::TypesMap").trace("Basyx VAB types defined");

			return UA_STATUSCODE_GOOD;
		}

		template<typename CONNECTOR_TYPE>
		UA_StatusCode TypesMap::defineBasyxMap(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			return services.addObjectTypeNode(
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxMap),
				NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
				NodeId::numeric(UA_NS0ID_HASSUBTYPE),
				QualifiedName(t_ns, AttrNames::BasyxMap),
				ObjectTypeAttributes(AttrNames::BasyxMap, AttrNames::BasyxMap, "en-US")	
			);
		}

		template<typename CONNECTOR_TYPE>
		inline UA_StatusCode TypesMap::defineBasyxObjectCollection(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			return services.addObjectTypeNode(
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxObjectCollection),
				NodeId::numeric(UA_NS0ID_BASEOBJECTTYPE),
				NodeId::numeric(UA_NS0ID_HASSUBTYPE),
				QualifiedName(t_ns, AttrNames::BasyxObjectCollection),
				ObjectTypeAttributes(AttrNames::BasyxObjectCollection, AttrNames::BasyxObjectCollection, "en-US")
			);
		}

		template<typename CONNECTOR_TYPE>
		inline UA_StatusCode TypesMap::defineBasyxIntCollection(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			return services.addObjectTypeNode(
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxIntCollection),
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxObjectCollection),
				NodeId::numeric(UA_NS0ID_HASSUBTYPE),
				QualifiedName(t_ns, AttrNames::BasyxIntCollection),
				ObjectTypeAttributes(AttrNames::BasyxIntCollection, AttrNames::BasyxIntCollection, "en-US")
			);
		}

		template<typename CONNECTOR_TYPE>
		inline UA_StatusCode TypesMap::defineBasyxBooleanCollection(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			return services.addObjectTypeNode(
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxBooleanCollection),
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxObjectCollection),
				NodeId::numeric(UA_NS0ID_HASSUBTYPE),
				QualifiedName(t_ns, AttrNames::BasyxBooleanCollection),
				ObjectTypeAttributes(AttrNames::BasyxBooleanCollection, AttrNames::BasyxBooleanCollection, "en-US")
			);
		}

		template<typename CONNECTOR_TYPE>
		inline UA_StatusCode TypesMap::defineBasyxDoubleCollection(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			return services.addObjectTypeNode(
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxDoubleCollection),
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxObjectCollection),
				NodeId::numeric(UA_NS0ID_HASSUBTYPE),
				QualifiedName(t_ns, AttrNames::BasyxDoubleCollection),
				ObjectTypeAttributes(AttrNames::BasyxDoubleCollection, AttrNames::BasyxDoubleCollection, "en-US")
			);
		}

		template<typename CONNECTOR_TYPE>
		inline UA_StatusCode TypesMap::defineBasyxStringCollection(int32_t t_ns, CONNECTOR_TYPE & t_connector)
		{
			Services<CONNECTOR_TYPE> services(t_connector);

			return services.addObjectTypeNode(
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxStringCollection),
				NodeId::numeric(t_ns, TypesMap::NodeIds::BasyxObjectCollection),
				NodeId::numeric(UA_NS0ID_HASSUBTYPE),
				QualifiedName(t_ns, AttrNames::BasyxStringCollection),
				ObjectTypeAttributes(AttrNames::BasyxStringCollection, AttrNames::BasyxStringCollection, "en-US")
			);
		}
	}
}

#endif