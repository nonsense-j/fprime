// ======================================================================
// \title  ResCap_take_photo.cpp
// \author nonsense
// \brief  cpp file for ResCap_take_photo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Ref/ResCapActuators/ResCap_take_photo.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  ResCap_take_photo ::
    ResCap_take_photo(
        const char *const compName
    ) : ResCap_take_photoComponentBase(compName)
  {

  }

  void ResCap_take_photo ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    ResCap_take_photoComponentBase::init(instance);
  }

  ResCap_take_photo ::
    ~ResCap_take_photo()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  I8 ResCap_take_photo ::
    resCap_take_photo_in_handler(
        const NATIVE_INT_TYPE portNum,
        I8 flag
    )
  {
    // TODO return
    this->log_ACTIVITY_LO_ACTFINISHED();
    return 1;
  }

} // end namespace Ref
