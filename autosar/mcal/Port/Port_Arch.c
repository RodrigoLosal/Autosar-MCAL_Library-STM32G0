/**
 * @file    Port_Arch.c
 * @brief   **Port Specific Arquitecture Driver**
 * @author  Enrique Ortega, Diego Perez
 *
 * PORT driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the PORT driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#include "Std_Types.h"
#include "Port_Cfg.h"
#include "Port_Arch.h"
#include "Registers.h"
#include "Bfx.h"

/**
 * @defgroup bits  defines to replace magic numbers
 * @{*/
#define TWO_BITS    0x02u /*!< operation on two bits */
#define FOUR_BITS   0x04u /*!< operation on four bits */
#define PIN_08_VAL  0x08u /*!< value of pin 8 */
/**
 * @}*/

/**
 * @defgroup mlu_factors  multiplication factors
 *
 * @{*/
#define MUL_BY_TWO  1u /*!< Multiply by two on a shift operation */
#define MUL_BY_FOUR 2u /*!< Multiply by four on a shift operation */
/**
 * @}*/

/**
 * @brief Global port register array
 */
/* clang-format off */
static Port_RegisterType *PortPeripherals[ ] = { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF };
/* clang-format on */

/**
 * @brief Initialize the GPIO pins to the configuration store on ConfigPTR.
 *
 * This function changes the values of the registers depending on the ConfigPtr values.
 *
 * @param PortConfigPtr       Pointer to ConfigPtr struct array.
 *
 * @reqs   SWS_Port_00140
 */
void Port_Arch_Init( const Port_PinConfigType *PortConfigPtr )
{
    Port_RegisterType *PortReg = PortPeripherals[ PortConfigPtr->Port ];

    /*change values on PUPDR*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->PUPDR, ( PortConfigPtr->Pin << MUL_BY_TWO ), TWO_BITS, PortConfigPtr->Pull );
    /*change values on OTYPER*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->OTYPER, PortConfigPtr->Pin, 1u, PortConfigPtr->OutputDrive );
    /*change values on OSPEEDR*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->OSPEEDR, ( PortConfigPtr->Pin << MUL_BY_TWO ), TWO_BITS, PortConfigPtr->Speed );
    /*change values on MODER*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( PortConfigPtr->Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( PortConfigPtr->Mode ) );

    if( PortConfigPtr->Pin < PIN_08_VAL )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRL, ( PortConfigPtr->Pin << MUL_BY_FOUR ), FOUR_BITS, GET_LOW_NIBBLE( PortConfigPtr->Mode ) );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRH, ( ( PortConfigPtr->Pin - PIN_08_VAL ) << MUL_BY_FOUR ), FOUR_BITS, GET_LOW_NIBBLE( PortConfigPtr->Mode ) );
    }
}

/**
 * @brief Set the direction of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS direction during runtime.
 *
 * @param PortConfigPtr            Pointer for the port configuration value.
 * @param Direction       Direction to be changed.
 *
 * @reqs   SWS_Port_00141
 */
void Port_Arch_SetPinDirection( const Port_PinConfigType *PortConfigPtr, Port_PinDirectionType Direction )
{
    Port_RegisterType *PortReg = PortPeripherals[ PortConfigPtr->Port ];

    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, PortConfigPtr->Pin, TWO_BITS, Direction );
}

/**
 * @brief Set the mode of a GPIO during runtime.
 *
 * The function changes the registers values of the GPIOS mode during runtime.
 *
 * @param PortConfigPtr Pointer for the port configuration value.
 * @param PinMode       Pin Mode to be changed.
 * @param AltMode       Altern Mode to be changed.
 *
 * @reqs   SWS_Port_00145
 */
void Port_Arch_SetPinMode( const Port_PinConfigType *PortConfigPtr, uint8 PinMode, uint8 AltMode )
{
    Port_RegisterType *PortReg = PortPeripherals[ PortConfigPtr->Port ];

    /*Set mode*/
    Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( PortConfigPtr->Pin << MUL_BY_TWO ), TWO_BITS, PinMode );

    if( PortConfigPtr->Pin < PIN_08_VAL )
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRL, ( PortConfigPtr->Pin << MUL_BY_FOUR ), FOUR_BITS, AltMode );
    }
    else
    {
        /*change values on Altern*/
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->AFRH, ( ( PortConfigPtr->Pin - PIN_08_VAL ) << MUL_BY_FOUR ), FOUR_BITS, AltMode );
    }
}

/**
 * @brief Refresh port direction.
 *
 * The function refreshes the registers values of the GPIOS moder during runtime to the initial values
 * only if they are configured as non changeables.
 *
 * @param PortConfigPtr            Pointer for the port configuration value.
 *
 * @reqs   SWS_Port_00142
 */
void Port_Arch_RefreshPortDirection( const Port_PinConfigType *PortConfigPtr )
{
    Port_RegisterType *PortReg = PortPeripherals[ PortConfigPtr->Port ];

    if( ( PortConfigPtr->DirChange == FALSE ) && ( ( PortConfigPtr->Mode == PORT_MODE_INPUT ) || ( PortConfigPtr->Mode == PORT_MODE_OUTPUT ) ) )
    {
        Bfx_PutBits_u32u8u8u32( (uint32 *)&PortReg->MODER, ( PortConfigPtr->Pin << MUL_BY_TWO ), TWO_BITS, GET_HIGH_NIBBLE( PortConfigPtr->Mode ) );
    }
}
