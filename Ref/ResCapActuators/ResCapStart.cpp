// ======================================================================
// \title  ResCapStart.cpp
// \author nonsense
// \brief  cpp file for ResCapStart component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapActuators/ResCapStart.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCapStart ::
    ResCapStart(
        const char *const compName
    ) : ResCapStartComponentBase(compName)
  {

  }

  void ResCapStart ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ResCapStartComponentBase::init(instance);
  }

  ResCapStart ::
    ~ResCapStart()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I8 ResCapStart ::
    resCapStartin_handler(
        const NATIVE_INT_TYPE portNum,
        I8 flag
    )
  {
    // TODO return
    sleep(8);
    this->log_ACTIVITY_LO_STARTFINISHED();
    return 1;
  }

} // end namespace Ref
