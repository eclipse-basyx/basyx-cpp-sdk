/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

/*
 * test_TCPSelectServer.h
 *
 * Testing of TCPSelectServer, similar to tests in Test_VABBasyxTCP, the whole loop with
 * NativeProvider is tested.
 * 
 *      Author: wendel
 */

#include <gtest/gtest.h>

#include <BaSyx/server/TCPSelectServer.h>
#include <support/MockupModelProvider.h>
#include <BaSyx/abstraction/Thread.h>
#include <BaSyx/vab/backend/connector/native/BaSyxConnector.h>

using namespace basyx::vab::provider::native;

class TCPSelectServerTest : public ::testing::Test
{
protected:
  const int port = 8989;
  std::atomic<bool> running;

  MockupModelProvider* provider;
  TCPSelectServer* server;
  vab::connector::native::NativeConnector * connector;

  basyx::thread thread;

  virtual void SetUp()
  {
    provider = new MockupModelProvider();
    server = new TCPSelectServer(provider, port, 100);
    server->Init();

    connector = new vab::connector::native::NativeConnector("127.0.0.1", port);

    running = true;
    thread = basyx::thread([&](){while(running.load()){server->Update();}});
  }

  virtual void TearDown()
  {
    delete(connector);
    running.store(false);
    server->Close();
    thread.join();

    delete(provider);
    delete(server);
  }

};

TEST_F(TCPSelectServerTest, getTest)
{
  std::string path = "TestPath";
  basyx::object val = connector->basysGet(path);

  // Check if correct call occured
  ASSERT_EQ(provider->called, MockupModelProvider::CalledFunction::GET);
  ASSERT_EQ(provider->path, path);

  // Check return value
  ASSERT_TRUE(val.InstanceOf<int>());
  ASSERT_EQ(val.Get<int>(), 2);
}

TEST_F(TCPSelectServerTest, setTest)
{
  std::string path = "TestPath";
  basyx::object val = 10;
  connector->basysSet(path, val);

  while (provider->called != MockupModelProvider::CalledFunction::SET);

  // Check if correct call occured
  ASSERT_EQ(provider->called, MockupModelProvider::CalledFunction::SET);
  ASSERT_EQ(provider->path, path);
}

TEST_F(TCPSelectServerTest, createTest)
{
  std::string path = "TestPath";
  basyx::object val = 10;
  connector->basysCreate(path, val);

  // Check if correct call occured
  ASSERT_EQ(provider->called, MockupModelProvider::CalledFunction::CREATE);
  ASSERT_EQ(provider->path, path);
  ASSERT_TRUE(provider->val.InstanceOf<int>());
  ASSERT_EQ(provider->val.Get<int>(), 10);
}

TEST_F(TCPSelectServerTest, deleteSimpleTest)
{
  std::string path = "TestPath";
  connector->basysDelete(path);

  // Check if correct call occured
  ASSERT_EQ(provider->called, MockupModelProvider::CalledFunction::DELETE_SIMPLE);
  ASSERT_EQ(provider->path, path);
}

TEST_F(TCPSelectServerTest, deleteComplexTest)
{
  std::string path = "TestPath";
  basyx::object val = 10;
  connector->basysDelete(path, val);

  // Check if correct call occured
  ASSERT_EQ(provider->called, MockupModelProvider::CalledFunction::DELETE_COMPLEX);
  ASSERT_EQ(provider->path, path);
  ASSERT_TRUE(provider->val.InstanceOf<int>());
  ASSERT_EQ(provider->val.Get<int>(), 10);
}
