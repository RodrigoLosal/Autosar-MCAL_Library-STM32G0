#include "Port.h"

void Port_Init( const Port_ConfigType *ConfigPtr )
{
    Port_RegisterType *port;
    uint32 mask                   = 1u;
    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ ConfigPtr->Port ];

    for( uint32 i = 0u; i < 16u; i++ )
    {
        if( Bfx_TstBitLnMask_uint32_uint32( ConfigPtr->Pins, mask ) == TRUE )
        {
            /*change values on PUPDR*/
            Bfx_ClrBitMask_uint32_uint32( (uint32 *)&port->PUPDR, ( 0b11 << ( i * 2 ) ) );
            Bfx_SetBitMask_uint32_uint32( (uint32 *)&port->PUPDR, ( (uint32)ConfigPtr->Pull << ( i * 2 ) ) );

            /*change values on OTYPER*/
            Bfx_ClrBitMask_uint32_uint32( (uint32 *)&port->OTYPER, ( 0b1 << ( i ) ) );
            Bfx_SetBitMask_uint32_uint32( (uint32 *)&port->OTYPER, ( (uint32)ConfigPtr->OutputDrive << ( i ) ) );

            /*change values on OSPEEDR*/
            Bfx_ClrBitMask_uint32_uint32( (uint32 *)&port->OSPEEDR, ( 0b11 << ( i * 2 ) ) );
            Bfx_SetBitMask_uint32_uint32( (uint32 *)&port->OSPEEDR, ( (uint32)ConfigPtr->Speed << ( i * 2 ) ) );

            /*change values on MODER*/
            Bfx_ClrBitMask_uint32_uint32( (uint32 *)&port->MODER, ( 0b11 << ( i * 2 ) ) );
            Bfx_SetBitMask_uint32_uint32( (uint32 *)&port->MODER, ( (uint32)ConfigPtr->Mode << ( i * 2 ) ) );
        }
        mask = mask << 1;
    }
}


void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    Port_RegisterType *port;
    uint32 mask = 1u;

    Port_RegisterType *ports[ 6 ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
    port                          = ports[ Pin >> 4 ];

    switch( Direction )
    {
        case PORT_PIN_IN:
            /*change values on MODER*/
            Bfx_ClrBitMask_uint32_uint32( (uint32 *)&port->MODER, ( 0b11 << ( ( Pin & 0xFu ) * 2 ) ) );
            Bfx_SetBitMask_uint32_uint32( (uint32 *)&port->MODER, ( PORT_PIN_IN << ( ( Pin & 0xFu ) * 2 ) ) );
            break;

        case PORT_PIN_OUT:
            /*change values on MODER*/
            Bfx_ClrBitMask_uint32_uint32( (uint32 *)&port->MODER, ( 0b11 << ( ( Pin & 0xFu ) * 2 ) ) );
            Bfx_SetBitMask_uint32_uint32( (uint32 *)&port->MODER, ( PORT_PIN_OUT << ( ( Pin & 0xFu ) * 2 ) ) );
            break;
    }
}