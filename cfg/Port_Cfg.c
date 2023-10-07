#include "Std_Types.h"
#include "Port.h"

// clang-format off
const Port_ConfigType PortConfig[ PORT_PIN_NUMBER_OF_PORTS ] =
{

  {
  .Port        = PORTS_C,
  .Pins        = PORTS_PIN_00 | PORTS_PIN_01 | PORTS_PIN_02 | PORTS_PIN_03 | PORTS_PIN_04 | PORTS_PIN_05 | PORTS_PIN_06 | PORTS_PIN_07,
  .Pull        = PORTS_NOPULL,
  .OutputDrive = PORTS_PUSH_PULL,
  .Speed       = PORTS_LOW_SPEED,
  .Mode        = PORTS_MODE_OUTPUT
  } 
};
// clang-format on