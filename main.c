#include "Std_Types.h"
#include "Bfx.h"
#include "Pwm.h"
#include "Fls.h"
#include "Port.h"
#include "Spi.h"
#include "Gpt.h"
#include "Can.h"
#include "Adc.h"
#include "Nvic.h"
#include "Mcu.h"
#include "Dio.h"
#include "Det.h"

int main( void )
{
    // Spi_ConfigType a = { 0 };
    Pwm_ConfigType b = { 0 };


    // Spi_Init( &a );
    // Spi_Init( &a );
    Pwm_Init( &b );
    Pwm_Init( &b );

    while( 1u )
    {
    }

    return 0;
}
