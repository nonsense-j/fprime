// ======================================================================
// \title  ResCapStart.hpp
// \author nonsense
// \brief  hpp file for ResCapStart component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCapStart_HPP
#define ResCapStart_HPP

#include "Ref/ResCapActuators/ResCapStartComponentAc.hpp"
#include <unistd.h>

namespace Ref {

  class ResCapStart :
    public ResCapStartComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCapStart
      //!
      ResCapStart(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCapStart
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCapStart
      //!
      ~ResCapStart();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for resCapStartin
      //!
      I8 resCapStartin_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 flag 
      );


    };

} // end namespace Ref

#endif
