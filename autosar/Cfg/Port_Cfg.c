#include "Port.h"

const Port_ConfigType PortConfig[PORT_PIN_NUMBER_OF_PORTS] =
{
    { .Port        = PORTS_C,
    .Pins        = PORTS_PIN_0 | PORTS_PIN_1 | PORTS_PIN_2 | PORTS_PIN_3 | PORTS_PIN_4 | PORTS_PIN_5 | PORTS_PIN_6 | PORTS_PIN_7,
    .Pull        = PORTS_NOPULL,
    .OutputDrive = PORTS_PUSH_PULL,
    .Speed       = PORTS_LOW_SPEED,
    .Mode        = PORTS_MODE_OUTPUT,
    .Altern      = 0 
    } 
};