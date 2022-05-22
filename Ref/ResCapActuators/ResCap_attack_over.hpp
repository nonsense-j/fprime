// ======================================================================
// \title  ResCap_attack_over.hpp
// \author nonsense
// \brief  hpp file for ResCap_attack_over component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCap_attack_over_HPP
#define ResCap_attack_over_HPP

#include "Ref/ResCapActuators/ResCap_attack_overComponentAc.hpp"

namespace Ref {

  class ResCap_attack_over :
    public ResCap_attack_overComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCap_attack_over
      //!
      ResCap_attack_over(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCap_attack_over
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCap_attack_over
      //!
      ~ResCap_attack_over();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for resCap_attack_over_in
      //!
      I8 resCap_attack_over_in_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 flag 
      );


    };

} // end namespace Ref

#endif
