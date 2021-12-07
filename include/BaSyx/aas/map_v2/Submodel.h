/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_SUBMODEL_H
#define BASYX_SUBMODEL_MAP_V2_SUBMODEL_H


#include <BaSyx/aas/api_v2/ISubmodel.h>
#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/map_v2/qualifier/Identifiable.h>
#include <BaSyx/aas/map_v2/qualifier/Qualifiable.h>
#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/map_v2/reference/Reference.h>

#include <BaSyx/aas/map_v2/common/ModelType.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>

#include <memory>
#include <vector>
#include <unordered_map>


namespace basyx {
namespace aas {
namespace map {

class Submodel : 
	public virtual api::ISubmodel,
	public Identifiable,
	public HasDataSpecification,
	public Qualifiable,
	public ModelType<ModelTypes::Submodel>,
	public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char SubmodelElements[] = "submodelElements";
    static constexpr char SemanticId[] = "semanticId";
    static constexpr char Kind[] = "kind";
  };
private:
  std::unique_ptr<Reference> semanticId;
	ElementContainer<api::ISubmodelElement> elementContainer;
public:
	Submodel(const std::string & idShort, const simple::Identifier & identifier, ModelingKind kind = ModelingKind::Instance);
	Submodel(basyx::object object);

	virtual ~Submodel() = default;
public:
	virtual api::IElementContainer<api::ISubmodelElement> & submodelElements() override;
	virtual const api::IElementContainer<api::ISubmodelElement> & submodelElements() const override;

	// Inherited via IHasKind
	virtual ModelingKind getKind() const override;

	// Inherited via IHasSemantics
	virtual const api::IReference * getSemanticId() const override;
	virtual void setSemanticId(std::unique_ptr<Reference> semanticId);

	virtual KeyElements getKeyElementType() const override { return KeyElements::Submodel; };
};


}
}
}


#endif /* BASYX_SUBMODEL_MAP_V2_SUBMODEL_H */
