/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/controlcomponent/simple/ControlComponent.h>
#include <BaSyx/controlcomponent/enumerations/ControlComponentConstants.h>

namespace basyx {
namespace controlcomponent {
namespace simple {

using constants = basyx::controlcomponent::ControlComponentConstants;
using constants_ = basyx::controlcomponent::ControlComponentConstants_;

ControlComponent::ControlComponent()
  : savedOccupierId {""}
  , occupationState{OccupationState::free}
  , occupier{""}
  , lastOccupier{""}
  , exMode{ExecutionMode::Auto}
  , exState{ExecutionState::idle}
  , opMode{""}
  , workState{""}
  , errorState{""}
  , prevError{""}
  , cmd{""}
  , localOverwrite{""}
  , localOverwriteFree{""}
  , service_operations{object::make_map()}
{
  this->init_service_operations();
}

void ControlComponent::addControlComponentChangeListener(const std::shared_ptr<IControlComponentChangeListener> listener)
{
  this->componentChangeListeners.emplace(listener->getUniqueID(), listener);
}

void ControlComponent::removeControlComponentChangeListener(const std::shared_ptr<IControlComponentChangeListener> listener)
{
  this->componentChangeListeners.erase(listener->getUniqueID());
}

const basyx::object ControlComponent::getServiceOperationMap()
{
  return this->service_operations;
}

void ControlComponent::finishState()
{
  switch (this->getExecutionState())
  {
    case ExecutionState::starting:
    {
      this->setExecutionState(ExecutionState::execute);
      return;
    }
    case ExecutionState::execute:
    {
      this->setExecutionState(ExecutionState::completing);
      return;
    }
    case ExecutionState::completing:
    {
      this->setExecutionState(ExecutionState::complete);
      return;
    }
    case ExecutionState::resetting:
    {
      this->setExecutionState(ExecutionState::idle);
      return;
    }
    case ExecutionState::holding:
    {
      this->setExecutionState(ExecutionState::held);
      return;
    }
    case ExecutionState::unholding:
    {
      this->setExecutionState(ExecutionState::execute);
      return;
    }
    case ExecutionState::suspending:
    {
      this->setExecutionState(ExecutionState::suspended);
      return;
    }
    case ExecutionState::unsuspending:
    {
      this->setExecutionState(ExecutionState::execute);
      return;
    }
    case ExecutionState::stopping:
    {
      this->setExecutionState(ExecutionState::stopped);
      return;
    }
    case ExecutionState::stopped:
    {
      this->setExecutionState(ExecutionState::idle);
      return;
    }
    case ExecutionState::aborting:
    {
      this->setExecutionState(ExecutionState::aborted);
      return;
    }
    case ExecutionState::clearing:
    {
      this->setExecutionState(ExecutionState::stopped);
      return;
    }
  }
}

const std::vector<std::string> & ControlComponent::getOrderList()
{
  return this->orderList;
}

void ControlComponent::addOrder(const std::string &newOrder)
{
  this->orderList.push_back(newOrder);
}

void ControlComponent::clearOrder()
{
  this->orderList.clear();
}

OccupationState ControlComponent::getOccupationState()
{
  return static_cast<OccupationState>(this->occupationState);
}

void ControlComponent::setOccupationState(const OccupationState &occState)
{
  this->occupationState = occState;
  this->notify_change_listeners_on_variable_change(constants::occupationState, (int) occState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onNewOccupationState(occState);
  }
}

std::string ControlComponent::getOccupierID()
{
  return this->occupier;
}

void ControlComponent::setOccupierID(const std::string &occId)
{
  this->occupier = occId;
  this->notify_change_listeners_on_variable_change(constants::occupier, occId);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onNewOccupier(occId);
  }
}

std::string ControlComponent::getLastOccupierID()
{
  return this->lastOccupier;
}

void ControlComponent::setLastOccupierID(const std::string &occId)
{
  this->lastOccupier = occId;
  this->notify_change_listeners_on_variable_change(constants::lastOccupier, occId);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onLastOccupier(occId);
  }
}

ExecutionMode ControlComponent::getExecutionMode()
{
  return this->exMode;
}

void ControlComponent::setExecutionMode(const ExecutionMode &exMode)
{
  this->exMode = exMode;
  this->notify_change_listeners_on_variable_change(constants::exMode, (int) exMode);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedExecutionMode(exMode);
  }
}

