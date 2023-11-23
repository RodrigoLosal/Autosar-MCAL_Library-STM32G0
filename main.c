#include "Std_Types.h"
#include "Bfx.h"
#include "Spi.h"

extern void initialise_monitor_handles( void );

int main( void )
{
    initialise_monitor_handles( );

    Spi_ConfigType config;
    Spi_Init( &config );

    Spi_Init( &config );


    while( 1u )
    {
    }

    return 0;
}
