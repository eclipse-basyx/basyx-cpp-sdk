/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_REFERENCEELEMENT_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_REFERENCEELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/property/IReferenceElement.h>
#include <BaSyx/aas/simple/submodelelement/DataElement.h>
#include <BaSyx/aas/simple/reference/Reference.h>

namespace basyx {
namespace aas {
namespace simple {


class ReferenceElement
  : public virtual api::IReferenceElement
  , public DataElement
{
private:
	Reference value;
public:
	ReferenceElement(const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
	virtual ~ReferenceElement() = default;

	virtual const api::IReference * const getValue() const override;
	virtual void setValue(const api::IReference & value) override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_REFERENCEELEMENT_H */
