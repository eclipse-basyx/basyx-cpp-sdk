/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_QUALIFIER_IADMINISTRATIVEINFORMATION_H
#define BASYX_SUBMODEL_API_V2_QUALIFIER_IADMINISTRATIVEINFORMATION_H

#include <BaSyx/aas/api_v2/qualifier/IHasDataSpecification.h>

#include <string>

namespace basyx {
namespace aas {
namespace api {

class IAdministrativeInformation
  : public virtual IHasDataSpecification
{
public:
  virtual ~IAdministrativeInformation() = 0;

  virtual void setVersion(const std::string & version) = 0;
  virtual void setRevision(const std::string & revision) = 0;

  virtual bool hasVersion() const = 0;
  virtual bool hasRevision() const = 0;

  virtual const std::string * const getVersion() const = 0;
  virtual const std::string * const getRevision() const = 0;
};

inline IAdministrativeInformation::~IAdministrativeInformation() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IADMINISTRATIVEINFORMATION_H */
