// ======================================================================
// \title  ResCapMove.cpp
// \author nonsense
// \brief  cpp file for ResCapMove component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapActuators/ResCapMove.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCapMove ::
    ResCapMove(
        const char *const compName
    ) : ResCapMoveComponentBase(compName)
  {

  }

  void ResCapMove ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ResCapMoveComponentBase::init(instance);
  }

  ResCapMove ::
    ~ResCapMove()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I8 ResCapMove ::
    resCapMovein_handler(
        const NATIVE_INT_TYPE portNum,
        I8 flag,
        const regionString &region
    )
  {
    // TODO return
    const char * reg_str = region.toChar();
    sleep(5);
    if (*reg_str == '!')
      this->log_ACTIVITY_LO_STAYFINISHED(reg_str+1);
    else
      this->log_ACTIVITY_LO_MOVEFINISHED(region);
    return 1;
  }

} // end namespace Ref
