/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_SUBMODEL_H
#define BASYX_SUBMODEL_SIMPLE_SUBMODEL_H


#include <BaSyx/aas/api_v2/ISubmodel.h>
#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/simple/qualifier/Identifiable.h>
#include <BaSyx/aas/simple/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/simple/qualifier/Qualifiable.h>

#include <BaSyx/aas/simple/common/ElementContainer.h>

#include <memory>
#include <vector>
#include <unordered_map>


namespace basyx {
namespace aas {
namespace simple {


class Submodel : public api::ISubmodel
{
private:
	Identifiable identifiable;
	ModelingKind kind;
	HasDataSpecification dataSpecification;
  std::unique_ptr<Reference> semanticId;
	Qualifiable qualifiable;

	ElementContainer<api::ISubmodelElement> elementContainer;
public:
	Submodel(const std::string & idShort, const Identifier & identifier);

	virtual ~Submodel() = default;
public:
	virtual api::IElementContainer<api::ISubmodelElement> & submodelElements();
	virtual const api::IElementContainer<api::ISubmodelElement> & submodelElements() const;

	// Inherited via IHasKind
	virtual ModelingKind getKind() const override;

	// Inherited via IReferable
	virtual const std::string & getIdShort() const override;
	virtual const std::string * const getCategory() const override;
	virtual void setCategory(const std::string & category) override;
	virtual simple::LangStringSet & getDescription() override;
	virtual const simple::LangStringSet & getDescription() const override;
	
	virtual IReferable * getParent() const override;
	virtual void setParent(IReferable * parent) override;
	
	// Inherited via IIdentifiable
	virtual const AdministrativeInformation & getAdministrativeInformation() const override;
	virtual AdministrativeInformation & getAdministrativeInformation() override;

	virtual Identifier getIdentification() const override;

	virtual bool hasAdministrativeInformation() const;

	// Inherited via IHasDataSpecification
	virtual void addDataSpecification(const Reference & reference) override;
	virtual const std::vector<Reference> getDataSpecificationReference() const override;

	// Inherited via IHasSemantics
	virtual const api::IReference * getSemanticId() const override;
	virtual void setSemanticId(std::unique_ptr<Reference> semanticId);

	// Inherited via IQualifiable
	virtual void addFormula(const api::IFormula & formula) override;
	virtual void addQualifier(const api::IQualifier & qualifier) override;

	virtual std::vector<simple::Formula> getFormulas() const override;
	virtual std::vector<simple::Qualifier> getQualifiers() const override;

	virtual KeyElements getKeyElementType() const override { return KeyElements::Submodel; };
	virtual simple::Reference getReference() const override;
	virtual simple::Key getKey(bool local = true) const override;
};


}
}
}


#endif /* BASYX_SUBMODEL_SIMPLE_SUBMODEL_H */
