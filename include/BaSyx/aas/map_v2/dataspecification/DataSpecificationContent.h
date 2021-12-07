/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONCONTENT_H
#define BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONCONTENT_H

#include <BaSyx/aas/api_v2/dataspecification/IDataSpecificationContent.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {

class DataSpecificationContent
    : public api::IDataSpecificationContent
    , public virtual vab::ElementMap
{};

}
}
}
#endif /* BASYX_SUBMODEL_MAP_V2_DATASPECIFICATION_DATASPECIFICATIONCONTENT_H */
