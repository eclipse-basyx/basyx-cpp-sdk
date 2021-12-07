/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_MULTILANGUAGEPROPERTY_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_MULTILANGUAGEPROPERTY_H

#include <BaSyx/aas/api_v2/submodelelement/property/IMultiLanguageProperty.h>
#include <BaSyx/aas/simple/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/simple/reference/Reference.h>
#include <BaSyx/aas/simple/common/LangStringSet.h>

namespace basyx {
namespace aas {
namespace simple {


class MultiLanguageProperty : 
	public api::IMultiLanguageProperty,
	public SubmodelElement
{
private:
	std::unique_ptr<LangStringSet> value;
	std::unique_ptr<Reference> valueId;
public:
	MultiLanguageProperty(const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
	virtual ~MultiLanguageProperty() = default;

	virtual const api::ILangStringSet * const getValue() override;

	virtual const api::IReference * const getValueId() const override;
	virtual void setValueId(std::unique_ptr<Reference> valueId);
};


}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_PROPERTY_MULTILANGUAGEPROPERTY_H */
