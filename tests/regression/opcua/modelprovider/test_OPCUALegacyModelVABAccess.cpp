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
#include <BaSyx/shared/object.h>
#include <string>
#include <cstdint>
#include <thread>
#include <csignal>
#include <chrono>
#include <BaSyx/shared/object.h>
#include <BaSyx/vab/provider/VABModelProvider.h>
#include <BaSyx/opcua/client/Client.h>
#include <BaSyx/opcua/provider/OPCUAModelProvider.h>
#include <BaSyx/opcua/provider/OPCUAModelProviderHelpers.h>
#include <BaSyx/opcua/provider/VAB2OPCUAHandlers.h>
#include <BaSyx/opcua/provider/OPCUA2VabHandlers.h>
#include <BaSyx/opcua/typesmap/TypesMap.h>

#include "buildCNCModel.h"

#include <BaSyx/opcua/server/Server.h>
#include <BaSyx/opcua/client/Client.h>

namespace tests_opcua_model_provider_leg
{

    using namespace basyx::opcua;
    using namespace basyx::aas;
    using namespace basyx::opcua::provider;

    class OPCUAModelProviderLegacyModel : public ::testing::Test
    {
    protected:
        const char* endpoint = "opc.tcp://localhost:4842";
        std::shared_ptr<OPCUAModelProvider<>> providerWithMeta;
        std::shared_ptr<OPCUAModelProvider<>> providerRaw;
        std::unique_ptr<basyx::opcua::Server> m_server;
        std::thread m_serverThread;
    public:
        virtual void SetUp()
        {
            m_server = util::make_unique<basyx::opcua::Server>(4842, shared::Namespaces::BASYX_NS_URI);
            m_server->initialize();
            m_serverThread = std::thread{ [this]() {m_server->run(); } };

            createCNCMachineInstance();

            providerWithMeta = std::make_shared<OPCUAModelProvider<>>(
                endpoint,
                shared::Namespaces::BASYX_NS_URI,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER),
                true
                );

            providerRaw = std::make_shared<OPCUAModelProvider<>>(
                endpoint,
                shared::Namespaces::BASYX_NS_URI,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER),
                false
                );
        }

        virtual void TearDown()
        {
            m_server->abort();
            m_serverThread.join();
        }

        void createCNCMachineInstance();
    };

    TEST_F(OPCUAModelProviderLegacyModel, ModelProviderWithMetaData)
    {
        providerWithMeta->setModelPropertyValue(
            "EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit", TypesTransformer::objectWithMeta<std::string>("Some string value with meta")
        );

        auto val_Engineering_Unit_With_Meta = providerWithMeta->getModelPropertyValue("EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit");
        ASSERT_EQ(TypesTransformer::objectWithMeta<std::string>("Some string value with meta"), val_Engineering_Unit_With_Meta);

    }

    TEST_F(OPCUAModelProviderLegacyModel, ModelProviderWithoutMetaData)
    {
        providerRaw->setModelPropertyValue("EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit", "Some string value without meta");

        auto val_Engineering_Unit_With_Raw = providerRaw->getModelPropertyValue(
            "EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit"
        );
        ASSERT_EQ(basyx::object("Some string value without meta"), val_Engineering_Unit_With_Raw);
    }

    void OPCUAModelProviderLegacyModel::createCNCMachineInstance()
    {
        auto client = util::make_unique<basyx::opcua::Client>(
            endpoint,
            shared::Namespaces::BASYX_NS_URI
            );

        client->connect();
        /* Define types */
        EmcoCNC::defineMachineToolType(client.get());
        EmcoCNC::defineCuttingToolType(client.get());
        EmcoCNC::defineToolVibrationType(client.get());
        EmcoCNC::defineCuttingForceType(client.get());
        /* Create instance */
        EmcoCNC::createEmoCNCInstance(client.get(), NodeId::numeric(UA_NS0ID_OBJECTSFOLDER));
    }
}