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

#include <BaSyx/controlcomponent/map/ControlComponent.h>
#include <BaSyx/controlcomponent/enumerations/ExecutionOrder.h>
#include <BaSyx/controlcomponent/simple/ControlComponent.h>
#include "support/ControlComponentChangeListenerMock.hpp"

using namespace basyx::controlcomponent;

using ImplTypes = ::testing::Types<
  simple::ControlComponent,
  map::ControlComponent
>;

template<class Impl>
class ControlComponentTest: public ::testing::Test{
protected:
	std::unique_ptr<IControlComponent> control_component;
	std::shared_ptr<ControlComponentChangeListenerMock> change_listener, change_listener_2;
protected:
	void SetUp() override
	{
	  this->control_component = util::make_unique<Impl>();
	    this->change_listener = std::make_shared<ControlComponentChangeListenerMock>();
      this->change_listener_2 = std::make_shared<ControlComponentChangeListenerMock>(2);

	  this->control_component->addControlComponentChangeListener(change_listener);
    this->control_component->addControlComponentChangeListener(change_listener_2);
	}

	void TearDown() override
	{
	}
};

TYPED_TEST_CASE(ControlComponentTest, ImplTypes);

TYPED_TEST(ControlComponentTest, TestListener)
{
  this->control_component->removeControlComponentChangeListener(this->change_listener);
  // getUniqueID should have been called twice (see SetUp() above)
  ASSERT_EQ(2, this->change_listener->call_counter_getUniqueID);

  //only teh second change listener should have been notified
  this->control_component->setLastOccupierID("");
  ASSERT_EQ(0, this->change_listener->call_counter_onLastOccupier);
  ASSERT_EQ(1, this->change_listener_2->call_counter_onLastOccupier);
}

TYPED_TEST(ControlComponentTest, TestAddClearOrder)
{
  //intially the list should be empty
  const std::vector<std::string> & list = this->control_component->getOrderList();
  ASSERT_EQ(list.size(), 0);

  //add some orders
  this->control_component->addOrder("order_1");
  this->control_component->addOrder("order_2");

  //check if they are in list
  ASSERT_EQ(list.size(), 2);

  //clear list
  this->control_component->clearOrder();
  ASSERT_EQ(list.size(), 0);
}

/*TEST_F(MapTest, TestPut)
{
  this->control_component->addControlComponentChangeListener(this->change_listener_2);

  this->control_component->put("key", "test");
  //key value pair should be in map
  ASSERT_EQ("test", this->control_component->getMap().getProperty("key").GetStringContent());
  //changeListeners onVariableChange should be called for each put
  ASSERT_EQ(1, this->change_listener->call_counter_onVariableChange);
  ASSERT_EQ(1, this->change_listener_2->call_counter_onVariableChange);
  this->change_listener->reset();
  this->change_listener_2->reset();

  //If key cmd and value is a valid ExecutionOrder, ExecutionState should have changed
  this->control_component->put("cmd", ExecutionOrder_::to_string(ExecutionOrder::reset));
  ASSERT_EQ(1, this->change_listener->call_counter_onChangedExecutionState);
  ASSERT_EQ(1, this->change_listener_2->call_counter_onChangedExecutionState);
  ASSERT_EQ(ExecutionState::resetting ,this->control_component->getExecutionState());
    this->change_listener->reset();
    this->change_listener_2->reset();

  //If key is localOverwrite occupier should be local
  this->control_component->put(ControlComponentConstants_::to_string(ControlComponentConstants::localOverwrite), "test");
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupationState);
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(ControlComponentConstants_::to_string(ControlComponentConstants::LOCAL), this->control_component->getOccupierID());
  ASSERT_EQ(OccupationState::local, this->control_component->getOccupationState());

  this->control_component->put(ControlComponentConstants_::to_string(ControlComponentConstants::localOverwriteFree), "test");
  ASSERT_EQ("", this->control_component->getOccupierID());
}*/

TYPED_TEST(ControlComponentTest, TestOccupationState)
{
  OccupationState inital = this->control_component->getOccupationState();
  ASSERT_EQ(OccupationState::free, inital);

  this->control_component->setOccupationState(OccupationState::occupied);
  OccupationState next = this->control_component->getOccupationState();
  ASSERT_EQ(OccupationState::occupied, next);
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupationState);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onNewOccupationState);
}

TYPED_TEST(ControlComponentTest, TestOccupierId)
{
  std::string initial = this->control_component->getOccupierID();
  ASSERT_EQ(initial, "");

  this->control_component->setOccupierID("Some occupier");
  std::string id = this->control_component->getOccupierID();
  ASSERT_EQ("Some occupier", id);
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onNewOccupier);
}

