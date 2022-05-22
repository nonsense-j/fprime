// ======================================================================
// \title  ResCapExecutor.cpp
// \author nonsense
// \brief  cpp file for ResCapExecutor component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapMission/ResCapExecutor.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCapExecutor ::
    ResCapExecutor(
        const char *const compName
    ) : ResCapExecutorComponentBase(compName)
  {

  }

  void ResCapExecutor ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ResCapExecutorComponentBase::init(queueDepth, instance);
    this->SpecStrategy = new Strategy("ResCapMission/Config/ResCap.spec");
    this->envChange = false;
    this->curActions.clear();
    this->doneActionsMap.clear();
  }

  ResCapExecutor ::
    ~ResCapExecutor()
  {
    delete this->SpecStrategy;
  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ResCapExecutor ::
    envSetin_handler(
        const NATIVE_INT_TYPE portNum,
        const nameString &name,
        I8 value
    )
  {
    // TODO
    if (this->SpecStrategy->curSensorMap[name.toChar()] != value)
      this->envChange = true;

    this->SpecStrategy->curSensorMap[name.toChar()] = value;
    this->log_ACTIVITY_HI_ENV_UPDATE(name, value == 1);
  }

  void ResCapExecutor ::
    resCapExeCtrlin_handler(
        const NATIVE_INT_TYPE portNum,
        I8 control_id
    )
  {
    // TODO
    switch (control_id) {
      case 0: {  // start
        this->stopFlag = false;
        this->log_ACTIVITY_LO_INIT_SUCC();
        this->log_ACTIVITY_HI_START_RECV();
        this->resCapStartout_out(0, 0);
        break;
      }
      case 1:   // stop
        this->stopFlag = true;
        break;
      case 2:   // reset
        this->envChange = false;
        this->SpecStrategy->setCurState(0);
        this->doneActionsMap.clear();
        this->curActions.clear();
        this->log_ACTIVITY_HI_RESET_RECV();
        break;
      default:
        break;
    }
  }

  bool ResCapExecutor ::
    resCapWakein_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    // TODO return
    std::vector<std::string> tmp;

    if (this->stopFlag){
      this->log_ACTIVITY_HI_STOP_RECV();
      return true;
    }

    // check whether the env has changed  -- state change
    if (this->envChange)
    {
      std::unordered_map<std::string, int> backupMap(this->SpecStrategy->curSensorMap);
      if (this->curActions.size() == this->doneActionsMap.size()){
        // unchanged states will not be printed
        if (!curActions.empty()) {
          std::cout<< "==============> Finish Actions -- State Change <==============" << std::endl;
          //  print current state information
          this->SpecStrategy->refreshCurState();
          this->SaveCurStateInfo(this->SpecStrategy->curStateID);
        }
      }
      std::cout << "==============> Recv Env Change : "<< backupMap["enemy"];
      std::cout << "\t" << backupMap["ground_casualty"] <<"<==============" << std::endl;
      tmp = this->SpecStrategy->runSingleTransition(backupMap);
      std::cout << "Env change, Transition needs Actions : ";
      printStringVector(tmp);
      // run the actuators to do actions
      this->curActions.assign(tmp.begin(), tmp.end());
      this->doneActionsMap.clear();
      std::cout<< "==============> Do Actions to Env Change <==============" << std::endl;
      for (std::string act : this->curActions)
        this->RunActuators(act, 0);
    }
    // env not change, actions not finish, then check the actuators -- no state change
    else if (!this->envChange && this->curActions.size() != this->doneActionsMap.size()){
      // set the flag for checking
      for (std::string act : this->curActions)
          this->RunActuators(act, 1);
    }

    // check whether the actions are finished -- state change
    if (this->curActions.size() == this->doneActionsMap.size()) {
      //  refresh state after the acts are executed
      this->SpecStrategy->refreshCurState();
      
      tmp = this->SpecStrategy->runSingleTransition(this->SpecStrategy->curSensorMap);
      // if the state stay unchanged, no actions will be executed because they are done
      if (this->SpecStrategy->nextStateID != this->SpecStrategy->curStateID){
        //  print current state information
        std::cout<< "==============> Finish Actions -- State Change <==============" << std::endl;
        this->SaveCurStateInfo(this->SpecStrategy->curStateID);
        std::cout << "Transition needs actions : ";
        printStringVector(tmp);
        
        // run the actuators to do actions
        this->curActions.assign(tmp.begin(), tmp.end());
        this->doneActionsMap.clear();
        for (std::string act : this->curActions)
          this->RunActuators(act, 0);
      }
      else {
        // record the state if env change actions are finished
        if (this->envChange) {
          std::cout<< "==============> Finish Actions -- State Change <==============" << std::endl;
          this->SaveCurStateInfo(this->SpecStrategy->curStateID);
          this->envChange = false;
        }
        this->doneActionsMap.clear();
        this->curActions.clear();
      }
    }

    // // set frequency as 2hz
    // sleep(0.5);

    // invocate the controller for next loop
    this->resCapCallbackout_out(0);

    return false;
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void ResCapExecutor ::
    SET_ENV_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Ref::EnvSensor name,
        Ref::EnvValue value
    )
  {
    // TODO
    I8 val;
    switch (name.e) {
      case EnvSensor::enemy:
          val = (value.e == EnvValue::TRUE) ? 1 : 0;
          if (this->SpecStrategy->curSensorMap["enemy"] != val)
            this->envChange = true;
          this->SpecStrategy->curSensorMap["enemy"] = val;
          this->log_ACTIVITY_HI_ENV_UPDATE("enemy", val == 1);
          break;
      case EnvSensor::ground_casualty:
          val = (value.e == EnvValue::TRUE) ? 1 : 0;
          if (this->SpecStrategy->curSensorMap["ground_casualty"] != val)
            this->envChange = true;
          this->SpecStrategy->curSensorMap["ground_casualty"] = val;
          this->log_ACTIVITY_HI_ENV_UPDATE("ground_casualty", val == 1);
          break;
      default:
          // FW_ASSERT(0, name.e);
          break;
      }
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  // ----------------------------------------------------------------------
  // Customized Functions
  // ----------------------------------------------------------------------
  void ResCapExecutor ::
    RunActuators(
        std::string action,
        I8 flag
    )
  {
    // flag 0:doAct; flag 1:checkAct; flag 2:stopAll. 
    if (action.compare("attack") == 0){
      if (this->resCap_attack_out_out(0, flag) == 1)
        this->doneActionsMap[action] = 1;
    }
    else if (action.compare("!attack") == 0){
      if (this->resCap_attack_out_out(0, flag + 2) == 1)
        this->doneActionsMap[action] = 1;
    }
    else if (action.compare("attack_over") == 0){
      if (this->resCap_attack_over_out_out(0, flag) == 1)
        this->doneActionsMap[action] = 1;
    }
    else if (action.compare("!attack_over") == 0){
      if (this->resCap_attack_over_out_out(0, flag + 2) == 1)
        this->doneActionsMap[action] = 1;
    }
    else if (action.compare("take_photo") == 0){
      if (this->resCap_take_photo_out_out(0, flag) == 1)
        this->doneActionsMap[action] = 1;
    }
    else if (action.compare("!take_photo") == 0){
      if (this->resCap_take_photo_out_out(0, flag + 2) == 1)
        this->doneActionsMap[action] = 1;
    }
    else {
      if (action.find("!") == 0){
        if (this->resCapMoveout_out(0, flag + 2, action.c_str()) == 1)
        this->doneActionsMap[action] = 1;
      }
      else{
        if (this->resCapMoveout_out(0, flag, action.c_str()) == 1)
        this->doneActionsMap[action] = 1;
      }
    }
  }

  void ResCapExecutor ::
    SaveCurStateInfo(int state_id)
  {
    State curState = this->SpecStrategy->States[state_id];
    log_ACTIVITY_HI_SHOW_TANSITION(curState.state_id,
      curState.propositions[0].second,
      curState.propositions[1].second,
      curState.propositions[2].second,
      curState.propositions[3].second,
      curState.propositions[4].second,
      curState.propositions[5].second,
      this->SpecStrategy->getCurRegionNamePair().first.c_str(),
      this->SpecStrategy->getCurRegionNamePair().second.c_str());
    this->tlmWrite_state_id(curState.state_id);
    this->tlmWrite_enemy(curState.propositions[0].second);
    this->tlmWrite_ground_casualty(curState.propositions[1].second);
    this->tlmWrite_attack(curState.propositions[2].second);
    this->tlmWrite_attack_over(curState.propositions[3].second);
    this->tlmWrite_take_photo(curState.propositions[4].second);
    this->tlmWrite_attack_mode(curState.propositions[5].second);
    this->tlmWrite_region(this->SpecStrategy->getCurRegionNamePair().first.c_str());
  }

} // end namespace Ref
