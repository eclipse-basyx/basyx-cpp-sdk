/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#pragma once

#include <BaSyx/submodel/api_v2/aas/IAssetAdministrationShell.h>

#include <memory>

namespace basyx {
namespace tests {
namespace opcua {

class support {
public:
	static std::unique_ptr<submodel::api::IAssetAdministrationShell> support::buildTestAAS();
};

}
}
}