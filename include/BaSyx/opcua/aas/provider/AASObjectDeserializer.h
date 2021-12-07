/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_OBJECT_DESERIALIZER_H
#define AAS_OBJECT_DESERIALIZER_H

#include <BaSyx/opcua/aas/node/MetamodelTypes.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/opcua/aas/provider/AASModelProviderCommon.h>
#include <BaSyx/opcua/aas/api_v2/ApiMetamodelUtilities.h>
#include <BaSyx/aas/api_v2/submodelelement/property/XSDAnySimpleType.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            // Helper fuctions to deserialize basyx::object to corresponding 
            // AAS metamodel types. PS : these functions will be removed in the
            // future once the contructors for basyx::object for corresponding types 
            // are available
            struct AASObjectDeserializer
            {
                // Deserialize object type to AssetAdministrationShell type
                static std::unique_ptr<AssetAdministrationShell_t> makeAssetAdministrationShell(basyx::object t_object)
                {
                    std::string& idShort = t_object.getProperty(Element::idShort).Get<std::string&>();
                    //// TODO : Fix asset
                    auto aas = util::make_unique<AssetAdministrationShell_t>(idShort,
                        makeIdentifier(t_object),
                        *makeAsset(basyx::object::make_null()).get());
                
                    auto description = t_object.getProperty(Element::description);
                    if (!description.empty())
                    {
                        for (auto& langs : description.Get<basyx::object::object_list_t>())
                        {
                            auto langMap = langs.Get<basyx::object::object_map_t>();
                            auto& text = langMap[Element::text].Get<std::string&>();
                            auto& lang = langMap[Element::language].Get<std::string&>();
                            aas->getDescription().add(lang, text);
                        }
                    }
                    return aas;
                }

                // Deserialize object to AssetType (TODO : Incomplete)
                static std::unique_ptr<Asset_t> makeAsset(basyx::object t_object)
                {
                    return util::make_unique<Asset_t>(std::string(), Identifier::Custom(std::string()));
                }

                // Deserialize object to Submodel type
                static std::unique_ptr<Submodel_t> makeSubmodel(basyx::object t_object)
                {
                    std::string& idShort = t_object.getProperty(Element::idShort).Get<std::string&>();
                    // TODO : Fix asset
                    auto sm = util::make_unique<Submodel_t>(idShort, makeIdentifier(t_object));
                    auto description = t_object.getProperty(Element::description);
                    if (!description.empty())
                    {
                        for (auto& langs : description.Get<basyx::object::object_list_t>())
                        {
                            auto langMap = langs.Get<basyx::object::object_map_t>();
                            auto& text = langMap[Element::text].Get<std::string&>();
                            auto& lang = langMap[Element::language].Get<std::string&>();
                            sm->getDescription().add(lang, text);
                        }
                    }
                    //SubmodelElements
                    auto sme = t_object.getProperty(Element::submodelElements);
                    if (!sme.empty())
                    {
                        for (auto& subModelElement : sme.Get<basyx::object::object_map_t>())
                        {
                            auto type = subModelElement.second.getProperty(Element::modelType);
                            const std::string& name = type.getProperty(Element::name).Get<std::string&>();
                            if (name == Element::property)
                            {
                                addPropertiesToSubmodel(*sm.get(), subModelElement.second);
                            }
                        }
                    }
                    return sm;
                }

                // Deserialize object to Property<U> type
                template<typename TYPE>
                static std::unique_ptr<Property_t<TYPE>> makeProperty(basyx::object t_object)
                {
                    using namespace basyx::xsd_types;
                    std::string idShort, kind, valueType, category;
             
                    auto idShortObj   = t_object.getProperty(Element::idShort);
                    auto kindObj      = t_object.getProperty(Element::kind);
                    auto valueObj     = t_object.getProperty(Element::value);
                    auto valueTypeObj = t_object.getProperty(Element::valueType);
                    auto categoryObj  = t_object.getProperty(Element::category);

                    idShort   = !idShortObj.IsError() ? idShortObj.Get<std::string&>() : std::string();
                    //valueType = !valueTypeObj.IsError() ? valueTypeObj.Get<std::string&>() : std::string();
                    //kind      = !kindObj.IsError() ? kindObj.Get<std::string&>() : std::string();
                    category  = !categoryObj.IsError() ? categoryObj.Get<std::string&>() : std::string();

                    auto keys = makeKeys(t_object);

                    auto prop = util::make_unique<Property_t<TYPE>>(idShort);
                    TYPE value = xsd_type<TYPE>::fromXSDRepresentation(valueObj);
                    prop->setValue(value);
                    prop->setCategory(category);
                    prop->setValueId(Reference(keys));

                    auto description = t_object.getProperty(Element::description);
                    if (!description.empty())
                    {
                        for (auto& langs : description.Get<basyx::object::object_list_t>())
                        {
                            auto langMap = langs.Get<basyx::object::object_map_t>();
                            auto& text = langMap[Element::text].Get<std::string&>();
                            auto& lang = langMap[Element::language].Get<std::string&>();
                            prop->getDescription().add(lang, text);
                        }
                    }
                    
                    return prop;
                }

                // Deserialize object to Identifier type
                static Identifier_t makeIdentifier(basyx::object t_object)
                {
                    auto identification = t_object.getProperty(Element::identifier);

                    auto& typeStr{ identification.getProperty(Element::idType).Get<std::string&>() };

                    auto& idStr{ identification.getProperty(Element::id).Get<std::string&>() };

                    auto type{ basyx::aas::IdentifierType_::from_string(typeStr) };

                    return Identifier_t(type, idStr);
                }
               // Adds Properties to the Submodel
               static void addPropertiesToSubmodel(Submodel_t & t_sm, basyx::object t_object)
               {
                   using namespace metamodel;
                   std::string  valueType, idShort;
                   basyx::log logger("AASObjectDeserializer");
                   auto idShortObj = t_object.getProperty(Element::idShort);
                   idShort = !idShortObj.IsError() ? idShortObj.Get<std::string&>() : std::string();
               
                   auto valueTypeObj = t_object.getProperty(Element::valueType);

                   valueType = !valueTypeObj.IsError() ? valueTypeObj.Get<std::string&>() : std::string();

                   // Read the PropertyType based on the meta information in ValueType
                   if (valueType == AASPropertyType::TypeName::bool_)
                       return t_sm.submodelElements().addElement(std::move(makeProperty<bool>(t_object)));
                   else if (valueType == AASPropertyType::TypeName::int8)
                   {
                       auto prop = makeProperty<int32_t>(t_object);
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::uint8)
                   {
                       auto prop = makeProperty<int32_t>(convertObjectValue<uint8_t, uint64_t>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::int16)
                   {
                       auto prop = makeProperty<int32_t>(convertObjectValue<int16_t, uint64_t>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::uint16)
                   {
                       auto prop = makeProperty<int32_t>(convertObjectValue<uint16_t, uint64_t>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::int32)
                       return t_sm.submodelElements().addElement(std::move(makeProperty<int32_t>(t_object)));
                   else if (valueType == AASPropertyType::TypeName::uint32)
                   {
                       auto prop = makeProperty<int32_t>(convertObjectValue<uint32_t, uint64_t>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::int64)
                   {
                       auto prop = makeProperty<int32_t>(convertObjectValue<int64_t, uint64_t>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::uint64)
                   {
                       auto prop = makeProperty<int32_t>(convertObjectValue<uint64_t, uint64_t>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::int8);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::float_)
                   {
                       auto prop = makeProperty<float>(convertObjectValue<float, float>(t_object));
                       prop->setValueType(AASPropertyType::TypeName::float_);
                       return t_sm.submodelElements().addElement(std::move(prop));
                   }
                   else if (valueType == AASPropertyType::TypeName::double_)
                       return t_sm.submodelElements().addElement(std::move(makeProperty<double>(t_object)));
                   else if (valueType == AASPropertyType::TypeName::string_)
                       return t_sm.submodelElements().addElement(std::move(makeProperty<std::string>(t_object)));
                   // Complex types are encoded as string in OPC UA
                   else {
                       auto propertyStr = makeProperty<std::string>(t_object);
                       std::string valueStr = propertyStr->getValue();
                       std::string categoryStr = propertyStr->getCategory() ? *propertyStr->getCategory() : std::string();
                       auto description = propertyStr->getDescription();
                       
                       if (valueType == AASPropertyType::TypeName::anyUri)
                           //return t_subModel.submodelElements().addElement(std::move(makeProperty>(t_object)));
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<AnyURI_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::date)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<Date_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::time)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<Time_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::dayTimeDuration)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<DayTimeDuration_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::yearMonthDuration)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<YearMonthDuration_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::dateTime)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<DateTime_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::gDay)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<GDay_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::gMonth)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<GMonth_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::gMonthDay)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<GMonthDay_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::gYear)
                           return t_sm.submodelElements().addElement(
                               std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<GYear_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else if (valueType == AASPropertyType::TypeName::gYearMonth)
                          return t_sm.submodelElements().addElement(
                              std::move(ApiMetamodelUtilities::makeXsdPropertyWithValue<GYearMonth_t>(valueStr, propertyStr->getIdShort(), categoryStr, description)));
                       else;      
                   }
               }

               private:
               // Dirty workaround to forcefully cast all integrals to int32 and 
               // floating to double. This may result in data loss for integral types
               // uint32, int64 and uint64 types. TODO :In the future all the types will be
               // stored as int64 types and therefore this fucntion will be removed.
               template<typename TYPE_SRC, typename TYPE_DEST>
               static object convertObjectValue(basyx::object t_object)
               {
                   auto valueObj = t_object.getProperty(Element::value);
                   TYPE_SRC valSrc = valueObj.Get<TYPE_SRC&>();
                   TYPE_DEST valDest = static_cast<TYPE_DEST>(valSrc);
                   t_object.insertKey("value", valDest);
                   return t_object;
               }
               // Keys from Object
               static std::vector<Key_t> makeKeys(basyx::object t_object)
               {
                   using namespace basyx::opcua::aas;
               
                   std::vector<Key_t> keys;
               
                   auto valueId{ t_object.getProperty(Element::valueId) };
                   if (valueId.getError() != basyx::object::error::PropertyNotFound)
                   {
                       for (auto& key_obj : valueId.getProperty(Element::keys).Get<basyx::object::object_list_t>())
                       {
                           auto key = key_obj.Get<basyx::object::object_map_t>();
                           auto keyStr = makeKey(KeyFromMap(key));
                           keys.push_back(keyStr);
                       }
                   }
                   return keys;
               }

               // Key from string
               static Key_t makeKey(const std::string& keyStr)
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
               
                   Key ret(basyx::aas::KeyElements_::from_string(keyElement),
                       isLocalStr, basyx::aas::KeyType_::from_string(keyType), keyVal);
                   return ret;
               }

               // Deserializes object to LangStringSet
               LangStringSet_t makeLangStringSet(basyx::object t_object)
               {
                   LangStringSet_t ret;

                   if (!t_object.empty())
                   {
                       for (auto& langs : t_object.Get<basyx::object::object_list_t>())
                       {
                           auto langMap = langs.Get<basyx::object::object_map_t>();
                           auto& text = langMap[Element::text].Get<std::string&>();
                           auto& lang = langMap[Element::language].Get<std::string&>();
                           ret.add(lang, text);
                       }
                   }
                   return ret;
               }
            };
        }
    }
}
#endif