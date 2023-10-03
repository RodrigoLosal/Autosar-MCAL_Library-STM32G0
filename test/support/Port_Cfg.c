#include "Std_Types.h"
#include "Port.h"
#include "Port_Cfg.h"

// clang-format off
const Port_ConfigType PortsConfig[ PORT_PIN_NUMBER_OF_PORTS ] =
{
    { 
        .Port          = PORTS_C,
        .Pins          = PORTS_PIN_00 | PORTS_PIN_01,
        .Pull          = PORTS_NOPULL,
        .OutputDrive   = PORTS_PUSH_PULL,
        .Speed         = PORTS_LOW_SPEED,
        .Mode          = PORTS_MODE_OUTPUT,
        .DirChange     = TRUE
    },
    { 
        .Port          = PORTS_A,
        .Pins          = PORTS_PIN_04 | PORTS_PIN_05,
        .Pull          = PORTS_PULLDOWN,
        .OutputDrive   = PORTS_OPEN_COLECTOR,
        .Speed         = PORTS_VERY_HIGH_SPEED,
        .Mode          = PORTS_MODE_OUTPUT,
        .DirChange     = FALSE 
    },
    { 
        .Port          = PORTS_B,
        .Pins          = PORTS_PIN_13 | PORTS_PIN_10 | PORTS_PIN_05,
        .Pull          = PORTS_PULLDOWN,
        .OutputDrive   = PORTS_OPEN_COLECTOR,
        .Speed         = PORTS_VERY_HIGH_SPEED,
        .Mode          = PORTS_MODE_ALT_AF2,
        .DirChange     = FALSE 
    },
    { 
        .Port          = PORTS_D,
        .Pins          = PORTS_PIN_01,
        .Pull          = PORTS_PULLDOWN,
        .OutputDrive   = PORTS_OPEN_COLECTOR,
        .Speed         = PORTS_VERY_HIGH_SPEED,
        .Mode          = PORTS_MODE_INPUT,
        .DirChange     = FALSE 
    } 
};
// clang-format on