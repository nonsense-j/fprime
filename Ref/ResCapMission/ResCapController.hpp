// ======================================================================
// \title  ResCapController.hpp
// \author nonsense
// \brief  hpp file for ResCapController component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCapController_HPP
#define ResCapController_HPP

#include "Ref/ResCapMission/ResCapControllerComponentAc.hpp"

namespace Ref {

  class ResCapController :
    public ResCapControllerComponentBase
  {

    public:

      I32 loopIndex;
      bool skipOnce;

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCapController
      //!
      ResCapController(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCapController
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCapController
      //!
      ~ResCapController();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for resCapCallbackin
      //!
      void resCapCallbackin_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Handler implementation for simControlin
      //!
      void simControlin_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 control_id 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for START command handler
      //! Start single simulation
      void START_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for STOP command handler
      //! Stop single simulation
      void STOP_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for RESET command handler
      //! Reset single simulation
      void RESET_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace Ref

#endif
