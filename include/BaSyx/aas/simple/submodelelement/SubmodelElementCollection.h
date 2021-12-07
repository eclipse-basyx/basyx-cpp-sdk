/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_SUBMODELELEMENTCOLLECTION_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_SUBMODELELEMENTCOLLECTION_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElementCollection.h>
#include <BaSyx/aas/simple/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/simple/common/ElementContainer.h>


namespace basyx {
namespace aas {
namespace simple {


class SubmodelElementCollection
  : public SubmodelElement
  , public api::ISubmodelElementCollection
{
private:
	ElementContainer<ISubmodelElement> elementContainer;
	bool ordered;
	bool allowDuplicates;

public:
	SubmodelElementCollection(const std::string & idShort, ModelingKind = ModelingKind::Instance, bool ordered = false, bool allowDuplicates = false);

	virtual ~SubmodelElementCollection() = default;

	virtual api::IElementContainer<ISubmodelElement> & getSubmodelElements() override;

	void addElement(std::unique_ptr<SubmodelElement>);

	virtual bool isOrdered() const override;
	virtual bool isAllowDuplicates() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_SUBMODELELEMENTCOLLECTION_H */
