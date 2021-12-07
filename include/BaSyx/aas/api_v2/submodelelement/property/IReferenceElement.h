/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_PROPERTY_IREFERENCEELEMENT_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_PROPERTY_IREFERENCEELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/IDataElement.h>
#include <BaSyx/aas/api_v2/reference/IReference.h>

namespace basyx {
namespace aas {
namespace api {


class IReferenceElement : public virtual IDataElement
{
public:
	virtual ~IReferenceElement() = 0;

	virtual const IReference * const getValue() const = 0;
	virtual void setValue(const IReference & value) = 0;
};

inline IReferenceElement::~IReferenceElement() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_PROPERTY_IREFERENCEELEMENT_H */
