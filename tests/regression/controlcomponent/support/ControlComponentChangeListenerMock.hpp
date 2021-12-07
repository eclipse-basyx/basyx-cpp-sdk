#ifndef BASYX_TESTING_SUPPORT_CONTROLCOMPONENT_CONTROLCOMPONENTCHANGELISTENER_MOCK_H_
#define BASYX_TESTING_SUPPORT_CONTROLCOMPONENT_CONTROLCOMPONENTCHANGELISTENER_MOCK_H_

#include <gtest/gtest.h>
#include <BaSyx/controlcomponent/interfaces/IControlComponentChangeListener.h>

using namespace basyx::controlcomponent;

class ControlComponentChangeListenerMock : public IControlComponentChangeListener
{
public:
  int unique_id = 0;

  int call_counter_onVariableChange = 0;
  int call_counter_onNewOccupier = 0;
  int call_counter_onNewOccupationState = 0;
  int call_counter_onLastOccupier = 0;
  int call_counter_onChangedExecutionMode = 0;
  int call_counter_onChangedExecutionState = 0;
  int call_counter_onChangedOperationMode = 0;
  int call_counter_onChangedWorkState = 0;
  int call_counter_onChangedErrorState = 0;
  int call_counter_onChangedPrevError = 0;
  int call_counter_getUniqueID = 0;

  ControlComponentChangeListenerMock(int id) : unique_id{id} {}
  ControlComponentChangeListenerMock() {}

  void onVariableChange(const std::string &varName, basyx::object newValue) override
  {
    call_counter_onVariableChange++;
  }

  void onNewOccupier(const std::string &occupierId) override
  {
    call_counter_onNewOccupier++;
  }

  void onNewOccupationState(basyx::controlcomponent::OccupationState state) override
  {
    call_counter_onNewOccupationState++;
  }

  void onLastOccupier(const std::string &lastOccupierId) override
  {
    call_counter_onLastOccupier++;
  }

  void onChangedExecutionMode(basyx::controlcomponent::ExecutionMode newExecutionMode) override
  {
    call_counter_onChangedExecutionMode++;
  }

  void onChangedExecutionState(basyx::controlcomponent::ExecutionState newExecutionState) override
  {
    call_counter_onChangedExecutionState++;
  }

  void onChangedOperationMode(const std::string &newOperationMode) override
  {
    call_counter_onChangedOperationMode++;
  }

  void onChangedWorkState(const std::string &newWorkState) override
  {
    call_counter_onChangedWorkState++;
  }

  void onChangedErrorState(const std::string &newWorkState) override
  {
    call_counter_onChangedErrorState++;
  }

  void onChangedPrevError(const std::string &newWorkState) override
  {
    call_counter_onChangedPrevError++;
  }

  int getUniqueID() override
  {
    call_counter_getUniqueID++;
    return unique_id;
  }

  void reset()
  {
    call_counter_onVariableChange = 0;
    call_counter_onNewOccupier = 0;
    call_counter_onNewOccupationState = 0;
    call_counter_onLastOccupier = 0;
    call_counter_onChangedExecutionMode = 0;
    call_counter_onChangedExecutionState = 0;
    call_counter_onChangedOperationMode = 0;
    call_counter_onChangedWorkState = 0;
    call_counter_onChangedErrorState = 0;
    call_counter_onChangedPrevError = 0;
    call_counter_getUniqueID = 0;  
  }
};

#endif