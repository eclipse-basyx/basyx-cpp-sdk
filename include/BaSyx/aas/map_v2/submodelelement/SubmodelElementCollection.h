/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_SUBMODELELEMENTCOLLECTION_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_SUBMODELELEMENTCOLLECTION_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElementCollection.h>
#include <BaSyx/aas/map_v2/submodelelement/SubmodelElement.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/aas/map_v2/common/ModelType.h>


namespace basyx {
namespace aas {
namespace map {


class SubmodelElementCollection
  : public api::ISubmodelElementCollection
  , public SubmodelElement
  , public ModelType<ModelTypes::SubmodelElementCollection>
{
public:
	struct Path {
		static constexpr char Value[] = "value";
		static constexpr char Ordered[] = "ordered";
		static constexpr char AllowDuplicates[] = "allowDuplicates";
	};

private:
	ElementContainer<ISubmodelElement> elementContainer;

public:
	SubmodelElementCollection(const char * idShort, ModelingKind Kind = ModelingKind::Instance, bool ordered = false, bool allowDuplicates = false);
	SubmodelElementCollection(const std::string & idShort, ModelingKind Kind = ModelingKind::Instance, bool ordered = false, bool allowDuplicates = false);
    SubmodelElementCollection(basyx::object);

	virtual ~SubmodelElementCollection() = default;

	virtual api::IElementContainer<ISubmodelElement> & getSubmodelElements() override;

	void addElement(std::unique_ptr<SubmodelElement>);

	virtual bool isOrdered() const override;
	virtual bool isAllowDuplicates() const override;

	virtual KeyElements getKeyElementType() const override { return KeyElements::SubmodelElementCollection; };
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODELELEMENT_SUBMODELELEMENTCOLLECTION_H */
