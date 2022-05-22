// ======================================================================
// \title  ResCap_attack_over.cpp
// \author nonsense
// \brief  cpp file for ResCap_attack_over component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapActuators/ResCap_attack_over.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCap_attack_over ::
    ResCap_attack_over(
        const char *const compName
    ) : ResCap_attack_overComponentBase(compName)
  {

  }

  void ResCap_attack_over ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ResCap_attack_overComponentBase::init(instance);
  }

  ResCap_attack_over ::
    ~ResCap_attack_over()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I8 ResCap_attack_over ::
    resCap_attack_over_in_handler(
        const NATIVE_INT_TYPE portNum,
        I8 flag
    )
  {
    // TODO return
    this->log_ACTIVITY_LO_ACTFINISHED();
    return 1;
  }

} // end namespace Ref
