/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IEMBEDDEDDATASPECIFICATION_H
#define BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IEMBEDDEDDATASPECIFICATION_H

#include <BaSyx/aas/api_v2/reference/IReference.h>

namespace basyx {
namespace aas {
namespace api {

class IEmbeddedDataSpecification
{
public:
  virtual ~IEmbeddedDataSpecification() = 0;

  virtual IReference * getDataSpecifaction() const = 0;
};

inline IEmbeddedDataSpecification::~IEmbeddedDataSpecification() = default;

}
}
}
#endif /* BASYX_SUBMODEL_API_V2_DATASPECIFICATION_IEMBEDDEDDATASPECIFICATION_H */
