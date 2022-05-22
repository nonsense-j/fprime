module Ref {

  @ Port for general control
  port SimControl(
    control_id: I8
  )

  @ Component for controlling the system 
  passive component SimManager {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for controlling the general simulation
    output port simControlout: SimControl

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

    @ general simulation starts
    sync command START()

    @ general simulation stops
    sync command STOP()

    @ @ general simulation resets
    sync command RESET()

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------
    
    @ Start Simulation
    event START_RECV() \
      severity activity low \
      format "General Simulation is Starting --- "

    @ Stop Simulation
    event STOP_RECV() \
      severity activity low \
      format "General Simulation is Stopping --- "

    @ Reset Simulation
    event RESET_RECV() \
      severity activity low \
      format "General Simulation is Resetting --- "

  }

}
