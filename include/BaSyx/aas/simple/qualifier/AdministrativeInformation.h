/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_SIMPLE_QUALIFIER_ADMINISTRATIVEINFORMATION_H
#define BASYX_SUBMODEL_SIMPLE_QUALIFIER_ADMINISTRATIVEINFORMATION_H

#include <BaSyx/aas/simple/qualifier/HasDataSpecification.h>
#include <BaSyx/aas/api_v2/qualifier/IAdministrativeInformation.h>

namespace basyx {
namespace aas {
namespace simple {

class AdministrativeInformation
  : public api::IAdministrativeInformation
  , public HasDataSpecification
{
private:
	std::string version;
	std::string revision;
public:
	~AdministrativeInformation() = default;

	AdministrativeInformation();
	AdministrativeInformation(const std::string & version, const std::string & revision);
	explicit AdministrativeInformation(const IAdministrativeInformation & other);

	void setVersion(const std::string & version) override;
	void setRevision(const std::string & revision) override;

	inline bool hasVersion() const override { return !version.empty(); };
	inline bool hasRevision() const override { return !revision.empty(); };

	inline bool exists() const noexcept { return !version.empty() && !revision.empty(); };

	virtual const std::string * const getVersion() const override;
	virtual const std::string * const getRevision() const override;
};

}
}
}

#endif /* BASYX_SUBMODEL_SIMPLE_QUALIFIER_ADMINISTRATIVEINFORMATION_H */
