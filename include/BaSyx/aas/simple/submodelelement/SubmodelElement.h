/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_SUBMODELELEMENT_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_SUBMODELELEMENT_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>

#include <BaSyx/aas/simple/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/api_v2/qualifier/IHasKind.h>
#include <BaSyx/aas/simple/qualifier/Referable.h>
#include <BaSyx/aas/simple/qualifier/Qualifiable.h>


namespace basyx {
namespace aas {
namespace simple {

class SubmodelElement
  : public virtual api::ISubmodelElement
{
private:
	HasDataSpecification dataSpecification;
	ModelingKind kind;
  std::unique_ptr<Reference> semanticId;
	Referable referable;
	Qualifiable qualifiable;
	ModelTypes modelType;
public:
	SubmodelElement(const std::string & idShort, ModelingKind kind = ModelingKind::Instance);

	~SubmodelElement() = default;

	// Inherited via IHasDataSemantics
	const api::IReference * getSemanticId() const override;
	void setSemanticId(std::unique_ptr<Reference> semanticId);

	// Inherited via IHasDataSpecification
	void addDataSpecification(const Reference & reference) override;
	const std::vector<Reference> getDataSpecificationReference() const override;

	// Inherited via IReferable
	const std::string & getIdShort() const override;
	const std::string * const getCategory() const override;
  	void setCategory(const std::string & category) override;
	simple::LangStringSet & getDescription() override;
	const simple::LangStringSet & getDescription() const override;
	IReferable * getParent() const override;
	void setParent(IReferable * parent) override;
	Key getKey(bool local) const override;
	simple::Reference getReference() const override;

	// Inherited via IHasKind
	ModelingKind getKind() const override;

	// Inherited via IQualifiable
	std::vector<Formula> getFormulas() const override;
	std::vector<Qualifier> getQualifiers() const override;
	void addFormula(const api::IFormula & formula) override;
	void addQualifier(const api::IQualifier & qualifier) override;

  // Inherited vie IModelType
  ModelTypes GetModelType() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODELELEMENT_SUBMODELELEMENT_H */
