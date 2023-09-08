#include "Std_Types.h"
#include "Port.h"
#include "Port_Cfg.h"

// clang-format off
const Port_ConfigType PortsConfig[ PORT_PIN_NUMBER_OF_PORTS ] =
{
    { 
        .Port          = PORTS_C,
        .Pins          = PORTS_PIN_0 | PORTS_PIN_1,
        .Pull          = PORTS_NOPULL,
        .OutputDrive   = PORTS_PUSH_PULL,
        .Speed         = PORTS_LOW_SPEED,
        .Mode          = PORTS_MODE_OUTPUT,
        .Altern        = 0,
        .Pin_direction = PORTS_CHANGEABLE
    },
    { 
        .Port          = PORTS_A,
        .Pins          = PORTS_PIN_4 | PORTS_PIN_5,
        .Pull          = PORTS_PULLDOWN,
        .OutputDrive   = PORTS_OPEN_COLECTOR,
        .Speed         = PORTS_VERY_HIGH_SPEED,
        .Mode          = PORTS_MODE_OUTPUT,
        .Altern        = 0,
        .Pin_direction = PORTS_NON_CHANGEABLE 
    },
    { 
        .Port          = PORTS_B,
        .Pins          = PORTS_PIN_13 | PORTS_PIN_10 | PORTS_PIN_5,
        .Pull          = PORTS_PULLDOWN,
        .OutputDrive   = PORTS_OPEN_COLECTOR,
        .Speed         = PORTS_VERY_HIGH_SPEED,
        .Mode          = PORTS_MODE_ALT,
        .Altern        = PORT_PIN_MODE_AF2,
        .Pin_direction = PORTS_NON_CHANGEABLE 
    },
    { 
        .Port          = PORTS_D,
        .Pins          = PORTS_PIN_1,
        .Pull          = PORTS_PULLDOWN,
        .OutputDrive   = PORTS_OPEN_COLECTOR,
        .Speed         = PORTS_VERY_HIGH_SPEED,
        .Mode          = PORTS_MODE_INPUT,
        .Altern        = 0,
        .Pin_direction = PORTS_NON_CHANGEABLE 
    } 
};
// clang-format on