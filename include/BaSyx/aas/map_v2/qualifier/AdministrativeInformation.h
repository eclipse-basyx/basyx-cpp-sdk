/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_QUALIFIER_ADMINISTRATIVEINFORMATION_H
#define BASYX_SUBMODEL_MAP_V2_QUALIFIER_ADMINISTRATIVEINFORMATION_H

#include <BaSyx/aas/api_v2/qualifier/IAdministrativeInformation.h>

#include <BaSyx/aas/map_v2/qualifier/HasDataSpecification.h>
#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

class AdministrativeInformation
  : public virtual api::IAdministrativeInformation
  , public HasDataSpecification
  , public virtual vab::ElementMap
{
public:
  struct Path {
    static constexpr char Version[] = "version";
    static constexpr char Revision[] = "revision";
  };

public:
  AdministrativeInformation();
  AdministrativeInformation(const std::string & version, const std::string & revision);
  AdministrativeInformation(basyx::object);

  void setVersion(const std::string & version) override;
  void setRevision(const std::string & revision) override;

  bool hasVersion() const override;
  bool hasRevision() const override;

  const std::string * const getVersion() const override;
  const std::string * const getRevision() const override;
};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_QUALIFIER_ADMINISTRATIVEINFORMATION_H */