ExecutionState ControlComponent::getExecutionState()
{
  return this->exState;
}

void ControlComponent::setExecutionState(const ExecutionState &newSt)
{
  this->exState = newSt;
  this->notify_change_listeners_on_variable_change(constants::exState, ExecutionState_::to_string(newSt));

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedExecutionState(newSt);
  }
}

std::string ControlComponent::getOperationMode()
{
  return this->opMode;
}

void ControlComponent::setOperationMode(const std::string &opMode)
{
  this->opMode = opMode;
  this->notify_change_listeners_on_variable_change(constants::opMode, opMode);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedOperationMode(opMode);
  }
}

std::string ControlComponent::getWorkState()
{
  return this->workState;
}

void ControlComponent::setWorkState(const std::string &workState)
{
  this->workState = workState;
  this->notify_change_listeners_on_variable_change(constants::workState, workState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedWorkState(workState);
  }
}

std::string ControlComponent::getErrorState()
{
  return this->errorState;
}

void ControlComponent::setErrorState(const std::string &errorState)
{
  this->errorState = errorState;
  this->notify_change_listeners_on_variable_change(constants::errorState, errorState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedErrorState(errorState);
  }
}

std::string ControlComponent::getLastErrorState()
{
  return this->prevError;
}

void ControlComponent::setLastErrorState(const std::string &lastErrorState)
{
  this->errorState = lastErrorState;
  this->notify_change_listeners_on_variable_change(constants::errorState, lastErrorState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedPrevError(lastErrorState);
  }
}

std::string ControlComponent::getCommand()
{
  return this->cmd;
}

void ControlComponent::setCommand(const std::string &cmd)
{
  this->cmd = cmd;
}

std::string ControlComponent::getLocalOverwrite()
{
  return this->localOverwrite;
}

void ControlComponent::setLocalOverwrite(const std::string &cmd)
{
  this->localOverwrite = cmd;
}

std::string ControlComponent::getLocalOverwriteFree()
{
  return this->localOverwriteFree;
}

void ControlComponent::setLocalOverwriteFree(const std::string &cmd)
{
  this->localOverwriteFree = cmd;
}

void ControlComponent::changeExecutionState(const ExecutionOrder &ex_order)
{
  // Check if execution order leads to valid state in current state
  switch (this->getExecutionState())
  {
    case ExecutionState::idle:
      // Process expected orders
      if (ex_order == ExecutionOrder::start)
      {
        this->setExecutionState(ExecutionState::starting);
        return;
      }
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::starting:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::execute:
      // Process expected orders
      if (ex_order == ExecutionOrder::complete)
      {
        this->setExecutionState(ExecutionState::completing);
        return;
      }
      if (ex_order == ExecutionOrder::hold)
      {
        this->setExecutionState(ExecutionState::holding);
        return;
      }
      if (ex_order == ExecutionOrder::suspend)
      {
        this->setExecutionState(ExecutionState::suspending);
        return;
      }
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::completing:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::complete:
      if (ex_order == ExecutionOrder::reset)
      {
        this->setExecutionState(ExecutionState::resetting);
        return;
      }
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::resetting:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::holding:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::held:
      if (ex_order == ExecutionOrder::unhold)
      {
        this->setExecutionState(ExecutionState::unholding);
        return;
      }
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::unholding:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::suspending:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::suspended:
      if (ex_order == ExecutionOrder::unsuspend)
      {
        this->setExecutionState(ExecutionState::unsuspending);
        return;
      }
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::unsuspending:
      if (ex_order == ExecutionOrder::stop)
      {
        this->setExecutionState(ExecutionState::stopping);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::stopping:
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }

    case ExecutionState::stopped:
      if (ex_order == ExecutionOrder::reset)
      {
        this->setExecutionState(ExecutionState::resetting);
        return;
      }
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }
    case ExecutionState::aborted:
      if (ex_order == ExecutionOrder::clear)
      {
        this->setExecutionState(ExecutionState::clearing);
        return;
      }

    case ExecutionState::clearing:
      if (ex_order == ExecutionOrder::abort)
      {
        this->setExecutionState(ExecutionState::aborting);
        return;
      }
  }

}

