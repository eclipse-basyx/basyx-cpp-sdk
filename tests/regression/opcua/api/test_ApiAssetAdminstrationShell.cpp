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
#include <BaSyx/opcua/common/Services.h>
#include <BaSyx/opcua/aas/metamodel/AASMetamodel.h>
#include <BaSyx/opcua/aas/api_v2/ApiAssetAdminstrationShell.h>
#include <tests/regression/opcua/OPCUATestSetup.h>

namespace basyx
{
    namespace tests
    {
        namespace opcua_aas_api
        {
            using namespace basyx::opcua;
            using namespace aas::metamodel;
            using namespace basyx::aas;

            class ApiAssetAdminstrationShell_test : public ::testing::Test
            {

            public:
                std::unique_ptr<opcua::OPCUATestSetup> m_opcuaSetup;
                const int serverPort = 6004;
            public:
                virtual void SetUp()
                {
                    m_opcuaSetup = util::make_unique<opcua::OPCUATestSetup>(serverPort);
                }
                virtual void TearDown()
                {
                    m_opcuaSetup->getServer().abort();
                }
                /* Build a simple minimal AAS  */
                std::unique_ptr<map::AssetAdministrationShell> AAS()
                {
                    /* Build an AssetAdministrationShell */
                    auto aas = util::make_unique<map::AssetAdministrationShell>("aas_foo",
                        simple::Identifier::Custom("aas_foo_ident"),
                        map::Asset{ std::string(), simple::Identifier::Custom(std::string()) }
                    );

                    /* Set Administration attributes */
                    aas->setAdministrativeInformation(basyx::aas::map::AdministrativeInformation("1", "2"));

                    return std::move(aas);
                }

                /* Build Submodels */
                std::vector<std::unique_ptr<map::Submodel>> SMS()
                {
                    std::vector<std::unique_ptr<map::Submodel>> ret;

                    auto sm_foo_1 = util::make_unique <map::Submodel>("foo_idshort1", simple::Identifier::Custom("foo_idlong1"));
                    sm_foo_1->setAdministrativeInformation(map::AdministrativeInformation("1", "0"));
                    auto sm_foo_2 = util::make_unique <map::Submodel>("foo_idshort2", simple::Identifier::Custom("foo_idlong2"));
                    sm_foo_2->setAdministrativeInformation(map::AdministrativeInformation("alpha", "_0"));
                    ret.push_back(std::move(sm_foo_1));
                    ret.push_back(std::move(sm_foo_2));
                    
                    return ret;
                }
            };

            TEST_F(ApiAssetAdminstrationShell_test, api)
            {
               using namespace basyx::opcua::aas;

               auto aas = AAS();

               ApiAssetAdminstrationShell<Client> api(m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER));

               ASSERT_EQ(UA_STATUSCODE_GOOD, api.createAssetAdministrationShell(*aas.get()));

               auto submodels = SMS();
               // Add submodels to AAS
               ASSERT_EQ(UA_STATUSCODE_GOOD, api.addSubmodel("aas_foo_ident", *submodels[0].get()));
               ASSERT_EQ(UA_STATUSCODE_GOOD, api.addSubmodel("aas_foo_ident", *submodels[1].get()));
          
               auto aasNew = api.getAssetAdministrationShell("aas_foo_ident");
               ASSERT_NE(aasNew, nullptr);
               ASSERT_NE(aasNew->getAdministrativeInformation().getRevision(), nullptr);
               ASSERT_EQ(*aasNew->getAdministrativeInformation().getRevision(), "2");      
               ASSERT_NE(aasNew->getAdministrativeInformation().getVersion(), nullptr);
               ASSERT_EQ(*aasNew->getAdministrativeInformation().getVersion(), "1");           
               ASSERT_EQ(aasNew->getIdShort(), "aas_foo");
               ASSERT_EQ(aasNew->getIdentification().getId(), "aas_foo_ident");
               ASSERT_EQ(aasNew->getIdentification().getIdType(), IdentifierType::Custom);
               // TODO: AssetTest is missing
               // Get submodels
               auto sms = api.getAllSubmodels("aas_foo_ident");
               ASSERT_EQ(sms.size(), 2);               
               for (const auto& sm : sms)
               {
                   if (sm->getIdShort() == "foo_idshort1")
                   {
                       ASSERT_EQ(sm->getIdentification().getId(), "foo_idlong1");
                       ASSERT_EQ(sm->getIdentification().getIdType(), aas::KeyType::Custom);
                       ASSERT_EQ(sm->getKind(), aas::ModelingKind::Instance);
                       ASSERT_EQ(*sm->getAdministrativeInformation().getVersion(), "1");
                       ASSERT_EQ(*sm->getAdministrativeInformation().getRevision(), "0");
                   }
                   if (sm->getIdShort() == "foo_idshort2")
                   {
                       ASSERT_EQ(sm->getIdentification().getId(), "foo_idlong2");
                       ASSERT_EQ(sm->getIdentification().getIdType(), aas::KeyType::Custom);
                       ASSERT_EQ(sm->getKind(), aas::ModelingKind::Instance);
                       ASSERT_EQ(*sm->getAdministrativeInformation().getVersion(), "alpha");
                       ASSERT_EQ(*sm->getAdministrativeInformation().getRevision(), "_0");
                   }
               }
               // Delete Submodels
               ASSERT_EQ(UA_STATUSCODE_GOOD, api.deleteSubmodel("aas_foo_ident", "foo_idshort1"));
               ASSERT_EQ(UA_STATUSCODE_GOOD, api.deleteSubmodel("aas_foo_ident", "foo_idshort2"));
               // Delete AASes
               ASSERT_EQ(UA_STATUSCODE_GOOD, api.deleteAssetAdministrationShell("aas_foo_ident"));

            }
        }
    }
}