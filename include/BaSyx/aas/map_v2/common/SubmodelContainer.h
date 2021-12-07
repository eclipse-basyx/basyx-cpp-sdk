/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_COMMON_SUBMODELCONTAINER_H
#define BASYX_SUBMODEL_MAP_V2_COMMON_SUBMODELCONTAINER_H

#include <BaSyx/aas/api_v2/ISubmodel.h>
#include <BaSyx/aas/map_v2/common/ElementContainer.h>
#include <BaSyx/vab/ElementMap.h>

#include <unordered_map>
#include <algorithm>

namespace basyx {
namespace aas {
namespace map {

class SubmodelContainer : public map::ElementContainer<api::ISubmodel>
{
public:

};


}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_COMMON_SUBMODELCONTAINER_H */
