/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_QUALIFIER_IHASKIND_H
#define BASYX_SUBMODEL_API_V2_QUALIFIER_IHASKIND_H

#include <string>

#include <BaSyx/aas/enumerations/ModelingKind.h>

#include <BaSyx/util/util.h>

namespace basyx {
namespace aas {

class IHasKind
{
public:
	virtual ~IHasKind() = default;
	virtual ModelingKind getKind() const = 0;
};


}
}
#endif /* BASYX_SUBMODEL_API_V2_QUALIFIER_IHASKIND_H */
