// ======================================================================
// \title  ResCap_take_photo.hpp
// \author nonsense
// \brief  hpp file for ResCap_take_photo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef ResCap_take_photo_HPP
#define ResCap_take_photo_HPP

#include "Ref/ResCapActuators/ResCap_take_photoComponentAc.hpp"

namespace Ref {

  class ResCap_take_photo :
    public ResCap_take_photoComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ResCap_take_photo
      //!
      ResCap_take_photo(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object ResCap_take_photo
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ResCap_take_photo
      //!
      ~ResCap_take_photo();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for resCap_take_photo_in
      //!
      I8 resCap_take_photo_in_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          I8 flag 
      );


    };

} // end namespace Ref

#endif
