/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/controlcomponent/map/ControlComponent.h>
#include <BaSyx/controlcomponent/enumerations/ControlComponentConstants.h>

namespace basyx {
namespace controlcomponent {
namespace map {

using constants = basyx::controlcomponent::ControlComponentConstants;
using constants_ = basyx::controlcomponent::ControlComponentConstants_;

ControlComponent::ControlComponent()
  : vab::ElementMap {}, savedOccupierId {""}, status_map {object::make_map()}, operations {object::make_map()}
{
  this->map.insertKey(constants_::to_string(constants::orderList), std::vector<std::string>{});

  //initialize status map
  this->map.insertKey(constants_::to_string(constants::status), this->status_map);
  this->insert_status(constants::occupationState, (int) OccupationState::free);
  this->insert_status(constants::occupier, "");
  this->insert_status(constants::lastOccupier, "");
  this->insert_status(constants::exMode, (int) ExecutionMode::Auto);
  this->insert_status(constants::exState, ExecutionState_::to_string(ExecutionState::idle));
  this->insert_status(constants::opMode, "");
  this->insert_status(constants::workState, "");
  this->insert_status(constants::errorState, "");
  this->insert_status(constants::prevError, "");

  //initialize input signals
  this->map.insertKey(constants_::to_string(constants::cmd), "");
  this->map.insertKey(constants_::to_string(constants::localOverwrite), "");
  this->map.insertKey(constants_::to_string(constants::localOverwriteFree), "");

  // Add operations map
  this->map.insertKey(constants_::to_string(constants::operations), this->operations);
  this->operations.insertKey(constants_::to_string(constants::service), init_service_operations());
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
  return this->map.getProperty(constants_::to_string(constants::operations)).getProperty(constants_::to_string(constants::service));
}

void ControlComponent::put(const std::string &key, object value)
{
  this->map.insertKey(key, value);

  // Indicate value change
  for (auto listener : componentChangeListeners)
  {
    listener.second->onVariableChange(key, value);
  }

  // Process variable changes
  switch (constants_::from_string(key))
  {
    case constants::cmd:
    {
      this->changeExecutionState(ExecutionOrder_::from_string(value.Get<std::string>()));
      break;
    }
    case constants::localOverwrite:
    {
      this->invokeLocalOverwrite();
      break;
    }
    case constants::localOverwriteFree:
    {
      this->clearLocalOverwrite();
      break;
    }
  }
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
  return *this->map.getProperty(constants_::to_string(constants::orderList)).GetPtr<std::vector<std::string>>();
}

void ControlComponent::addOrder(const std::string &newOrder)
{
  this->map.getProperty(constants_::to_string(constants::orderList)).GetPtr<std::vector<std::string>>()->push_back(newOrder);
}

void ControlComponent::clearOrder()
{
  this->map.getProperty(constants_::to_string(constants::orderList)).GetPtr<object::list_t<std::string>>()->clear();
}

OccupationState ControlComponent::getOccupationState()
{
  return static_cast<OccupationState>(this->status_map.getProperty(constants_::to_string(constants::occupationState)).Get<int>());
}

void ControlComponent::setOccupationState(const OccupationState &occState)
{
  this->insert_status(constants::occupationState, (int) occState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onNewOccupationState(occState);
  }
}

std::string ControlComponent::getOccupierID()
{
  return this->get_status<std::string>(constants::occupier);
}

void ControlComponent::setOccupierID(const std::string &occId)
{
  this->insert_status(constants::occupier, occId);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onNewOccupier(occId);
  }
}

std::string ControlComponent::getLastOccupierID()
{
  return this->get_status<std::string>(constants::lastOccupier);
}

void ControlComponent::setLastOccupierID(const std::string &occId)
{
  this->insert_status(constants::lastOccupier, occId);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onLastOccupier(occId);
  }
}

ExecutionMode ControlComponent::getExecutionMode()
{
  return (ExecutionMode) this->get_status<int>(constants::exMode);
}

void ControlComponent::setExecutionMode(const ExecutionMode &exMode)
{
  this->insert_status(constants::exMode, (int) exMode);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedExecutionMode(exMode);
  }
}

