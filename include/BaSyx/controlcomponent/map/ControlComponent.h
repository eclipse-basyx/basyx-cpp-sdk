/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_CONTROLCOMPONENT_MAP_CONTROLCOMPONENT_H
#define BASYX_CONTROLCOMPONENT_MAP_CONTROLCOMPONENT_H

#include <BaSyx/controlcomponent/interfaces/IControlComponent.h>

#include <BaSyx/vab/ElementMap.h>
#include <BaSyx/controlcomponent/enumerations/ControlComponentConstants.h>
#include <BaSyx/controlcomponent/enumerations/ExecutionOrder.h>

namespace basyx {
namespace controlcomponent {
namespace map {

class ControlComponent : public IControlComponent, public vab::ElementMap
{
private:
  std::map<int, std::shared_ptr<IControlComponentChangeListener>> componentChangeListeners;
  std::string savedOccupierId;
  basyx::object status_map, operations;

public:
  ControlComponent();

  virtual void addControlComponentChangeListener(const std::shared_ptr<IControlComponentChangeListener> listener) override;

  virtual void removeControlComponentChangeListener(const std::shared_ptr<IControlComponentChangeListener> listener) override;

  const basyx::object getServiceOperationMap();

  void put(const std::string &key, basyx::object value);

  virtual void finishState() override;

  virtual const std::vector<std::string> & getOrderList() override;

  virtual void addOrder(const std::string &newOrder) override;

  virtual void clearOrder() override;

  virtual OccupationState getOccupationState() override;

  virtual void setOccupationState(const OccupationState &occState) override;

  virtual std::string getOccupierID() override;

  virtual void setOccupierID(const std::string &occId) override;

  virtual std::string getLastOccupierID() override;

  virtual void setLastOccupierID(const std::string &occId) override;

  virtual ExecutionMode getExecutionMode() override;

  virtual void setExecutionMode(const ExecutionMode &exMode) override;

  virtual ExecutionState getExecutionState() override;

  virtual void setExecutionState(const ExecutionState &newSt) override;

  virtual std::string getOperationMode() override;

  virtual void setOperationMode(const std::string &opMode) override;

  virtual std::string getWorkState() override;

  virtual void setWorkState(const std::string &workState) override;

  virtual std::string getErrorState() override;

  virtual void setErrorState(const std::string &errorState) override;

  virtual std::string getLastErrorState() override;

  virtual void setLastErrorState(const std::string &lastErrorState) override;

  virtual std::string getCommand() override;

  virtual void setCommand(const std::string &cmd) override;

  virtual std::string getLocalOverwrite() override;

  virtual void setLocalOverwrite(const std::string &cmd) override;

  virtual std::string getLocalOverwriteFree() override;

  virtual void setLocalOverwriteFree(const std::string &cmd) override;

private:
  void changeExecutionState(const ExecutionOrder &);

  void invokeLocalOverwrite();

  void clearLocalOverwrite();

  void freeControlComponent(const std::string &);

  void occupyControlComponent(const std::string &occupier);

  void priorityOccupation(const std::string &occupier);

  object init_service_operations();

  template<typename T> void insert_status(const basyx::controlcomponent::ControlComponentConstants &, T status);

  template<typename T> T get_status(const basyx::controlcomponent::ControlComponentConstants &);
};

}
}
}
#endif //BASYX_CONTROLCOMPONENT_CONTROLCOMPONENT_H
