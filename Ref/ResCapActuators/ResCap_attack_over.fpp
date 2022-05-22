module Ref {
  @ Component for customize your own actions
  passive component ResCap_attack_over {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    sync input port resCap_attack_over_in : ResCapAct

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
      format "[ResCap] Action: attack_over has finished."

  }

}
