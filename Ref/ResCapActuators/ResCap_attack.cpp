// ======================================================================
// \title  ResCap_attack.cpp
// \author nonsense
// \brief  cpp file for ResCap_attack component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapActuators/ResCap_attack.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCap_attack ::
    ResCap_attack(
        const char *const compName
    ) : ResCap_attackComponentBase(compName)
  {

  }

  void ResCap_attack ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ResCap_attackComponentBase::init(instance);
  }

  ResCap_attack ::
    ~ResCap_attack()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I8 ResCap_attack ::
    resCap_attack_in_handler(
        const NATIVE_INT_TYPE portNum,
        I8 flag
    )
  {
    // TODO return
    this->log_ACTIVITY_LO_ACTFINISHED();
    return 1;
  }

} // end namespace Ref
