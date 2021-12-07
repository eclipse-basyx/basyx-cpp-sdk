/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ISUBMODELELEMENTCOLLECTION_H
#define BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ISUBMODELELEMENTCOLLECTION_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/api_v2/common/IElementContainer.h>


namespace basyx {
namespace aas {
namespace api {


class ISubmodelElementCollection : public virtual ISubmodelElement
{
public:
	virtual ~ISubmodelElementCollection() = 0;

	virtual IElementContainer<ISubmodelElement> & getSubmodelElements() = 0;

	virtual bool isOrdered() const = 0;
	virtual bool isAllowDuplicates() const = 0;
};

inline ISubmodelElementCollection::~ISubmodelElementCollection() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_SUBMODELELEMENT_ISUBMODELELEMENTCOLLECTION_H */
