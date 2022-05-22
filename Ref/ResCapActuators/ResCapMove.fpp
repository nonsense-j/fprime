module Ref {
  @ Component for customize your own actions
  passive component ResCapMove {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    sync input port resCapMovein : ResCapMove

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

    @ arrived at region
    event MOVEFINISHED(
                  region: string
                ) \
      severity activity low \
      format "[ResCap] Arrived at {}."

    @ stay there
    event STAYFINISHED(
                  region: string
                ) \
      severity activity low \
      format "[ResCap] Still Stay at {}."

  }

}
