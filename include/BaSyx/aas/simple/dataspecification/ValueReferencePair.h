/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUEREFERENCEPAIR_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUEREFERENCEPAIR_H

#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/shared/object/object_type.h>
#include <BaSyx/shared/object.h>

#include <string>
#include <BaSyx/aas/map_v2/reference/Reference.h>

namespace basyx {
namespace aas {
namespace simple {

class ValueReferencePair
{
private:
	std::string value;
	Reference valueId;

public:
	ValueReferencePair() = default;
	ValueReferencePair(const ValueReferencePair & other) = default;
	ValueReferencePair(ValueReferencePair && other) noexcept = default;

	ValueReferencePair & operator=(const ValueReferencePair & other) = default;
	ValueReferencePair & operator=(ValueReferencePair && other) noexcept = default;

	ValueReferencePair(const std::string & value, const api::IReference & valueId)
		: value(value), valueId(valueId)
	{};

	~ValueReferencePair() = default;
public:
	const std::string & getValue() const { return this->value; };
	const api::IReference & getValueId() const { return this->valueId; };
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_VALUEREFERENCEPAIR_H */
