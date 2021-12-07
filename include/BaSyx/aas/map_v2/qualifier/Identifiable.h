/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_QUALIFIER_IDENTIFIABLE_H
#define BASYX_SUBMODEL_MAP_V2_QUALIFIER_IDENTIFIABLE_H

#include <BaSyx/aas/api_v2/qualifier/IIdentifiable.h>
#include <BaSyx/aas/map_v2/qualifier/Referable.h>
#include <BaSyx/aas/map_v2/qualifier/AdministrativeInformation.h>

namespace basyx {
namespace aas {
namespace map {

class Identifiable
	: public virtual api::IIdentifiable
	, public virtual vab::ElementMap
	, public Referable
{
public:
  struct Path {
    static constexpr char IdType[] = "idType";
    static constexpr char Id[] = "id";
    static constexpr char AdministrativeInformation[] = "administration";
    static constexpr char Identifier[] = "identification";
  };
private:
	map::AdministrativeInformation administrativeInformation;
public:
	virtual ~Identifiable() = default;

	// Constructors
	Identifiable(const std::string & idShort, const simple::Identifier & identifier);

	bool hasAdministrativeInformation() const noexcept override;

	// Inherited via IIdentifiable
	const api::IAdministrativeInformation & getAdministrativeInformation() const override;
	api::IAdministrativeInformation & getAdministrativeInformation() override;

	virtual simple::Identifier getIdentification() const override;

  void setAdministrativeInformation(const AdministrativeInformation & administrativeInformation);
};

}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_QUALIFIER_IDENTIFIABLE_H */
