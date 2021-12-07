/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_COMMON_ILANGSTRINGSET_H
#define BASYX_SUBMODEL_API_V2_COMMON_ILANGSTRINGSET_H

#include <string>
#include <initializer_list>
#include <unordered_set>
#include <unordered_map>

namespace basyx {
namespace aas {
namespace api {

class ILangStringSet
{
public:
	using langCodeSet_t = std::unordered_set<std::string>;
public:
	virtual ~ILangStringSet();

	virtual langCodeSet_t getLanguageCodes() const = 0;

	virtual const std::string & get(const std::string & languageCode) const = 0;
	virtual void add(const std::string & languageCode, const std::string & langString) = 0;
	virtual bool empty() const noexcept = 0;
};

inline ILangStringSet::~ILangStringSet() = default;

bool operator==(const api::ILangStringSet & left, const api::ILangStringSet & right);

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_COMMON_ILANGSTRINGSET_H */
