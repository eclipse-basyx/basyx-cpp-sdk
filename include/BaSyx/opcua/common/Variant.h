/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VARIANT_H
#define VARIANT_H

#include <vector>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/client/open62541Client.h>
#include <BaSyx/opcua/common/NodeId.h>

namespace basyx
{
    namespace opcua
    {
        template<typename TYPE>
        class Variant
        {
        public:

            Variant() = default;

            Variant(TYPE t_value);

            Variant(std::vector<TYPE> t_value);

            virtual ~Variant()
            {
                UA_Variant_delete(m_variant);

                m_variant = nullptr;
            }

            size_t getArrayLength()
            {
                if (m_variant != nullptr)
                {
                    if (!((UA_Variant_isScalar(m_variant))))
                    {
                        return m_variant->arrayLength;
                    }
                }
                return -1;
            }

            inline UA_Variant* get_UAVariant()
            {
                return m_variant;
            }

            inline bool isScalar()
            {
                if (m_variant != nullptr)
                {
                    return UA_Variant_isScalar(m_variant);
                }
                return false;
            }

            inline bool isVector()
            {
                return !isScalar();
            }

            static TYPE scalar(UA_Variant& t_variant);

            static TYPE scalar(Variant& t_variant);

            static std::vector<TYPE> array(UA_Variant& t_variant);

            static std::vector<TYPE> array(Variant& t_variant);

            NodeId getType()
            {
                return m_variant->type->typeId;
            }

            static NodeId type(UA_Variant& t_variant);

        private:
            UA_Variant* m_variant = nullptr;
        };

        template<typename TYPE>
        std::vector<TYPE> basyx::opcua::Variant<TYPE>::array(UA_Variant& t_variant)
        {
            std::vector<TYPE> ret;

            size_t size = t_variant.arrayLength;
            auto data = (TYPE*)t_variant.data;

            ret.assign(size, TYPE());

            for (size_t i(0); i < size; i++)
            {
                ret.at(i) = *data;

                data++;
            }
            return ret;
        }

        template<>
        std::vector<std::string> basyx::opcua::Variant<std::string>::array(UA_Variant& t_variant)
        {
            std::vector<std::string> ret;

            size_t size = t_variant.arrayLength;
            auto data = (UA_String*)t_variant.data;

            ret.assign(size, std::string());

            for (size_t i(0); i < size; i++)
            {
                ret.at(i) = shared::string::UAStringToStdString(*data);

                data++;
            }
            return ret;
        }

        template<typename TYPE>
        std::vector<TYPE> basyx::opcua::Variant<TYPE>::array(Variant& t_variant)
        {
            return basyx::opcua::Variant<TYPE>::array(*t_variant.get_UAVariant());
        }

        template<typename TYPE>
        inline NodeId basyx::opcua::Variant<TYPE>::type(UA_Variant & t_variant)
        {
            return std::move(NodeId(t_variant.type->typeId));
        }

        template<typename TYPE>
        TYPE basyx::opcua::Variant<TYPE>::scalar(UA_Variant& t_variant)
        {
            if (!UA_Variant_isEmpty(&t_variant))
            {
                return *(static_cast<TYPE*>(t_variant.data));
            }
            return TYPE();
        }

        template<>
        std::string basyx::opcua::Variant<std::string>::scalar(UA_Variant& t_variant)
        {
            return basyx::opcua::shared::string::UAStringToStdString(
                Variant<UA_String>::scalar(t_variant)
            );
        }

        template<typename TYPE>
        TYPE basyx::opcua::Variant<TYPE>::scalar(Variant& t_variant)
        {
            return basyx::opcua::Variant<TYPE>::scalar(*t_variant.get_UAVariant());
        }

        template<typename TYPE>
        inline basyx::opcua::Variant<TYPE>::Variant(TYPE t_value)
        {
            m_variant = UA_Variant_new();

            auto status = UA_Variant_setScalarCopy(
                m_variant, &t_value, &UA_TYPES[shared::UATypeId(t_value)]
            );

            if (shared::diag::isStatusBad(status))
            {
                UA_Variant_delete(m_variant);

                m_variant = nullptr;
            }
        }

        template<>
        inline basyx::opcua::Variant<std::string>::Variant(std::string t_value)
        {
            m_variant = UA_Variant_new();

            UA_String* str = UA_String_new();

            *str = UA_STRING_ALLOC(t_value.c_str());

            auto status = UA_Variant_setScalarCopy(
                m_variant, str, &UA_TYPES[shared::UATypeId(t_value)]
            );

            if (shared::diag::isStatusBad(status))
            {
                UA_Variant_delete(m_variant);

                m_variant = nullptr;
            }

            UA_String_delete(str);
        }

        template<typename TYPE>
        inline basyx::opcua::Variant<TYPE>::Variant(std::vector<TYPE> t_value)
        {
            TYPE* valueRaw = new TYPE[t_value.size()];

            int i(0);
            for (const TYPE&v : t_value)
            {
                valueRaw[i] = v;
                i++;
            }

            m_variant = UA_Variant_new();

            UA_StatusCode status = UA_Variant_setArrayCopy(
                m_variant, valueRaw, t_value.size(), &UA_TYPES[shared::UATypeId(*valueRaw)]
            );

            if (status != UA_STATUSCODE_GOOD)
            {
                UA_Variant_delete(m_variant);

                m_variant = nullptr;
            }

            delete[] valueRaw;
        }

        template<>
        inline basyx::opcua::Variant<std::string>::Variant(std::vector<std::string> t_value)
        {
            UA_String *valueRaw = new UA_String[t_value.size()];

            int i(0);
            for (const std::string&v : t_value)
            {
                valueRaw[i] = UA_STRING(const_cast<char*>(v.c_str()));
                i++;
            }

            m_variant = UA_Variant_new();

            UA_StatusCode status = UA_Variant_setArrayCopy(
                m_variant, valueRaw, t_value.size(), &UA_TYPES[shared::UATypeId(*valueRaw)]
            );

            if (shared::diag::isStatusBad(status))
            {
                UA_Variant_delete(m_variant);

                m_variant = nullptr;
            }

            delete[] valueRaw;
        }
    }
}
#endif