#include "Bfx.h"
#include "Std_Types.h"
#include "Registers.h"
#include "Port.h"

static const Port_ConfigType *LocalConfigPtr;

void Port_Init( const Port_ConfigType *ConfigPtr )
{
    Port_RegisterType *port;
    uint32 mask;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };

    for( uint8 j = 0; j < PORT_PIN_NUMBER_OF_PORTS; j++ )
    {
        port = ports[ ( &ConfigPtr[ j ] )->Port ];
        mask = 1u;
        for( uint32 i = 0u; i < 16u; i++ )
        {
            if( Bfx_TstBitLnMask_u32u32_u8( ( &ConfigPtr[ j ] )->Pins, mask ) == TRUE )
            {
                /*change values on PUPDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->PUPDR, (uint8)( i * 2u ), (uint8)2u, (uint32)( &ConfigPtr[ j ] )->Pull );
                /*change values on OTYPER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->OTYPER, i, 1, (uint32)( &ConfigPtr[ j ] )->OutputDrive );
                /*change values on OSPEEDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->OSPEEDR, ( i * 2 ), 2, (uint32)( &ConfigPtr[ j ] )->Speed );
                /*change values on MODER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, ( i * 2 ), 2, (uint32)( &ConfigPtr[ j ] )->Mode );
                if( i < 8u )
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRL, ( i * 4 ), 4, (uint32)( &ConfigPtr[ j ] )->Altern );
                }
                else
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRH, ( i - 8 ) * 4, 4, (uint32)( &ConfigPtr[ j ] )->Altern );
                }
            }
            mask = mask << 1;
        }
    }
    LocalConfigPtr = ConfigPtr;
}


void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ) /* cppcheck-suppress misra-c2012-8.4 ; function will not always be defined */
{
    Port_RegisterType *port;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, (uint8)( Pin & 0xFu ), 2, (uint8)Direction );
}

void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ) /* cppcheck-suppress misra-c2012-8.4 ; function will not always be defined */
{
    Port_RegisterType *port;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    if( ( Pin & 0xFu ) < 8u )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRL, ( Pin & 0xFu ), 4, (uint32)Mode );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRH, ( ( Pin & 0xFu ) - 8 ), 4, (uint32)Mode );
    }
}

void Port_GetVersionInfo( Std_VersionInfoType *versioninfo ) /* cppcheck-suppress misra-c2012-8.4 ; function will not always be defined */
{
    versioninfo->moduleID         = 0;
    versioninfo->sw_major_version = 0;
    versioninfo->sw_minor_version = 0;
    versioninfo->sw_patch_version = 0;
    versioninfo->vendorID         = 0;
}

void Port_RefreshPortDirection( void ) /* cppcheck-suppress misra-c2012-8.4 ; function will not always be defined */
{
    Port_RegisterType *port;
    uint32 mask;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };

    for( uint8 j = 0; j < PORT_PIN_NUMBER_OF_PORTS; j++ )
    {
        port = ports[ ( &LocalConfigPtr[ j ] )->Port ];
        mask = 1u;
        for( uint32 i = 0u; i < 16u; i++ )
        {
            if( Bfx_TstBitLnMask_u32u32_u8( ( &LocalConfigPtr[ j ] )->Pins, mask ) == TRUE )
            {
                /*change values on MODER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, ( i * 2 ), 2, (uint32)( &LocalConfigPtr[ j ] )->Mode );
            }
            mask = mask << 1;
        }
    }
}