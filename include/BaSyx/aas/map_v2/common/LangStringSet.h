/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_COMMON_LANGSTRINGSET_H
#define BASYX_SUBMODEL_MAP_V2_COMMON_LANGSTRINGSET_H

#include <BaSyx/aas/api_v2/common/ILangStringSet.h>
#include <BaSyx/vab/ElementMap.h>

#include <string>
#include <initializer_list>
#include <vector>
#include <unordered_map>

namespace basyx {
namespace aas {
namespace map {

class LangStringSet : 
	public api::ILangStringSet,
	public virtual vab::ElementMap
{
public:
	struct Path {
		static constexpr char Text[] = "text";
		static constexpr char Language[] = "language";
	};
public:
	using langStringMap_t = std::unordered_map<std::string, std::string>;
private:
	langStringMap_t langStrings;
public:
	using vab::ElementMap::ElementMap;

	LangStringSet();
  LangStringSet(const ILangStringSet & other);

  static LangStringSet from_object(basyx::object);

	virtual langCodeSet_t getLanguageCodes() const override;

	virtual const std::string & get(const std::string & languageCode) const override;
	virtual void add(const std::string & languageCode, const std::string & langString) override;
	virtual bool empty() const noexcept override;

  friend bool api::operator==(const api::ILangStringSet & left, const api::ILangStringSet & right);
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_COMMON_LANGSTRINGSET_H */
