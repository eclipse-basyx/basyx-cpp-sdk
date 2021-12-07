/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_QUALIFIER_IDENTIFIABLE_H
#define BASYX_SUBMODEL_SIMPLE_QUALIFIER_IDENTIFIABLE_H

#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/simple/qualifier/Referable.h>
#include <BaSyx/aas/simple/qualifier/AdministrativeInformation.h>

namespace basyx {
namespace aas {
namespace simple {

class Identifiable
    : public virtual api::IIdentifiable
    , public Referable
{
private:
	Identifier identifier;
	AdministrativeInformation administrativeInformation;
public:
	virtual ~Identifiable() = default;

	// Constructors
	Identifiable(const std::string & idShort, const Identifier & identifier);
	explicit Identifiable(const api::IIdentifiable & other);

	bool hasAdministrativeInformation() const noexcept override;

	// Inherited via IIdentifiable
	const AdministrativeInformation & getAdministrativeInformation() const override;
	AdministrativeInformation & getAdministrativeInformation() override;

	Identifier getIdentification() const override;

	void setAdministrativeInformation(const AdministrativeInformation & administrativeInformation);
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_QUALIFIER_IDENTIFIABLE_H */