void ControlComponent::invokeLocalOverwrite()
{
  // Store current occupier because we need to restore it later
  this->savedOccupierId = this->getOccupierID();

  // Enter local overwrite state
  this->setOccupationState(OccupationState::local);
  this->setOccupierID(constants_::to_string(constants::LOCAL));
}

void ControlComponent::clearLocalOverwrite()
{
  this->setOccupierID(this->savedOccupierId);

  // Restore occupier state based on variables
  if (this->savedOccupierId.empty())
    this->setOccupationState(OccupationState::free);
  else if (this->getLastOccupierID().empty())
    this->setOccupationState(OccupationState::occupied);
  else
    this->setOccupationState(OccupationState::priority);
}

template<typename T> void ControlComponent::notify_change_listeners_on_variable_change(const ControlComponentConstants &status_key, T status)
{
  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onVariableChange(constants_::to_string(status_key), status);
  }
}

void ControlComponent::init_service_operations()
{
  // All lambdas returning bool since this is supported by vab
  this->service_operations.insertKey(constants_::to_string(constants::free), object::make_function([this](std::string senderId) {
    this->freeControlComponent(senderId);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::occupy), object::make_function([this](std::string occupier) {
    this->occupyControlComponent(occupier);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::priority), object::make_function([this](std::string occupier) {
    this->priorityOccupation(occupier);
    return true;
  }));

  this->service_operations.insertKey(constants_::to_string(constants::Auto), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Auto);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::semiauto), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Semiauto);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::manual), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Manual);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::simulation), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Simulation);
    return true;
  }));

  this->service_operations.insertKey(constants_::to_string(constants::start), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::start);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::reset), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::reset);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::hold), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::hold);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::unhold), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::unhold);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::suspend), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::suspend);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::unsuspend), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::unsuspend);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::abort), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::abort);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::stop), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::stop);
    return true;
  }));
  this->service_operations.insertKey(constants_::to_string(constants::clear), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::clear);
    return true;
  }));

  this->service_operations.insertKey(constants_::to_string(constants::bstate), object::make_function([this]() {
    this->setOperationMode(std::string {"BSTATE"});
    return true;
  }));
}

void ControlComponent::freeControlComponent(const std::string &senderId)
{
  if (this->getOccupierID().compare(senderId) == 0)
  {
    this->setOccupierID(this->getLastOccupierID());
    this->setLastOccupierID("");
    if (this->getOccupierID().empty())
      this->setOccupationState(OccupationState::free);
    else
      this->setOccupationState(OccupationState::occupied);
  }
}

void ControlComponent::occupyControlComponent(const std::string &occupier)
{
  if (this->getOccupationState() == OccupationState::free)
  {
    this->setOccupierID(occupier);
    this->setOccupationState(OccupationState::occupied);
  }
}

void ControlComponent::priorityOccupation(const std::string &occupier)
{
  if ((this->getOccupationState() == OccupationState::free) or (this->getOccupationState() == OccupationState::occupied))
  {
    this->setLastOccupierID(this->getOccupierID());
    this->setOccupierID(occupier);
    this->setOccupationState(OccupationState::priority);
  }
}

}
}
}
