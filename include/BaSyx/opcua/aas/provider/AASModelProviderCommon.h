/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_MODELPROVIDER_COMMON_H
#define AAS_MODELPROVIDER_COMMON_H

#include <tuple>
#include <string>
#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>
#include <BaSyx/vab/core/util/VABPath.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodelAliases.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            enum class RequestType
            {
                CREATE,
                GET,
                DELETE_,
                UPDATE,
                INVOKE
            };

            using identifiers = std::tuple<std::string, std::string, std::string>;

            static constexpr const size_t AAS_ID{ 0 };
            static constexpr const size_t SM_ID{ 1 };
            static constexpr const size_t SM_ELE_ID{ 2 };

            struct Element
            {
                static constexpr char aas[] = "aas";
                static constexpr char shells[] = "shells";

                static constexpr char assetAdministrationShell[] = "assetAdministrationShell";
                static constexpr char assetAdministrationShellSubmodels[] = "assetAdministrationShell/submodels";
                static constexpr char AssetAdministrationShell[] = "AssetAdministrationShell";
                static constexpr char administration[] = "administration";
                static constexpr char version[] = "version";
                static constexpr char revision[] = "revision";
                static constexpr char submodels[] = "submodels";
                static constexpr char submodel_[] = "submodel";
                static constexpr char submodel[] = "Submodel";
                static constexpr char submodelElements[] = "submodelElements";
                static constexpr char operations[] = "operations";
                static constexpr char operation[] = "Operation";
                static constexpr char invoke[] = "invoke";
                static constexpr char value[] = "value";
                static constexpr char values[] = "values";
                static constexpr char valueType[] = "valueType";
                static constexpr char valueId[] = "valueId";
                static constexpr char keys[] = "keys";
                static constexpr char valueValueType[] = "value/valueType";
                static constexpr char properties[] = "properties";
                static constexpr char property[] = "Property";
                static constexpr char idShort[] = "idShort";
                static constexpr char identifier[] = "identification";
                static constexpr char kind[] = "kind";
                static constexpr char tInt[] = "int";
                static constexpr char tDouble[] = "double";
                static constexpr char tBoolean[] = "boolean";
                static constexpr char tString[] = "string";
                static constexpr char modelType[] = "modelType";
                static constexpr char name[] = "name";
                static constexpr char id[] = "id";
                static constexpr char idType[] = "idType";
                static constexpr char description[] = "description";
                static constexpr char language[] = "language;";
                static constexpr char text[] = "text";
                static constexpr char category[] = "category";
            };

            inline std::string KindtoString(const Kind& t_kind) {
                return basyx::aas::ModelingKind_::to_string(t_kind);
            }

            inline Kind KindfromString(const std::string& t_kindStr) {
                return basyx::aas::ModelingKind_::from_string(t_kindStr);
            }

            inline std::string KeyElemementToString(KeyElements t_keyElement) {
                return basyx::aas::KeyElements_::to_string(t_keyElement);
            }

            inline KeyElements KeyElemementFromString(const std::string& t_keyElementStr) {
                return basyx::aas::KeyElements_::from_string(t_keyElementStr);
            }

            inline std::string KeyTypetoString(KeyType t_keyType) {
                return basyx::aas::KeyType_::to_string(t_keyType);
            }

            inline KeyType KeyTypeFromString(const std::string& t_keyTypeStr) {
                return basyx::aas::KeyType_::from_string(t_keyTypeStr);
            }

            inline std::string IdTypetoString(const Identifier& _identifier) {
                if (_identifier.getIdType() == IdentifierType::IRDI) {
                    return "IRDI";
                }
                else if (_identifier.getIdType() == IdentifierType::URI) {
                    return "URI";
                }
                else {
                    return "Custom";
                }
            }

            inline std::string IdTypetoString(IdentifierType _identifierType) {
                if (_identifierType == IdentifierType::IRDI) {
                    return "IRDI";
                }
                else if (_identifierType == IdentifierType::URI) {
                    return "URI";
                }
                else {
                    return "Custom";
                }
            }

            inline IdentifierType IdTypefromString(const std::string& t_idTypeStr) {
                return basyx::aas::IdentifierType_::from_string(t_idTypeStr);
            }

            inline std::string KeyToString(const Key& key) {

                return(
                    key.getType(), key.isLocal(), key.getIdType(), key.getValue()
                    );
            }

            inline std::string KeyToString(KeyElements keyElement, bool isLocal, KeyType _idType, const std::string& _value) {

                auto keyIdType = KeyTypetoString(_idType);
                auto keyElementType = KeyElemementToString(keyElement);
                auto keyType = isLocal ? "local" : "no-local";

                return "(" + keyElementType + ")" +
                    "(" + keyType + ")" +
                    "[" + keyIdType + "]" +
                    _value;

            }

            inline std::string KeyFromMap(basyx::object::object_map_t t_key)
            {
                KeyType keyIdType = KeyType::Unknown;
                std::string value;
                KeyElements keyElement = KeyElements::Unknown;
                bool isLocal(false);

                for (auto& e : t_key)
                {
                    if (e.first == "local")
                        isLocal = true;
                    if (e.first == "idType")
                        keyIdType = KeyTypeFromString(e.second.Get<std::string>());
                    if (e.first == "type")
                        keyElement = KeyElemementFromString(e.second.Get<std::string>());
                    if (e.first == "value")
                        value = e.second.Get<std::string>();
                }
                return KeyToString(keyElement, isLocal, keyIdType, value);
            }

            inline Key KeyFromString(const std::string& keyStr)
            {
                using namespace opcua::shared::string;

                std::string keyVal;
                std::string keyType;
                std::string keyElement;
                bool isLocalStr;

                auto str_1 = split(keyStr, ']');
                keyVal = str_1.at(1);
                auto str_2 = split(str_1.at(0), '[');
                keyType = str_2.at(1);
                auto str_3 = split(str_2.at(0), ')');
                keyElement = str_3.at(0).substr(1, str_3.at(0).length() - 1);
                isLocalStr = (str_3.at(1).substr(1, str_3.at(1).length() - 1) == "local");

                Key ret(KeyElemementFromString(keyElement), isLocalStr, KeyTypeFromString(keyType), keyVal);
                return ret;

            }
        }
    }
}

#endif 