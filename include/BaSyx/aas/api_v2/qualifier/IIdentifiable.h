/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_QUALIFIER_IIDENTIFIABLE_H
#define BASYX_SUBMODEL_API_V2_QUALIFIER_IIDENTIFIABLE_H

#include <BaSyx/aas/api_v2/qualifier/IReferable.h>
#include <BaSyx/aas/api_v2/qualifier/IAdministrativeInformation.h>
#include <BaSyx/aas/simple/identifier/Identifier.h>


#include <string>
#include <memory>

namespace basyx {
namespace aas {
namespace api {

class IIdentifiable : public virtual IReferable
{
public:
  virtual ~IIdentifiable() = 0;

  virtual const IAdministrativeInformation & getAdministrativeInformation() const = 0;
  virtual IAdministrativeInformation & getAdministrativeInformation() = 0;

  virtual simple::Identifier getIdentification() const = 0;

  virtual bool hasAdministrativeInformation() const = 0;

  virtual KeyType getKeyType() const {
	  return this->getIdentification().getIdType();
  };
};

inline IIdentifiable::~IIdentifiable() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IIDENTIFIABLE_H */