ExecutionState ControlComponent::getExecutionState()
{
  return ExecutionState_::from_string(this->get_status<std::string>(constants::exState));
}

void ControlComponent::setExecutionState(const ExecutionState &newSt)
{
  this->insert_status(constants::exState, ExecutionState_::to_string(newSt));

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedExecutionState(newSt);
  }
}

std::string ControlComponent::getOperationMode()
{
  return this->get_status<std::string>(constants::opMode);
}

void ControlComponent::setOperationMode(const std::string &opMode)
{
  this->insert_status(constants::opMode, opMode);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedOperationMode(opMode);
  }
}

std::string ControlComponent::getWorkState()
{
  return this->get_status<std::string>(constants::workState);
}

void ControlComponent::setWorkState(const std::string &workState)
{
  this->insert_status(constants::workState, workState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedWorkState(workState);
  }
}

std::string ControlComponent::getErrorState()
{
  return this->get_status<std::string>(constants::errorState);
}

void ControlComponent::setErrorState(const std::string &errorState)
{
  this->insert_status(constants::errorState, errorState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedErrorState(errorState);
  }
}

std::string ControlComponent::getLastErrorState()
{
  return this->get_status<std::string>(constants::prevError);
}

void ControlComponent::setLastErrorState(const std::string &lastErrorState)
{
  this->insert_status(constants::errorState, lastErrorState);

  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onChangedPrevError(lastErrorState);
  }
}

std::string ControlComponent::getCommand()
{
  return this->map.getProperty(constants_::to_string(constants::cmd)).GetStringContent();
}

void ControlComponent::setCommand(const std::string &cmd)
{
  this->map.insertKey(constants_::to_string(constants::cmd), cmd);
}

std::string ControlComponent::getLocalOverwrite()
{
  return this->map.getProperty(constants_::to_string(constants::localOverwrite)).GetStringContent();
}

void ControlComponent::setLocalOverwrite(const std::string &cmd)
{
  this->map.insertKey(constants_::to_string(constants::localOverwrite), cmd);
}

std::string ControlComponent::getLocalOverwriteFree()
{
  return this->map.getProperty(constants_::to_string(constants::localOverwriteFree)).GetStringContent();
}

void ControlComponent::setLocalOverwriteFree(const std::string &cmd)
{
  this->map.insertKey(constants_::to_string(constants::localOverwriteFree), cmd);
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

template<typename T> void ControlComponent::insert_status(const ControlComponentConstants &status_key, T status)
{
  this->status_map.insertKey(constants_::to_string(status_key), status);
  for (auto listener : this->componentChangeListeners)
  {
    listener.second->onVariableChange(constants_::to_string(status_key), status);
  }
}

template<typename T> T ControlComponent::get_status(const basyx::controlcomponent::ControlComponentConstants &key)
{
  return this->status_map.getProperty(constants_::to_string(key)).Get<T>();
}

object ControlComponent::init_service_operations()
{
  object map = object::make_map();

  // All lambdas returning bool since this is supported by vab
  map.insertKey(constants_::to_string(constants::free), object::make_function([this](std::string senderId) {
    this->freeControlComponent(senderId);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::occupy), object::make_function([this](std::string occupier) {
    this->occupyControlComponent(occupier);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::priority), object::make_function([this](std::string occupier) {
    this->priorityOccupation(occupier);
    return true;
  }));

  map.insertKey(constants_::to_string(constants::Auto), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Auto);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::semiauto), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Semiauto);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::manual), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Manual);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::simulation), object::make_function([this]() {
    this->setExecutionMode(ExecutionMode::Simulation);
    return true;
  }));

  map.insertKey(constants_::to_string(constants::start), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::start);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::reset), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::reset);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::hold), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::hold);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::unhold), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::unhold);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::suspend), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::suspend);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::unsuspend), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::unsuspend);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::abort), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::abort);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::stop), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::stop);
    return true;
  }));
  map.insertKey(constants_::to_string(constants::clear), object::make_function([this]() {
    this->changeExecutionState(ExecutionOrder::clear);
    return true;
  }));

  map.insertKey(constants_::to_string(constants::bstate), object::make_function([this]() {
    this->setOperationMode(std::string {"BSTATE"});
    return true;
  }));

  return map;
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
