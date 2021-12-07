/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <gtest/gtest.h>

#include <BaSyx/vab/provider/hashmap/VABHashmapProvider.h>
#include <BaSyx/vab/provider/hashmap/VABHashmapProvider.h>
#include <BaSyx/vab/backend/connector/native/BaSyxConnector.h>
#include <BaSyx/server/TCPServer.h>

#include <vab/stub/elements/SimpleVABElement.h>

#include "snippet/MapRead.h"
#include "snippet/MapCreateDelete.h"
#include "snippet/MapUpdate.h"
#include "snippet/MapInvoke.h"
#include "snippet/TestCollectionProperty.h"

#include <BaSyx/shared/serialization/json.h>

#include <atomic>
#include <memory>
#include <unordered_map>
#include <vector>
#include <thread>

using namespace basyx;

class ConnectedModelProvider;

class TestBaSyxNative : public ::testing::Test {
	using TcpServer_t = server::TCPServer<vab::provider::VABModelProvider>;
public:
	static constexpr int port = 7002;
	std::thread server_thread;

	std::unique_ptr<vab::provider::VABModelProvider> provider;
	std::unique_ptr<TcpServer_t> tcpServer;

	std::unique_ptr<vab::connector::native::NativeConnector> clientConnector;
	std::unique_ptr<ConnectedModelProvider> clientProvider;

	std::atomic<bool> done;

	TestBaSyxNative() 
	{
	};

	virtual void SetUp()
	{
		done.store(false);

		provider = util::make_unique<vab::provider::VABModelProvider>(tests::support::make_simple_vab_element());
		tcpServer = util::make_unique<TcpServer_t>(provider.get(), port);

		server_thread = std::thread{ [this]() {
					tcpServer->run();
			}
		};

		// Wait until server started up
		std::this_thread::sleep_for(std::chrono::seconds(1));

		clientConnector = util::make_unique<vab::connector::native::NativeConnector>();
		clientConnector->connect("127.0.0.1", port);

		clientProvider = util::make_unique<ConnectedModelProvider>(clientConnector.get());
	}

	virtual void TearDown()
	{
		tcpServer->Close();
		server_thread.join();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
};

class ConnectedModelProvider : public vab::core::IModelProvider
{
public:
	using Connector = vab::connector::IBaSyxConnector;
	Connector * connector;
public:
	ConnectedModelProvider(Connector * connector) : connector(connector)
	{};

	// Inherited via IModelProvider
	virtual basyx::object getModelPropertyValue(const std::string & path) override
	{
		return connector->basysGet(path);
	}

	virtual basyx::object::error  setModelPropertyValue(const std::string & path, const basyx::object newValue) override
	{
		auto obj = connector->basysSet(path, newValue);
		return obj.getError();
	}

	virtual basyx::object::error createValue(const std::string & path, const basyx::object addedValue) override
	{
		auto obj = connector->basysCreate(path, addedValue);
		return obj.getError();
	}

	virtual basyx::object::error deleteValue(const std::string & path, basyx::object deletedValue) override
	{
		auto obj = connector->basysDelete(path, deletedValue);
		return obj.getError();
	}

	virtual basyx::object::error deleteValue(const std::string & path) override
	{
		auto obj = connector->basysDelete(path);
		return obj.getError();
	}
	virtual basyx::object invokeOperation(const std::string & path, basyx::object parameter) override
	{
		return connector->basysInvoke(path, parameter);
	}
};

TEST_F(TestBaSyxNative, MapRead)
{
	tests::regression::vab::snippet::MapRead::test(clientProvider.get());
}

TEST_F(TestBaSyxNative, MapUpdate)
{
	tests::regression::vab::snippet::MapUpdate::test(clientProvider.get());
}

TEST_F(TestBaSyxNative, MapCreateDelete)
{
	tests::regression::vab::snippet::MapCreateDelete::test(clientProvider.get());
}

TEST_F(TestBaSyxNative, MapInvoke)
{
	tests::regression::vab::snippet::MapInvoke::test(clientProvider.get());
}

TEST_F(TestBaSyxNative, TestCollectionProperty)
{
	tests::regression::vab::snippet::TestCollectionProperty::test(clientProvider.get());
}

int constexpr TestBaSyxNative::port;