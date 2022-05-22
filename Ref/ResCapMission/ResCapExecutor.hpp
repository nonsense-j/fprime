// ======================================================================
// \title  ResCapExecutor.hpp
// \author nonsense
// \brief  hpp file for ResCapExecutor component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCapExecutor_HPP
#define ResCapExecutor_HPP

#include "Ref/ResCapMission/ResCapExecutorComponentAc.hpp"
#include "Ref/AutParser/autparser.hpp"

namespace Ref {

  class ResCapExecutor :
    public ResCapExecutorComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // SpecStrategy, stop sign
      // ----------------------------------------------------------------------
      Strategy *SpecStrategy;
      bool stopFlag, envChange;
      std::vector<std::string> curActions;
      std::unordered_map<std::string, int> doneActionsMap;

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCapExecutor
      //!
      ResCapExecutor(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCapExecutor
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCapExecutor
      //!
      ~ResCapExecutor();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for envSetin
      //!
      void envSetin_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const nameString &name,
          I8 value
      );

      //! Handler implementation for resCapExeCtrlin
      //!
      void resCapExeCtrlin_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 control_id
      );

      //! Handler implementation for resCapWakein
      //!
      bool resCapWakein_handler(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SET_ENV command handler
      //! Set Sensor value
      void SET_ENV_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Ref::EnvSensor name,
          Ref::EnvValue value
      );

      // ----------------------------------------------------------------------
      // Customized Functions
      // ----------------------------------------------------------------------
      void RunActuators(
          std::string action,
          I8 flag
      );
      void SaveCurStateInfo(int state_id);


    };

} // end namespace Ref

#endif
