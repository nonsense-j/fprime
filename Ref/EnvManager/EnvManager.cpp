// ======================================================================
// \title  EnvManager.cpp
// \author nonsense
// \brief  cpp file for EnvManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/EnvManager/EnvManager.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  EnvManager ::
    EnvManager(
        const char *const compName
    ) : EnvManagerComponentBase(compName)
  {

  }

  void EnvManager ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    EnvManagerComponentBase::init(instance);
    this->exeNum = 1;
  }

  EnvManager ::
    ~EnvManager()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void EnvManager ::
    SET_ENV_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        Ref::EnvSensor name,
        Ref::EnvValue value
    )
  {
    // TODO
    // the number of executors
    I8 val = 0;
    for (I8 i = 0; i < this->exeNum; i++) {
      switch (name.e) {
		case EnvSensor::enemy:
			val = (value.e == EnvValue::TRUE) ? 1 : 0;
			this->envSetout_out(i, "enemy", val);
			break;
		case EnvSensor::ground_casualty:
			val = (value.e == EnvValue::TRUE) ? 1 : 0;
			this->envSetout_out(i, "ground_casualty", val);
			break;
    default:
        // FW_ASSERT(0, name.e);
        break;
      }
    }
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Ref
