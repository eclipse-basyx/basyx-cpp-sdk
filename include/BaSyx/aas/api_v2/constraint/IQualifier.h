/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_CONSTRAINT_IQUALIFIER_H
#define BASYX_SUBMODEL_API_V2_CONSTRAINT_IQUALIFIER_H

#include <BaSyx/aas/api_v2/constraint/IConstraint.h>
#include <BaSyx/aas/api_v2/qualifier/IHasSemantics.h>
#include <BaSyx/aas/api_v2/reference/IReference.h>
#include <BaSyx/aas/api_v2/submodelelement/IRange.h>

#include <string>

namespace basyx {
namespace aas {

using QualifierType = std::string;

namespace api {

class IQualifier : public IConstraint, public virtual IHasSemantics
{
  using ValueDataType = std::string;
public:
	virtual ~IQualifier() = 0;

	virtual const QualifierType getQualifierType() const = 0;
	virtual const DataTypeDef getValueType() const = 0;

	virtual const ValueDataType * const getValueDataType() const = 0;
	virtual void setValueDataType(const ValueDataType & valueDataType) = 0;

	virtual const IReference * const getValueId() const = 0;
	virtual void setValueId(const IReference & reference) = 0;
};

inline IQualifier::~IQualifier() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_CONSTRAINT_IQUALIFIER_H */
