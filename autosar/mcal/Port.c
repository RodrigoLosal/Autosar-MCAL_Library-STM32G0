#include "Port.h"
#include "Bfx.h"
#include "Register.h"

uint16 port_direction_change[ 6 ];
uint32 port_moder[ 6 ] = { 0xEBFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

void Port_Init( const Port_ConfigType *ConfigPtr )
{
    Port_RegisterType *port;
    uint32 mask                   = 1u;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ ConfigPtr->Port ];

    if( ConfigPtr->Pin_direction == PORTS_CHANGEABLE )
    {
        port_direction_change[ ConfigPtr->Port ] |= ConfigPtr->Pins;
    }
    else if( ConfigPtr->Pin_direction == PORTS_NON_CHANGEABLE )
    {
        port_direction_change[ ConfigPtr->Port ] &= ~( ConfigPtr->Pins );
    }

    for( uint32 i = 0u; i < 16u; i++ )
    {
        if( Bfx_TstBitLnMask_u32u32_u8( ConfigPtr->Pins, mask ) == TRUE )
        {
            /*change values on PUPDR*/
            Bfx_ClrBitMask_u32u32( (uint32 *)&port->PUPDR, ( 0x03 << ( i * 2 ) ) );
            Bfx_SetBitMask_u32u32( (uint32 *)&port->PUPDR, ( (uint32)ConfigPtr->Pull << ( i * 2 ) ) );

            /*change values on OTYPER*/
            Bfx_ClrBitMask_u32u32( (uint32 *)&port->OTYPER, ( 0x01 << ( i ) ) );
            Bfx_SetBitMask_u32u32( (uint32 *)&port->OTYPER, ( (uint32)ConfigPtr->OutputDrive << ( i ) ) );

            /*change values on OSPEEDR*/
            Bfx_ClrBitMask_u32u32( (uint32 *)&port->OSPEEDR, ( 0x03 << ( i * 2 ) ) );
            Bfx_SetBitMask_u32u32( (uint32 *)&port->OSPEEDR, ( (uint32)ConfigPtr->Speed << ( i * 2 ) ) );

            /*change values on MODER*/
            Bfx_ClrBitMask_u32u32( (uint32 *)&port->MODER, ( 0x03 << ( i * 2 ) ) );
            Bfx_SetBitMask_u32u32( (uint32 *)&port->MODER, ( (uint32)ConfigPtr->Mode << ( i * 2 ) ) );
            Bfx_ClrBitMask_u32u32( &port_moder[ ConfigPtr->Port ], ( 0x03 << ( i * 2 ) ) );
            Bfx_SetBitMask_u32u32( &port_moder[ ConfigPtr->Port ], ( (uint32)ConfigPtr->Mode << ( i * 2 ) ) );

            if( i < 8u )
            {
                /*change values on Altern*/
                Bfx_ClrBitMask_u32u32( (uint32 *)&port->AFRL, ( 0x0F << ( i * 4 ) ) );
                Bfx_SetBitMask_u32u32( (uint32 *)&port->AFRL, ( (uint32)ConfigPtr->Altern << ( i * 4 ) ) );
            }
            else
            {
                /*change values on Altern*/
                Bfx_ClrBitMask_u32u32( (uint32 *)&port->AFRH, ( 0x0F << ( i * 4 ) ) );
                Bfx_SetBitMask_u32u32( (uint32 *)&port->AFRH, ( (uint32)ConfigPtr->Altern << ( i * 4 ) ) );
            }
        }
        mask = mask << 1;
    }
}


void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    Port_RegisterType *port;

    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    if( ( port_direction_change[ Pin >> 4 ] & ( 1 << ( Pin & 0xFu ) ) ) != 0u )
    {
        switch( Direction )
        {
            case PORT_PIN_IN:
                /*change values on MODER*/
                Bfx_ClrBitMask_u32u32( (uint32 *)&port->MODER, ( 0x03 << ( ( Pin & 0xFu ) * 2 ) ) );
                Bfx_SetBitMask_u32u32( (uint32 *)&port->MODER, ( PORT_PIN_IN << ( ( Pin & 0xFu ) * 2 ) ) );
                break;

            case PORT_PIN_OUT:
                /*change values on MODER*/
                Bfx_ClrBitMask_u32u32( (uint32 *)&port->MODER, ( 0x03 << ( ( Pin & 0xFu ) * 2 ) ) );
                Bfx_SetBitMask_u32u32( (uint32 *)&port->MODER, ( PORT_PIN_OUT << ( ( Pin & 0xFu ) * 2 ) ) );
                break;
        }
    }
}

void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    Port_RegisterType *port;

    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    if( ( Pin & 0xFu ) < 8u )
    {
        /*change values on Altern*/
        Bfx_ClrBitMask_u32u32( (uint32 *)&port->AFRL, ( 0x0F << ( ( Pin & 0xFu ) * 4 ) ) );
        Bfx_SetBitMask_u32u32( (uint32 *)&port->AFRL, ( Mode << ( ( Pin & 0xFu ) * 4 ) ) );
    }
    else
    {
        /*change values on Altern*/
        Bfx_ClrBitMask_u32u32( (uint32 *)&port->AFRH, ( 0x0F << ( ( Pin & 0xFu ) * 4 ) ) );
        Bfx_SetBitMask_u32u32( (uint32 *)&port->AFRH, ( Mode << ( ( Pin & 0xFu ) * 4 ) ) );
    }
}

void Port_GetVersionInfo( Std_VersionInfoType *versioninfo )
{
    versioninfo->moduleID         = 0;
    versioninfo->sw_major_version = 0;
    versioninfo->sw_minor_version = 0;
    versioninfo->sw_patch_version = 0;
    versioninfo->vendorID         = 0;
}

void Port_RefreshPortDirection( void )
{
    PORTA->MODER = port_moder[ 0 ];
    PORTB->MODER = port_moder[ 1 ];
    PORTC->MODER = port_moder[ 2 ];
    PORTD->MODER = port_moder[ 3 ];
    PORTE->MODER = port_moder[ 4 ];
    PORTF->MODER = port_moder[ 5 ];
}