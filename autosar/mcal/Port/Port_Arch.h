/**
 * @file    Port_Arch.h
 * @brief   **Port Specific Arquitecture Driver**
 * @author  Enrique Ortega, Diego Perez
 *
 * PORT driver implementation for the STM32G0xx family of microcontrollers. This file contains the
 * hardware specific implementation of the PORT driver. The file is implemented as a means of
 * abstraction from the hardware, this way we can avoid to include Arch headers in the actual
 * driver header, making the low level interfaces available only for the inmediate upper layer.
 */
#ifndef PORT_ARCH_H__
#define PORT_ARCH_H__

#include "Port_Types.h"

/**
 * @defgroup    PORTS_values. Port values
 *
 * The symbols are use to represent each port of the microcontroller
 *
 * @{ */
#define PORT_A               0u /*!< Port A value */
#define PORT_B               1u /*!< Port B value */
#define PORT_C               2u /*!< Port C value */
#define PORT_D               3u /*!< Port D value */
#define PORT_E               4u /*!< Port E value */
#define PORT_F               5u /*!< Port F value */
/**
 * @} */

/**
 * @defgroup get_bits  macros to extract certaing number of bits from a variable
 *
 * @{*/
#define GET_LOW_NIBBLE( x )  ( (x)&0xFu )    /*!< get the less significant bits */
#define GET_HIGH_NIBBLE( x ) ( ( x ) >> 4u ) /*!< get the four most significant nibble */
#define GET_HIGH_BYTE( x )   ( ( x ) >> 8u ) /*!< get hte MSB from and 16 bit variable */
/**
 * @}*/

/**
 * @defgroup    PORTS_mode Port modes
 *
 * Symbols to specify the mode value of PORT pins on init function and also
 * when use in Port_SetPinMode function. most significant nibble represent the mode
 * and less significant the altern mode
 *
 * @{ */
#define PORT_MODE_INPUT      0x00u /*!< Input mode value */
#define PORT_MODE_OUTPUT     0x10u /*!< General purpose output mode value */
#define PORT_MODE_ANALOG     0x30u /*!< Analog mode (reset state) value */
#define PORT_MODE_ALT_AF0    0x20u /*!< Alternarive funcion 0 */
#define PORT_MODE_ALT_AF1    0x21u /*!< Alternarive funcion 1 */
#define PORT_MODE_ALT_AF2    0x22u /*!< Alternarive funcion 2 */
#define PORT_MODE_ALT_AF3    0x23u /*!< Alternarive funcion 3 */
#define PORT_MODE_ALT_AF4    0x24u /*!< Alternarive funcion 4 */
#define PORT_MODE_ALT_AF5    0x25u /*!< Alternarive funcion 5 */
#define PORT_MODE_ALT_AF6    0x26u /*!< Alternarive funcion 6 */
#define PORT_MODE_ALT_AF7    0x27u /*!< Alternarive funcion 7 */
#define PORT_MODE_ALT_AF8    0x28u /*!< Alternarive funcion 8 */
#define PORT_MODE_ALT_AF9    0x29u /*!< Alternarive funcion 9 */
#define PORT_MODE_ALT_AF10   0x2Au /*!< Alternarive funcion 10 */
/**
 * @}*/

/**
 * @defgroup    PORTS_pull pull resistors
 *
 * Symbols to specify the ressitor pull configuration on each pin
 *
 * @{ */
#define PORT_NOPULL          0x00u /*!< No pull-up, pull-down value */
#define PORT_PULLUP          0x01u /*!< Pull-up */
#define PORT_PULLDOWN        0x02u /*!< Pull-down */
/**
 * @}*/

/**
 * @defgroup    PORTS_ouput_drive ouput drive values
 *
 * Symbols to specify the output drives modes
 *
 * @{ */
#define PORT_PUSH_PULL       0x00u /*!< Output push-pull (reset state) value */
#define PORT_OPEN_COLECTOR   0x01u /*!< Output open-drain */
/**
 * @} */

/**
 * @defgroup    PORTS_speeds port speeds
 *
 * Symbols to specify the Speed value of PORT pins on init function.
 *
 * @{ */
#define PORT_VERY_LOW_SPEED  0x00u /*!< Very low speed value */
#define PORT_LOW_SPEED       0x01u /*!< Low speed value */
#define PORT_HIGH_SPEED      0x02u /*!< High speed value */
#define PORT_VERY_HIGH_SPEED 0x03u /*!< Very high speed value */
/**
 * @} */

/**
 * @defgroup    PORTS_direction port directions
 *
 * Symbols to specify the direction of the GPIO pins
 *
 * @{ */
#define PORT_PIN_IN          0x00u /*!< Input mode value */
#define PORT_PIN_OUT         0x01u /*!< General purpose output mode value */
/**
 * @} */

void Port_Arch_Init( const Port_PinConfigType *PortConfigPtr );
void Port_Arch_SetPinDirection( const Port_PinConfigType *PortConfigPtr, Port_PinDirectionType Direction );
void Port_Arch_SetPinMode( const Port_PinConfigType *PortConfigPtr, uint8 PinMode, uint8 AltMode );
void Port_Arch_RefreshPortDirection( const Port_PinConfigType *PortConfigPtr );

#endif /* PORT_ARCH_H__ */