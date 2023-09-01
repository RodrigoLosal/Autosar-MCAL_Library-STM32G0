#include "Bfx.h"
#include "Std_Types.h"
#include "Port_Cfg.h"
#include "Registers.h"
#include "Port.h"

uint16 port_direction_change[ 6 ];

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
            Bfx_PutBits_u32u8u8u32( (uint32 *)&port->PUPDR, (uint8)(i*2u) , (uint8) 2u, (uint32)ConfigPtr->Pull);

            /*change values on OTYPER*/
            Bfx_PutBits_u32u8u8u32( (uint32 *)&port->OTYPER, i, 1, (uint32)ConfigPtr->OutputDrive );

            /*change values on OSPEEDR*/
            Bfx_PutBits_u32u8u8u32( (uint32 *)&port->OSPEEDR, ( i * 2 ), 2, (uint32)ConfigPtr->Speed );

            /*change values on MODER*/
            Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, ( i * 2 ), 2 , (uint32)ConfigPtr->Mode);

            if( i < 8u )
            {
                /*change values on Altern*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRL, ( i * 4 ), 4, (uint32)ConfigPtr->Altern );
            }
            else
            {
                /*change values on Altern*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRH, (i-8) * 4, 4, (uint32)ConfigPtr->Altern );
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

    Bfx_PutBits_u32u8u8u32( (uint32 *)&port->MODER, (uint8)(Pin & 0xFu), 2, (uint8)Direction );

}

void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    Port_RegisterType *port;

    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    if( ( Pin & 0xFu ) < 8u )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRL, ( Pin & 0xFu ), 4, (uint32) Mode );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&port->AFRH, ( (Pin & 0xFu)-8 ), 4, (uint32) Mode );
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