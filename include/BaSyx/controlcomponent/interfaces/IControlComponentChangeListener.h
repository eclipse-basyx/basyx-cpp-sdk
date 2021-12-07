/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_CONTROLCOMPONENT_ICONTROLCOMPONENTCHANGELISTENER_H
#define BASYX_CONTROLCOMPONENT_ICONTROLCOMPONENTCHANGELISTENER_H

#include <BaSyx/shared/object.h>
#include <BaSyx/controlcomponent/enumerations/OccupationState.h>
#include <BaSyx/controlcomponent/enumerations/ExecutionState.h>
#include <BaSyx/controlcomponent/enumerations/ExecutionMode.h>

namespace basyx {
namespace controlcomponent {

/**
 * Receive change events from control components.
 */
class IControlComponentChangeListener
{
public:
  virtual ~IControlComponentChangeListener() = 0;

  /**
   * Indicate change of a variable
   */
  virtual void onVariableChange(const std::string & varName, object newValue) = 0;


  /**
   * Indicate new occupier
   */
  virtual void onNewOccupier(const std::string & occupierId) = 0;


  /**
   * Indicate new occupation state
   */
  virtual void onNewOccupationState(OccupationState state) = 0;


  /**
   * Indicate a change of last occupier.
   */
  virtual void onLastOccupier(const std::string & lastOccupierId) = 0;


  /**
   * Indicate an execution mode change
   */
  virtual void onChangedExecutionMode(ExecutionMode newExecutionMode) = 0;


  /**
   * Indicate an execution state change
   */
  virtual void onChangedExecutionState(ExecutionState newExecutionState) = 0;


  /**
   * Indicate an operation mode change
   */
  virtual void onChangedOperationMode(const std::string & newOperationMode) = 0;


  /**
   * Indicate an work state change
   */
  virtual void onChangedWorkState(const std::string & newWorkState) = 0;


  /**
   * Indicate an error state change
   */
  virtual void onChangedErrorState(const std::string & newWorkState) = 0;


  /**
   * Indicate an previous error state change.
   */
  virtual void onChangedPrevError(const std::string & newWorkState) = 0;

  /**
   * Generates a unique ID to identify ControlComponentChangeListener
   */
  virtual int getUniqueID() = 0;
};

inline IControlComponentChangeListener::~IControlComponentChangeListener() = default;

}
}

#endif //BASYX_API_V2_SDK_ICONTROLCOMPONENTCHANGELISTENER_H
