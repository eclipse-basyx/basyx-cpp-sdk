/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include "gtest/gtest.h"
#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/vab/core/util/VABPath.h>
#include <BaSyx/opcua/aas/provider/AASProviderApiParseHelpers.h>

namespace tests_opcua_model_provider_utils
{
    using namespace basyx::opcua;
    using namespace basyx::aas;

    class OPCUAModeProviderUtilitiesTest : public ::testing::Test
    {
    };

    TEST_F(OPCUAModeProviderUtilitiesTest, aasAPI)
    {
        using namespace basyx::vab::core;
        using namespace basyx::opcua::aas;

        basyx::vab::core::VABPath pathAAS("shells/xyz/aas");
        basyx::vab::core::VABPath pathNoAAS("shells/xyz");

        ASSERT_TRUE(AASProviderApiParseHelpers::isApiShellsAASIdAAS(pathAAS));
        ASSERT_FALSE(AASProviderApiParseHelpers::isApiShellsAASId(pathAAS));

        ASSERT_FALSE(AASProviderApiParseHelpers::isApiShellsAASIdAAS(pathNoAAS));
        ASSERT_TRUE(AASProviderApiParseHelpers::isApiShellsAASId(pathNoAAS));
    }

    TEST_F(OPCUAModeProviderUtilitiesTest, submodelAPI)
    {
        using namespace basyx::vab::core;
        using namespace basyx::opcua::aas;

        basyx::vab::core::VABPath path1("shells/xyz/aas");

        basyx::vab::core::VABPath path_isAPISubmodelsIdShort("shells/xyz/aas/submodels/abc");
        basyx::vab::core::VABPath path_isAPISubmodels("shells/xyz/aas/submodels");
        basyx::vab::core::VABPath path_isAPISubmodelsSubmodel("shells/xyz/aas/submodels/abc/submodel");
        basyx::vab::core::VABPath path_isAPISubmodelValues("shells/xyz/aas/submodels/abc/submodel/values");
        basyx::vab::core::VABPath path_isAPISubmodelElements("shells/xyz/aas/submodels/abc/submodel/submodelElements");
        basyx::vab::core::VABPath path_isAPISubmodelElementsIdShort("shells/xyz/aas/submodels/abc/submodel/submodelElements/jkl");
        basyx::vab::core::VABPath path_isAPISubmodelElementsValue("shells/xyz/aas/submodels/abc/submodel/submodelElements/jkl/value");
        basyx::vab::core::VABPath path_isAPISubmodelElementsInvoke("shells/xyz/aas/submodels/abc/submodel/submodelElements/jkl/invoke");

        /* API : shells/{aasID}/aas/submodels*/

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelsIdShort(path_isAPISubmodelsIdShort));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodels(path_isAPISubmodels));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelsSubmodel(path_isAPISubmodelsSubmodel));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelValues(path_isAPISubmodelValues));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelElements(path_isAPISubmodelElements));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelElementsIdShort(path_isAPISubmodelElementsIdShort));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelElementsValue(path_isAPISubmodelElementsValue));

        ASSERT_TRUE(AASProviderApiParseHelpers::isAPISubmodelElementsInvoke(path_isAPISubmodelElementsInvoke));
    }
}

