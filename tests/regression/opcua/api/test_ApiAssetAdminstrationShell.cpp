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

namespace tests_opcua_aas_api
{

    using namespace basyx::opcua;
    using namespace basyx::aas;
    using namespace test_opcua_setup;

    class ApiAssetAdminstrationShell_test : public ::testing::Test
    {
    protected:
        std::unique_ptr<OPCUATestSetup> m_opcuaSetup;
        std::unique_ptr<basyx::opcua::aas::ApiAssetAdminstrationShell<Client>> api;
        std::thread m_serverThread;
        std::unique_ptr<map::AssetAdministrationShell> aas = AAS();
        std::vector<std::unique_ptr<map::Submodel>> submodels = SMS();
    public:
        virtual void SetUp()
        {
            m_opcuaSetup = util::make_unique<OPCUATestSetup>();
            m_serverThread = std::thread{ [this]() {m_opcuaSetup->getServer().run(); } };

            auto nsIdx = m_opcuaSetup->getServer().getNamespaceIndex(shared::Namespaces::BASYX_NS_URI);
            aas::metamodel::AASMetamodel::define(nsIdx, m_opcuaSetup->getServer());

            m_opcuaSetup->getClient().connect();

            api = util::make_unique<basyx::opcua::aas::ApiAssetAdminstrationShell<Client>>
                (m_opcuaSetup->getClient(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER));
        }

        virtual void TearDown()
        {
            m_opcuaSetup->getClient().disconnect();
            m_opcuaSetup->getServer().abort();
            m_serverThread.join();
        }

        std::unique_ptr<map::AssetAdministrationShell> AAS();
        std::vector<std::unique_ptr<map::Submodel>> SMS();
    };

    TEST_F(ApiAssetAdminstrationShell_test, submodelAttributes)
    {
        using namespace basyx::opcua::aas;

        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createAssetAdministrationShell(*aas.get()));
        // Add submodels to AAS
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->addSubmodel("aas_foo_ident", *submodels[0].get()));
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->addSubmodel("aas_foo_ident", *submodels[1].get()));
        auto aasNew = api->getAssetAdministrationShell("aas_foo_ident");
        ASSERT_NE(aasNew, nullptr);
        ASSERT_NE(aasNew->getAdministrativeInformation().getRevision(), nullptr);
        ASSERT_EQ(*aasNew->getAdministrativeInformation().getRevision(), "2");
        ASSERT_NE(aasNew->getAdministrativeInformation().getVersion(), nullptr);
        ASSERT_EQ(*aasNew->getAdministrativeInformation().getVersion(), "1");
        ASSERT_EQ(aasNew->getIdShort(), "aas_foo");
        ASSERT_EQ(aasNew->getIdentification().getId(), "aas_foo_ident");
        ASSERT_EQ(aasNew->getIdentification().getIdType(), IdentifierType::Custom);
        // TODO: AssetTest is missing
    }

    TEST_F(ApiAssetAdminstrationShell_test, getAllSubmodels)
    {
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createAssetAdministrationShell(*aas.get()));
        // Add submodels to AAS
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->addSubmodel("aas_foo_ident", *submodels[0].get()));
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->addSubmodel("aas_foo_ident", *submodels[1].get()));
        auto sms = api->getAllSubmodels("aas_foo_ident");
        ASSERT_EQ(sms.size(), 2);
        auto sm_1 = std::move(sms[0]);
        auto sm_2 = std::move(sms[1]);
        ASSERT_EQ(sm_1->getIdentification().getId(), "foo_idlong1");
        ASSERT_EQ(sm_1->getIdentification().getIdType(), KeyType::Custom);
        ASSERT_EQ(sm_1->getKind(), ModelingKind::Instance);
        ASSERT_EQ(*sm_1->getAdministrativeInformation().getVersion(), "1");
        ASSERT_EQ(*sm_1->getAdministrativeInformation().getRevision(), "0");
        ASSERT_EQ(sm_2->getIdentification().getId(), "foo_idlong2");
        ASSERT_EQ(sm_2->getIdentification().getIdType(), KeyType::Custom);
        ASSERT_EQ(sm_2->getKind(), ModelingKind::Instance);
    }

    TEST_F(ApiAssetAdminstrationShell_test, deleteSubmodels)
    {
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->createAssetAdministrationShell(*aas.get()));
        // Add submodels to AAS
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->addSubmodel("aas_foo_ident", *submodels[0].get()));
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->addSubmodel("aas_foo_ident", *submodels[1].get()));
        // Delete Submodels
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteSubmodel("aas_foo_ident", "foo_idshort1"));
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteSubmodel("aas_foo_ident", "foo_idshort2"));
        // Delete AASes
        ASSERT_EQ(UA_STATUSCODE_GOOD, api->deleteAssetAdministrationShell("aas_foo_ident"));
    }

    /* Build a simple minimal AAS  */
    std::unique_ptr<map::AssetAdministrationShell> ApiAssetAdminstrationShell_test::AAS()
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
    std::vector<std::unique_ptr<map::Submodel>> ApiAssetAdminstrationShell_test::SMS()
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
}