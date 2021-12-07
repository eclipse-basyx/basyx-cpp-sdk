/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_PROPERTY_IPROPERTY_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_PROPERTY_IPROPERTY_H

#include <BaSyx/aas/api_v2/submodelelement/IDataElement.h>
#include <BaSyx/aas/api_v2/reference/IReference.h>

#include <BaSyx/shared/types.h>

namespace basyx {
namespace aas {
namespace api {


class IProperty : public virtual IDataElement
{
public:
	virtual ~IProperty() = 0;

	virtual const std::string & getValueType() const = 0;
	virtual void setValueType(const std::string & valueType) = 0;

	virtual basyx::object getObject() = 0;
	virtual void setObject(basyx::object & object) = 0;

	virtual const IReference * const getValueId() const = 0;
	virtual void setValueId(const IReference & valueId) = 0;
};

inline IProperty::~IProperty() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_PROPERTY_IPROPERTY_H */
