/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/aas/api_v2/ApiMetamodelUtilities.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            bool ApiMetamodelUtilities::isPropertyType(const ISubmodelElement_t * t_submodelElement)
            {
                if (t_submodelElement != nullptr)
                    return (dynamic_cast<const basyx::aas::api::IProperty*>(t_submodelElement) != nullptr);

                return false;
            }
        }
    }
}