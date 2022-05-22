module Ref {

  @ Component for receiving and performing a math operation
  active component ResCapExecutor {
 
    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for receiving the operation request
    sync input port resCapWakein: ResCapWake

    @ Port for env setting
    async input port envSetin: EnvSet

    @ Port for controlling the executor
    sync input port resCapExeCtrlin: ResCapExeCtrl

    @ Port for entering next loop by calling back to controller
    output port resCapCallbackout: ResCapCallback

    output port resCapStartout : ResCapAct

    output port resCapMoveout : ResCapMove

    output port resCap_attack_out : ResCapAct

    output port resCap_attack_over_out : ResCapAct

    output port resCap_take_photo_out : ResCapAct

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Event
    event port eventOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ init_succ
    event INIT_SUCC() \
      severity activity low \
      format "[ResCap] Stategy initializes successfully. Specification is located at : [Ref/ResCapMission/Config/ResCap.spec]." \

    @ Transition Info: evrytime entering a transition, state info should be emitted
    event SHOW_TANSITION(
                          state_id: I32 @< state id
                          $enemy: I8 @< sensor value
                          $ground_casualty: I8 @< sensor value
                          $attack: I8 @< action value
                          $attack_over: I8 @< action value
                          $take_photo: I8 @< action value
                          $attack_mode: I8 @< custom value
                          region: string @< current region name
                          region_base: string @< current region real name
                        ) \
      severity activity high \
      format "[ResCap] State #{d} ==> @Sensor: enemy[{d}] ground_casualty[{d}]; @Action: attack[{d}] attack_over[{d}] take_photo[{d}]; @Customs: attack_mode[{d}]; @Region: {}({})." \

    @ env update
    event ENV_UPDATE(
                  name: string
                  value: bool
                ) \
      severity activity high \
      format ">> [ResCap] Environment Sensor Updates: {} = {}"
        
    @ Start Simulation
    event START_RECV() \
      severity activity high \
      format "[ResCap] Simulation Starts --- "

    @ Stop Simulation
    event STOP_RECV() \
      severity activity high \
      format "[ResCap] Simulation Stops --- "

    @ Reset Simulation
    event RESET_RECV() \
      severity activity high \
      format "[ResCap] Simulation Resets --- "

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Set Sensor value
    async command SET_ENV(
                           name: EnvSensor
                           value: EnvValue
                         )

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    telemetry state_id: I32

    telemetry $enemy: I8

    telemetry $ground_casualty: I8

    telemetry $attack: I8

    telemetry $attack_over: I8

    telemetry $take_photo: I8

    telemetry $attack_mode: I8

    telemetry region: string

  }

}
