// ======================================================================
// \title  SimManager.cpp
// \author nonsense
// \brief  cpp file for SimManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/SimManager/SimManager.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  SimManager ::
    SimManager(
        const char *const compName
    ) : SimManagerComponentBase(compName)
  {

  }

  void SimManager ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    SimManagerComponentBase::init(instance);
    this->exeNum = 1;
  }

  SimManager ::
    ~SimManager()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void SimManager ::
    START_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->log_ACTIVITY_LO_START_RECV();
    for (I8 i = 0; i < this->exeNum; i++) {
        this->simControlout_out(i, 0);
    }
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void SimManager ::
    STOP_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->log_ACTIVITY_LO_STOP_RECV();
    for (I8 i = 0; i < this->exeNum; i++) {
        this->simControlout_out(i, 1);
    }
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void SimManager ::
    RESET_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->log_ACTIVITY_LO_RESET_RECV();
    for (I8 i = 0; i < this->exeNum; i++) {
        this->simControlout_out(i, 2);
    }
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Ref
