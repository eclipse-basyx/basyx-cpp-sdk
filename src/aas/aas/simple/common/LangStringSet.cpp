/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/aas/simple/common/LangStringSet.h>

#include <BaSyx/shared/types.h>

namespace basyx {
namespace aas {
namespace simple {

const std::string empty_string{};

LangStringSet::LangStringSet()
{
};

LangStringSet::LangStringSet(const std::string & languageCode, const std::string & langString)
{
	this->langStrings.emplace(languageCode, langString);
};

LangStringSet::langCodeSet_t LangStringSet::getLanguageCodes() const
{
  LangStringSet::langCodeSet_t langCodes;
  for (auto & langCode : this->langStrings)
    langCodes.insert(langCode.first);
  return langCodes;
};


LangStringSet::LangStringSet(std::initializer_list<LangStringSet::langStringMap_t::value_type> il)
{
	for (const auto & entry : il)
		this->add(entry.first, entry.second);
}

LangStringSet::LangStringSet(const api::ILangStringSet &other)
{
  for( auto & lang_code : other.getLanguageCodes())
    this->add(lang_code, other.get(lang_code));
}

const std::string & LangStringSet::get(const std::string & languageCode) const
{
	if (this->langStrings.find(languageCode) != langStrings.end()) {
		return langStrings.at(languageCode);
	}

	return empty_string;
};


void LangStringSet::add(const std::string & languageCode, const std::string & langString)
{
	this->langStrings.emplace(languageCode, langString);
};

bool LangStringSet::empty() const noexcept
{
	return this->langStrings.empty();
}

}
}
}
