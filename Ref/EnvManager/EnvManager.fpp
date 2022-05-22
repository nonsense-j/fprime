module Ref {

  @ Component for controlling the system 
  passive component EnvManager {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for innovating the executors to change sensor
    output port envSetout: EnvSet

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ Event port
    event port eventOut

    @ Telemetry port
    telemetry port tlmOut

    @ Text event port
    text event port textEventOut

    @ Time get port
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ env set
    sync command SET_ENV(
                           name: EnvSensor
                           value: EnvValue
                        )

  }

}
