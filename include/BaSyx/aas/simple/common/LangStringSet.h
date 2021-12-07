/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_COMMON_LANGSTRINGSET_H
#define BASYX_SUBMODEL_SIMPLE_COMMON_LANGSTRINGSET_H

#include <BaSyx/aas/api_v2/common/ILangStringSet.h>

#include <string>
#include <initializer_list>
#include <vector>
#include <unordered_map>

namespace basyx {
namespace aas {
namespace simple {

class LangStringSet : public api::ILangStringSet
{
public:
	using langStringMap_t = std::unordered_map<std::string, std::string>;
private:
	langStringMap_t langStrings;
public:
	LangStringSet();
	LangStringSet(const std::string & languageCode, const std::string & langString);
	LangStringSet(std::initializer_list<langStringMap_t::value_type>);
	LangStringSet(const api::ILangStringSet & other);
	virtual ~LangStringSet() = default;

	langCodeSet_t getLanguageCodes() const override;

	const std::string & get(const std::string & languageCode) const override;
	void add(const std::string & languageCode, const std::string & langString) override;
	bool empty() const noexcept override;

	friend bool api::operator==(const api::ILangStringSet & left, const api::ILangStringSet & right);
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_COMMON_LANGSTRINGSET_H */
