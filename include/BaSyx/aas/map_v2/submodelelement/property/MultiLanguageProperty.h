/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_MULTILANGUAGEPROPERTY_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_MULTILANGUAGEPROPERTY_H

#include <BaSyx/aas/api_v2/submodelelement/property/IMultiLanguageProperty.h>
#include <BaSyx/aas/map_v2/submodelelement/DataElement.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>
#include <BaSyx/aas/map_v2/common/LangStringSet.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>

namespace basyx {
namespace aas {
namespace map {


class MultiLanguageProperty : 
	public api::IMultiLanguageProperty,
	public DataElement,
	public ModelType<ModelTypes::MultiLanguageProperty>
{
public:
  struct Path {
    static constexpr char Value[] = "value";
    static constexpr char ValueId[] = "valueId";
    static constexpr char Kind[] = "kind";
  };
private:
	std::unique_ptr<LangStringSet> value;
	std::unique_ptr<Reference> valueId;

public:
	MultiLanguageProperty(const std::string & idShort, ModelingKind kind = ModelingKind::Instance);
  MultiLanguageProperty(basyx::object);

	virtual ~MultiLanguageProperty() = default;

	virtual const api::ILangStringSet * const getValue() override;
	void setValue(std::unique_ptr<LangStringSet>);

	virtual const api::IReference * const getValueId() const override;
	virtual void setValueId(std::unique_ptr<Reference> valueId);

	virtual KeyElements getKeyElementType() const override { return KeyElements::MultiLanguageProperty; };
};


}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_PROPERTY_MULTILANGUAGEPROPERTY_H */
