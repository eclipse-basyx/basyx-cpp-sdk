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

    void createCNCMachineInstance();

    class OPCUAModelProviderLegacyModel : public ::testing::Test
    {
    public:
        std::shared_ptr<OPCUAModelProvider<>> providerWithMeta;
        std::shared_ptr<OPCUAModelProvider<>> providerRaw;

        std::unique_ptr<basyx::opcua::Server> server;
    public:

        virtual void SetUp() {

            server = util::make_unique<basyx::opcua::Server>(5010, shared::Namespaces::BASYX_NS_URI);

            server->initialize();
            server->runInBackground();

            while (!server->isServerUp());

            createCNCMachineInstance();

            providerWithMeta = std::make_shared<OPCUAModelProvider<>>(
                "opc.tcp://localhost:5010",
                shared::Namespaces::BASYX_NS_URI,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER),
                true
                );

            providerRaw = std::make_shared<OPCUAModelProvider<>>(
                "opc.tcp://localhost:5010",
                shared::Namespaces::BASYX_NS_URI,
                NodeId::numeric(UA_NS0ID_OBJECTSFOLDER),
                false
                );
        }

        virtual void TearDown()
        {
            server->abort();
        }
    };

    TEST_F(OPCUAModelProviderLegacyModel, ModelProviderLegacyModels)
    {

        providerWithMeta->setModelPropertyValue(
            "EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit", TypesTransformer::objectWithMeta<std::string>("Some string value with meta")
        );

        auto val_Engineering_Unit_With_Meta = providerWithMeta->getModelPropertyValue("EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit");

        ASSERT_EQ(TypesTransformer::objectWithMeta<std::string>("Some string value with meta"), val_Engineering_Unit_With_Meta);

        providerRaw->setModelPropertyValue("EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit", "Some string value without meta");

        auto val_Engineering_Unit_With_Raw = providerRaw->getModelPropertyValue(
            "EmcoCNC/CuttingTool/CuttingForces/Force_X/Engineering_Unit"
        );

        ASSERT_EQ(basyx::object("Some string value without meta"), val_Engineering_Unit_With_Raw);
    }


    void createCNCMachineInstance()
    {
        auto client = util::make_unique<basyx::opcua::Client>(
            "opc.tcp://localhost:5010",
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