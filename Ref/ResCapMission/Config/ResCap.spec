# This is a specification definition file for the LTLMoP toolkit.
# Format details are described at the beginning of each section below.


======== SETTINGS ========

Actions: # List of action propositions and their state (enabled = 1, disabled = 0)
attack, 1
attack_over, 1
take_photo, 1

CompileOptions:
convexify: True
parser: structured
symbolic: False
use_region_bit_encoding: True
synthesizer: jtlv
fastslow: False
decompose: True

CurrentConfigName:
ResCap

Customs: # List of custom propositions
attack_mode

RegionFile: # Relative path of region description file
ResCap.regions

Sensors: # List of sensor propositions and their state (enabled = 1, disabled = 0)
enemy, 1
ground_casualty, 1


======== SPECIFICATION ========

RegionMapping: # Mapping between region names and their decomposed counterparts
right = p2, p4
up = p3, p9, p10, p11
down = p8, p12, p13, p14
others = 
nofly = p3, p4, p6, p8
left = p5, p6

Spec: # Specification in structured English
# initial conditions
Env starts with false
you start in left and !nofly with false

# Guarantee
Always !nofly

# Define robot safety including how to attack
Do attack if and only if you are sensing enemy and you are not activating attack_mode
If you are activating attack then stay there
attack_mode is set on attack and reset on attack_over
Do attack_over if and only if you are not sensing enemy and you are activating attack_mode

# Define when and how to take_photo
Do take_photo if and only if you are sensing ground_casualty
if you are activating take_photo or you were activating take_photo then stay there

# Patrol goals
Group areas is left, up, down, right
If you are not activating attack_mode and you are not activating take_photo then visit all areas

