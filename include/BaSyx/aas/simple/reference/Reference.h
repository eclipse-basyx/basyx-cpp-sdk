/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_REFERENCE_REFERENCE_H
#define BASYX_SUBMODEL_SIMPLE_REFERENCE_REFERENCE_H

#include <BaSyx/aas/api_v2/reference/IReference.h>

#include <BaSyx/aas/simple/reference/Key.h>

#include <vector>

namespace basyx {
namespace aas {
namespace simple {

class Reference : public api::IReference
{
private:
	std::vector<Key> keyList;
public:
	virtual ~Reference() = default;

	Reference(const api::IReference & other);
	Reference(const Reference & other) = default;
	Reference(Reference && other) noexcept = default;

	Reference & operator=(const Reference & other) = default;
	Reference & operator=(Reference && other) noexcept = default;

	Reference(const Key & key);
	Reference(const std::vector<Key> & keys);
	Reference(std::vector<Key> && keys);
	Reference(const std::initializer_list<Key> keys);

	Reference() = default;
public:
	bool operator!=(const Reference & other) const;
	inline bool operator==(const Reference & other) const { return !(*this != other); };

	bool operator!=(const api::IReference & other) const;
	inline bool operator==(const api::IReference & other) const { return !(*this != other); };
public:
	std::vector<Key> getKeys() const override;
	void addKey(const Key & key) override;

	bool empty() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_REFERENCE_REFERENCE_H */
