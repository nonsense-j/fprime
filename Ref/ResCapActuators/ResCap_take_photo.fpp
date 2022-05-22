module Ref {
  @ Component for customize your own actions
  passive component ResCap_take_photo {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    sync input port resCap_take_photo_in : ResCapAct

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Event port
    event port eventOut

    @ Telemetry port
    telemetry port tlmOut

    @ Text event port
    text event port textEventOut

    @ Time get port
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Print the index of simulation
    event ACTFINISHED() \
      severity activity low \
      format "[ResCap] Action: take_photo has finished."

  }

}
