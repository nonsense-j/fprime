module Ref {

  @ Port connecting controller(Loop) and executor(single transition)
  port ResCapWake() -> bool

  @ Port for calling back to controoler to activate loop
  port ResCapCallback()

  @ Port to ctrl executor(0:start, 1:stop, 2:reset)
  port ResCapExeCtrl(control_id: I8)

  @ Port to invocate actuators for different actions.flag 0:doAct; flag 1:checkAct; flag 2:stopAct. flag3:checkStopAct return 1:finished.
  port ResCapAct(flag: I8) -> I8

  @ Port to invocate actuators for going to regions. flag 0:doAct; flag 1:checkAct; flag 2:stopAct. flag3:checkStopAct return 1:finished.
  port ResCapMove(
               flag: I8
               region: string
             ) -> I8

}
