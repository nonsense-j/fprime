module Ref {

  @ A env sensor list
  enum EnvSensor {
    $enemy
    $ground_casualty
  }

  enum EnvValue {
      TRUE
      FALSE
  }

  @ Port for env management
  port EnvSet(
               name: string
               value: I8
             )

}