TYPED_TEST(ControlComponentTest, TestLastOccupierId)
{
  std::string initial = this->control_component->getLastOccupierID();
  ASSERT_EQ(initial, "");

  this->control_component->setLastOccupierID("Some last occupier");
  std::string id = this->control_component->getLastOccupierID();
  ASSERT_EQ("Some last occupier", id);
  ASSERT_EQ(1,   this->change_listener->call_counter_onLastOccupier);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onLastOccupier);
}

TYPED_TEST(ControlComponentTest, TestExecutionMode)
{
  ExecutionMode initial = this->control_component->getExecutionMode();
  ASSERT_EQ(initial, ExecutionMode::Auto);

  this->control_component->setExecutionMode(ExecutionMode::Reserved);
  ExecutionMode ex_mode = this->control_component->getExecutionMode();
  ASSERT_EQ(ex_mode, ExecutionMode::Reserved);
  ASSERT_EQ(1,   this->change_listener->call_counter_onChangedExecutionMode);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onChangedExecutionMode);
}

TYPED_TEST(ControlComponentTest, TestExecutionState)
{
  ExecutionState initial = this->control_component->getExecutionState();
  ASSERT_EQ(initial, ExecutionState::idle);

  this->control_component->setExecutionState(ExecutionState::clearing);
  ExecutionState ex_state = this->control_component->getExecutionState();
  ASSERT_EQ(ex_state, ExecutionState::clearing);
  ASSERT_EQ(1,   this->change_listener->call_counter_onChangedExecutionState);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onChangedExecutionState);
}

TYPED_TEST(ControlComponentTest, TestOperationMode)
{
  std::string initial = this->control_component->getOperationMode();
  ASSERT_EQ(initial, "");

  this->control_component->setOperationMode("Special operation");
  std::string op_mode = this->control_component->getOperationMode();
  ASSERT_EQ(op_mode, "Special operation");
  ASSERT_EQ(1,   this->change_listener->call_counter_onChangedOperationMode);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onChangedOperationMode);
}

TYPED_TEST(ControlComponentTest, TestCommand)
{
  std::string initial = this->control_component->getCommand();
  ASSERT_EQ(initial, "");

  this->control_component->setCommand("Some command");
  std::string command = this->control_component->getCommand();
  ASSERT_EQ(command, "Some command");
}

TYPED_TEST(ControlComponentTest, TestLocalOverwrite)
{
  std::string initial = this->control_component->getLocalOverwrite();
  ASSERT_EQ(initial, "");

  this->control_component->setLocalOverwrite("Some overwrite");
  std::string command = this->control_component->getLocalOverwrite();
  ASSERT_EQ(command, "Some overwrite");
}

TYPED_TEST(ControlComponentTest, TestLocalOverwriteFree)
{
  std::string initial = this->control_component->getLocalOverwriteFree();
  ASSERT_EQ(initial, "");

  this->control_component->setLocalOverwriteFree("Some overwrite free");
  std::string command = this->control_component->getLocalOverwriteFree();
  ASSERT_EQ(command, "Some overwrite free");
}

TYPED_TEST(ControlComponentTest, TestServiceMap)
{
  basyx::object service_map = this->control_component->getServiceOperationMap();

  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::semiauto)).invoke();
  ExecutionMode ex_mode = this->control_component->getExecutionMode();
  ASSERT_EQ(ex_mode, ExecutionMode::Semiauto);

  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::start)).invoke();
  ExecutionState ex_state = this->control_component->getExecutionState();
  ASSERT_EQ(ex_state, ExecutionState::starting);

  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::bstate)).invoke();
  std::string op_mode = this->control_component->getOperationMode();
  ASSERT_EQ(op_mode, "BSTATE");
}

TYPED_TEST(ControlComponentTest, TestFreeControlComponent)
{
  basyx::object service_map = this->control_component->getServiceOperationMap();

  //set occupierID and last occupierID
  this->control_component->setOccupierID("It's me");
  this->control_component->setLastOccupierID("It's not anymore me");

  // Try to free the controlcomponent
  basyx::object who("It's me");
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::free)).invoke(who);
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupationState);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onNewOccupationState);

  ASSERT_EQ("It's not anymore me", this->control_component->getOccupierID());
  OccupationState oc_state = this->control_component->getOccupationState();
  ASSERT_EQ(oc_state, OccupationState::occupied);

  // Try to free controlcomponent without permission
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::free)).invoke(who);
  //should not have changed
  ASSERT_EQ("It's not anymore me", this->control_component->getOccupierID());
  ASSERT_EQ(2,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(2,   this->change_listener_2->call_counter_onNewOccupier);

  basyx::object has_permission("It's not anymore me");
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::free)).invoke(has_permission);
  // should be empty now
  ASSERT_EQ("", this->control_component->getOccupierID());
  // ... and free
  oc_state = this->control_component->getOccupationState();
  ASSERT_EQ(oc_state, OccupationState::free);
  ASSERT_EQ(3,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(3,   this->change_listener_2->call_counter_onNewOccupier);
}

