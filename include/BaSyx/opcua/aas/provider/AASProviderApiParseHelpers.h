/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef AAS_PROVIDER_API_PARSE_HELPERS_H
#define AAS_PROVIDER_API_PARSE_HELPERS_H

#include <BaSyx/shared/object.h>
#include <BaSyx/shared/types.h>
#include <BaSyx/vab/core/util/VABPath.h>
#include <BaSyx/opcua/common/Utilities.h>
#include <BaSyx/opcua/aas/provider/AASModelProviderCommon.h>

namespace basyx
{
    namespace opcua
    {
        namespace aas
        {
            struct AASProviderApiParseHelpers
            {
                /* API : shells/{aasID}/aas*/
                static bool isApiShellsAASIdAAS(const vab::core::VABPath& t_path);

                /* API : shells/{aasID}*/
                static bool isApiShellsAASId(const vab::core::VABPath& t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort} */
                static bool isAPISubmodelsIdShort(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels*/
                static bool isAPISubmodels(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel */
                static bool isAPISubmodelsSubmodel(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/values */
                static bool isAPISubmodelValues(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements*/
                static bool isAPISubmodelElements(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort} */
                static bool isAPISubmodelElementsIdShort(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShort}/value */
                static bool isAPISubmodelElementsValue(const vab::core::VABPath & t_path);

                /* API : shells/{aasID}/aas/submodels/{submodelIdshort}/submodel/submodelElements/{seIdShortOperation}/invoke */
                static bool isAPISubmodelElementsInvoke(const vab::core::VABPath & t_path);

                /* Returns a tuple <aasId, smId, smEleId> */
                static std::tuple<std::string, std::string, std::string> parseIdentifiers(const vab::core::VABPath & t_path);
            };
        }
    }
}
#endif