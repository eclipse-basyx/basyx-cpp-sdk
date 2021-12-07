/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_REFERENCE_KEY_H
#define BASYX_SUBMODEL_SIMPLE_REFERENCE_KEY_H

#include <BaSyx/aas/enumerations/KeyType.h>
#include <BaSyx/aas/enumerations/KeyElements.h>
//#include <BaSyx/aas/api_v2/reference/IKey.h>

#include <string>

namespace basyx {
namespace aas {
namespace simple {

class Key // : public api::IKey
{
private:
	KeyElements type;
	KeyType idType;
	bool local;
	std::string value;
public:
	Key(KeyElements type, bool local, KeyType idType, const std::string & value);
public:
	bool operator!=(const Key & other) const;
	inline bool operator==(const Key & other) const { return !(*this != other); };
public:
	KeyElements getType() const noexcept;
	KeyType getIdType() const noexcept;
	bool isLocal() const noexcept;
	std::string getValue() const noexcept;

	bool isGlobalKey() const noexcept;
	bool isModelKey() const noexcept;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_REFERENCE_KEY_H */