TYPED_TEST(ControlComponentTest, TestOccupyControlComponent)
{
  basyx::object service_map = this->control_component->getServiceOperationMap();

  basyx::object who("me");
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::occupy)).invoke(who);

  // should be occupied by "me"
  ASSERT_EQ(who.GetStringContent(), this->control_component->getOccupierID());
  ASSERT_EQ(OccupationState::occupied, this->control_component->getOccupationState());
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupationState);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onNewOccupationState);

  //If occupied, no one else should be able to occupy component
  basyx::object not_permitted("Someone else");
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::occupy)).invoke();
  ASSERT_EQ(who.GetStringContent(), this->control_component->getOccupierID());
  ASSERT_EQ(OccupationState::occupied, this->control_component->getOccupationState());
  ASSERT_EQ(1,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(1,   this->change_listener_2->call_counter_onNewOccupier);
}

TYPED_TEST(ControlComponentTest, TestPriorityOccupation)
{
  basyx::object service_map = this->control_component->getServiceOperationMap();

  basyx::object who("me");
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::occupy)).invoke(who);
  basyx::object priority_occupier("priority");
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::priority)).invoke(priority_occupier);

  //Component should be in prioirity mode, last occupier "me" and actual occupier "priority"
  ASSERT_EQ(OccupationState::priority, this->control_component->getOccupationState());
  ASSERT_EQ("me", this->control_component->getLastOccupierID());
  ASSERT_EQ("priority", this->control_component->getOccupierID());
  ASSERT_EQ(2,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(2,   this->change_listener_2->call_counter_onNewOccupier);

  //"me" should not be able to free component
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::free)).invoke(who);
  ASSERT_EQ("priority", this->control_component->getOccupierID());
  ASSERT_EQ(2,   this->change_listener->call_counter_onNewOccupationState);
  ASSERT_EQ(2,   this->change_listener_2->call_counter_onNewOccupationState);

  //but "prioirity" should be
  service_map.getProperty(ControlComponentConstants_::to_string(ControlComponentConstants::free)).invoke(priority_occupier);
  ASSERT_EQ("me", this->control_component->getOccupierID());
  ASSERT_EQ(OccupationState::occupied, this->control_component->getOccupationState());
  ASSERT_EQ(3,   this->change_listener->call_counter_onNewOccupier);
  ASSERT_EQ(3,   this->change_listener_2->call_counter_onNewOccupier);
}

TYPED_TEST(ControlComponentTest, TestFinishState)
{
  // test transitions according to packml state machine
  this->control_component->setExecutionState(ExecutionState::starting);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::execute, this->control_component->getExecutionState());
  ASSERT_EQ(2,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::execute);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::completing, this->control_component->getExecutionState());
  ASSERT_EQ(4,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::completing);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::complete, this->control_component->getExecutionState());
  ASSERT_EQ(6,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::resetting);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::idle, this->control_component->getExecutionState());
  ASSERT_EQ(8,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::holding);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::held, this->control_component->getExecutionState());
  ASSERT_EQ(10,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::unholding);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::execute, this->control_component->getExecutionState());
  ASSERT_EQ(12,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::suspending);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::suspended, this->control_component->getExecutionState());
  ASSERT_EQ(14,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::unsuspending);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::execute, this->control_component->getExecutionState());
  ASSERT_EQ(16,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::stopping);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::stopped, this->control_component->getExecutionState());
  ASSERT_EQ(18,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::stopped);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::idle, this->control_component->getExecutionState());
  ASSERT_EQ(20,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::aborting);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::aborted, this->control_component->getExecutionState());
  ASSERT_EQ(22,   this->change_listener->call_counter_onChangedExecutionState);

  this->control_component->setExecutionState(ExecutionState::clearing);
  this->control_component->finishState();
  ASSERT_EQ(ExecutionState::stopped, this->control_component->getExecutionState());
  ASSERT_EQ(24,   this->change_listener->call_counter_onChangedExecutionState);
}