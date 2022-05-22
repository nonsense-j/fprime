// ======================================================================
// \title  SimManager.hpp
// \author nonsense
// \brief  hpp file for SimManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SimManager_HPP
#define SimManager_HPP

#include "Ref/SimManager/SimManagerComponentAc.hpp"

namespace Ref {

  class SimManager :
    public SimManagerComponentBase
  {

    public:

      I8 exeNum;

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object SimManager
      //!
      SimManager(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object SimManager
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object SimManager
      //!
      ~SimManager();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for START command handler
      //! general simulation starts
      void START_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for STOP command handler
      //! general simulation stops
      void STOP_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for RESET command handler
      //! @ general simulation resets
      void RESET_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace Ref

#endif
