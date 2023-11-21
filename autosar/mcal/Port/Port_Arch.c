/**
 * @file    Port_Arch.c
 * @brief   **Port **
 * @author  Enrique Ortega
 *
 * This PORT driver module control the overall configuration and initialization of the port structure
 * which is used in the DIO driver module. Therefore, the DIO driver works on pins and ports which are
 * configured by the PORT driver.
 */
#include "Std_Types.h"
#include "Registers.h"
#include "Port_Types.h"
#include "Port_Arch.h"

/**
 * @defgroup bits  defines to replace magic numbers
 * @{*/
#define TWO_BITS             0x02u /*!< operation on two bits */
#define FOUR_BITS            0x04u /*!< operation on four bits */
/**
 * @}*/


/**
 * @defgroup mlu_factors  multiplication factors
 *
 * @{*/
#define MUL_BY_TWO           1u /*!< Multiply by two on a shift operation */
#define MUL_BY_FOUR          2u /*!< Multiply by four on a shift operation */
/**
 * @}*/

/**
 * @brief  Variable for the initial value of the port configuration array.
 */
static const Port_ConfigType *LocalConfigPtr = NULL_PTR;

/**
 * @brief Global port register array
 */
/* clang-format off */
static Port_RegisterType *Port_Ports[ MAX_PORT_NUMBER ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
/* clang-format on */


void Port_Arch_Init( const Port_ConfigType *ConfigPtr )
{
    Port_RegisterType *PortReg;

    for( uint8 Port = 0u; Port < PORT_PIN_NUMBER_OF_PORTS; Port++ )
    {
        PortReg = Port_Ports[ ConfigPtr[ Port ].Port ];

        for( uint8 Pin = 0u; Pin < MAX_PIN_NUMBER; Pin++ )
        {
            if( Bfx_GetBit_u16u8_u8( ConfigPtr[ Port ].Pins, Pin ) == TRUE )
            {
                /*change values on PUPDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->PUPDR, ( Pin << MUL_BY_TWO ), TWO_BITS, ConfigPtr[ Port ].Pull );
                /*change values on OTYPER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->OTYPER, Pin, 1u, ConfigPtr[ Port ].OutputDrive );
                /*change values on OSPEEDR*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->OSPEEDR, ( Pin << MUL_BY_TWO ), TWO_BITS, ConfigPtr[ Port ].Speed );
                /*change values on MODER*/
                Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( ConfigPtr[ Port ].Mode ) );

                if( Pin < PORTS_PIN_08_VAL )
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRL, ( Pin << MUL_BY_FOUR ), FOUR_BITS, GET_LOW_NIBBLE( ConfigPtr[ Port ].Mode ) );
                }
                else
                {
                    /*change values on Altern*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRH, ( ( Pin - PORTS_PIN_08_VAL ) << MUL_BY_FOUR ), FOUR_BITS, GET_LOW_NIBBLE( ConfigPtr[ Port ].Mode ) );
                }
            }
        }
    }
    /*make the port configuration accesible for other functions*/
    LocalConfigPtr = ConfigPtr;
}

void Port_Arch_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    Port_RegisterType *PortReg = Port_Ports[ LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].Port ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, GET_LOW_NIBBLE( Pin ), 2u, Direction );
}

void Port_Arch_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    Port_RegisterType *PortReg = Port_Ports[ LocalConfigPtr[ GET_HIGH_BYTE( Pin ) ].Port ];

    /*Set mode*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( Mode ) );

    if( GET_LOW_NIBBLE( Pin ) < PORTS_PIN_08_VAL )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRL, ( GET_LOW_NIBBLE( Pin ) << MUL_BY_FOUR ), FOUR_BITS, Mode );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRH, ( ( GET_LOW_NIBBLE( Pin ) - PORTS_PIN_08_VAL ) << MUL_BY_FOUR ), FOUR_BITS, Mode );
    }
}

void Port_Arch_RefreshPortDirection( void )
{
    Port_RegisterType *PortReg;

    for( uint8 Port = 0; Port < PORT_PIN_NUMBER_OF_PORTS; Port++ )
    {
        PortReg = Port_Ports[ LocalConfigPtr[ Port ].Port ];

        if( ( LocalConfigPtr[ Port ].DirChange == FALSE ) && ( ( LocalConfigPtr[ Port ].Mode == PORTS_MODE_INPUT ) || ( LocalConfigPtr[ Port ].Mode == PORTS_MODE_OUTPUT ) ) )
        {
            for( uint8 Pin = 0u; Pin < MAX_PIN_NUMBER; Pin++ )
            {
                if( Bfx_GetBit_u32u8_u8( LocalConfigPtr[ Port ].Pins, Pin ) == TRUE )
                {
                    /*change values on MODER*/
                    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( LocalConfigPtr[ Port ].Mode ) );
                }
            }
        }
    }
}