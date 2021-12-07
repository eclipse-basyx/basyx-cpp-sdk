/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATION_H
#define BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATION_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecification.h>

#include <BaSyx/aas/simple/qualifier/Identifiable.h>

namespace basyx {
namespace aas {
namespace simple {

class DataSpecification : public api::IDataSpecification
{
private:
	Identifiable ident;
	std::unique_ptr<api::IDataSpecificationContent> content;
public:
	~DataSpecification() = default;
	DataSpecification(const std::string & idShort, const Identifier & identifier);

	void setContent(std::unique_ptr<api::IDataSpecificationContent> content);

	// Inherited via IDataSpecification
	virtual api::IDataSpecificationContent & getContent() override;

	// Inherited via IIdentifiable
	virtual const std::string & getIdShort() const override;
	virtual const std::string * const getCategory() const override;
	void setCategory(const std::string & category) override;
	virtual simple::LangStringSet & getDescription() override;
	virtual const simple::LangStringSet & getDescription() const override;
	virtual IReferable * getParent() const override;
	virtual void setParent(IReferable * parent) override;
	virtual const AdministrativeInformation & getAdministrativeInformation() const override;
	virtual AdministrativeInformation & getAdministrativeInformation() override;
	virtual Identifier getIdentification() const override;
	virtual bool hasAdministrativeInformation() const override;
	virtual simple::Reference getReference() const override;

        virtual Key getKey(bool local = true) const override { return ident.getKey(); }

};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_DATASPECIFICATION_DATASPECIFICATION_H */
