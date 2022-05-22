// ======================================================================
// \title  ResCapMove.hpp
// \author nonsense
// \brief  hpp file for ResCapMove component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCapMove_HPP
#define ResCapMove_HPP

#include "Ref/ResCapActuators/ResCapMoveComponentAc.hpp"
#include <unistd.h>

namespace Ref {

  class ResCapMove :
    public ResCapMoveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCapMove
      //!
      ResCapMove(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCapMove
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCapMove
      //!
      ~ResCapMove();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for resCapMovein
      //!
      I8 resCapMovein_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 flag, 
          const regionString &region 
      );


    };

} // end namespace Ref

#endif
