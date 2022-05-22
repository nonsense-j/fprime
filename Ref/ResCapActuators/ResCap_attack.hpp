// ======================================================================
// \title  ResCap_attack.hpp
// \author nonsense
// \brief  hpp file for ResCap_attack component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCap_attack_HPP
#define ResCap_attack_HPP

#include "Ref/ResCapActuators/ResCap_attackComponentAc.hpp"

namespace Ref {

  class ResCap_attack :
    public ResCap_attackComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCap_attack
      //!
      ResCap_attack(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCap_attack
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCap_attack
      //!
      ~ResCap_attack();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for resCap_attack_in
      //!
      I8 resCap_attack_in_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 flag 
      );


    };

} // end namespace Ref

#endif
