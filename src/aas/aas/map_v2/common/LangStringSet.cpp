/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <algorithm>

#include <BaSyx/aas/map_v2/common/LangStringSet.h>

namespace basyx {
namespace aas {
namespace map {

constexpr char LangStringSet::Path::Text[];
constexpr char LangStringSet::Path::Language[];

std::string empty_string;

LangStringSet::LangStringSet()
    : vab::ElementMap(basyx::object::make_object_list())
{};

LangStringSet::LangStringSet(const ILangStringSet & other)
    : vab::ElementMap(basyx::object::make_object_list())
{
  auto langCodes = other.getLanguageCodes();
  for (auto langCode : langCodes)
    this->add(langCode, other.get(langCode));
}

map::LangStringSet LangStringSet::from_object(object obj)
{
  map::LangStringSet lang_string_set;

  if ( obj.empty() or (obj.GetObjectType() != basyx::type::objectType::List) )
    return lang_string_set;

  auto lang_objects = obj.Get<object::object_list_t>();
  for (auto lang_object : lang_objects)
  {
    auto language = lang_object.getProperty(Path::Language).GetStringContent();
    auto content = lang_object.getProperty(Path::Text).GetStringContent();
    lang_string_set.add(language, content);
  }

  return lang_string_set;
}

LangStringSet::langCodeSet_t LangStringSet::getLanguageCodes() const
{
  auto &langStrings = this->map.Get<basyx::object::object_list_t &>();
  LangStringSet::langCodeSet_t langCodes;
  for (auto & langCode : langStrings)
    langCodes.emplace(langCode.getProperty(Path::Language).GetStringContent());
  return langCodes;
}

const std::string &LangStringSet::get(const std::string &languageCode) const
{
  auto &langStrings = this->map.Get<basyx::object::object_list_t &>();
  auto langString = std::find_if(
      langStrings.begin(), langStrings.end(),
      [&languageCode](basyx::object &obj) {
        const auto &langCode = obj.getProperty(Path::Language).Get<std::string &>();
        return langCode == languageCode;
      });

  if (langString != langStrings.end())
    return langString->getProperty(Path::Text).Get<std::string &>();

  return empty_string;
}

void LangStringSet::add(const std::string &languageCode, const std::string &langString)
{
  auto langStringMap = basyx::object::make_map();
  langStringMap.insertKey(Path::Text, langString);
  langStringMap.insertKey(Path::Language, languageCode);
  this->map.insert(langStringMap);
};

bool LangStringSet::empty() const noexcept
{
  return this->map.empty();
};
}

namespace api {
bool operator==(const basyx::aas::api::ILangStringSet &left, const basyx::aas::api::ILangStringSet &right)
{
  auto langCodes = left.getLanguageCodes();
  if (langCodes.size() != right.getLanguageCodes().size())
    return false;
  for (auto langCode : langCodes)
  {
    auto leftString = left.get(langCode);
    if (leftString.compare(right.get(langCode)) != 0)
      return false;
  }
  return true;
}

}
}
}