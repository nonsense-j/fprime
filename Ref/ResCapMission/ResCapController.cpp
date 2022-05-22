// ======================================================================
// \title  ResCapController.cpp
// \author nonsense
// \brief  cpp file for ResCapController component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapMission/ResCapController.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCapController ::
    ResCapController(
        const char *const compName
    ) : ResCapControllerComponentBase(compName)
  {

  }

  void ResCapController ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    ResCapControllerComponentBase::init(queueDepth, instance);
    this->loopIndex = 0;
  }

  ResCapController ::
    ~ResCapController()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void ResCapController ::
    resCapCallbackin_handler(
        const NATIVE_INT_TYPE portNum
    )
  {
    // TODO
    this->tlmWrite_num(++this->loopIndex);
    // this->log_ACTIVITY_LO_LOOPINFO(this->loopIndex);
    // display single transition
    if (!this->skipOnce)
      this->skipOnce = this->resCapWakeout_out(0);
  }

  void ResCapController ::
    simControlin_handler(
        const NATIVE_INT_TYPE portNum,
        I8 control_id
    )
  {
    // TODO
    switch (control_id) {
    case 0:   // start
      this->resCapExeCtrlout_out(0, 0);
      // display single transition
      if (this->skipOnce && this->loopIndex != 0)
        this->loopIndex--;
      this->tlmWrite_num(++this->loopIndex);
      // this->log_ACTIVITY_LO_LOOPINFO(this->loopIndex);
      this->skipOnce = this->resCapWakeout_out(0);
      break;
    case 1:   // stop
      this->resCapExeCtrlout_out(0, 1);
      break;
    case 2:   // reset
      this->resCapExeCtrlout_out(0, 2);
      this->loopIndex = 0;
      break;
    default:
      break;
    }
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void ResCapController ::
    START_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->resCapExeCtrlout_out(0, 0);
    // display single transition
    if (this->skipOnce && this->loopIndex != 0)
      this->loopIndex--;
    this->tlmWrite_num(++this->loopIndex);
    // this->log_ACTIVITY_LO_LOOPINFO(this->loopIndex);
    this->skipOnce = this->resCapWakeout_out(0);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void ResCapController ::
    STOP_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->resCapExeCtrlout_out(0, 1);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void ResCapController ::
    RESET_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->resCapExeCtrlout_out(0, 2);
    this->loopIndex = 0;
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Ref
