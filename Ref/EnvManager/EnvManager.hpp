// ======================================================================
// \title  EnvManager.hpp
// \author nonsense
// \brief  hpp file for EnvManager component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef EnvManager_HPP
#define EnvManager_HPP

#include "Ref/EnvManager/EnvManagerComponentAc.hpp"

namespace Ref {

  class EnvManager :
    public EnvManagerComponentBase
  {

    public:

      I8 exeNum;

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object EnvManager
      //!
      EnvManager(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object EnvManager
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object EnvManager
      //!
      ~EnvManager();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for SET_ENV command handler
      //! env set
      void SET_ENV_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Ref::EnvSensor name, 
          Ref::EnvValue value 
      );


    };

} // end namespace Ref

#endif
