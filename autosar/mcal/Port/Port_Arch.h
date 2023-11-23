/**
 * @file    Port_Arch.h
 * @brief   **  **
 * @author  Enrique Ortega
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
#define PORTS_A               0u /*!< Port A value */
#define PORTS_B               1u /*!< Port B value */
#define PORTS_C               2u /*!< Port C value */
#define PORTS_D               3u /*!< Port D value */
#define PORTS_E               4u /*!< Port E value */
#define PORTS_F               5u /*!< Port F value */
/**
 * @} */

/**
 * @defgroup    PORTS_pins Pins values
 *
 * Symbols to specify the values of PORTS pins on any port, this needs to
 * be use in combination with ports when specify in Port_Cfg.h.
 *
 * @{ */
#define PORTS_PIN_00_VAL      0x0000u /*!< Pin 0 value */
#define PORTS_PIN_01_VAL      0x0001u /*!< Pin 1 value */
#define PORTS_PIN_02_VAL      0x0002u /*!< Pin 2 value */
#define PORTS_PIN_03_VAL      0x0003u /*!< Pin 3 value */
#define PORTS_PIN_04_VAL      0x0004u /*!< Pin 4 value */
#define PORTS_PIN_05_VAL      0x0005u /*!< Pin 5 value */
#define PORTS_PIN_06_VAL      0x0006u /*!< Pin 6 value */
#define PORTS_PIN_07_VAL      0x0007u /*!< Pin 7 value */
#define PORTS_PIN_08_VAL      0x0008u /*!< Pin 8 value */
#define PORTS_PIN_09_VAL      0x0009u /*!< Pin 9 value */
#define PORTS_PIN_10_VAL      0x000Au /*!< Pin 10 value */
#define PORTS_PIN_11_VAL      0x000Bu /*!< Pin 11 value */
#define PORTS_PIN_12_VAL      0x000Cu /*!< Pin 12 value */
#define PORTS_PIN_13_VAL      0x000Du /*!< Pin 13 value */
#define PORTS_PIN_14_VAL      0x000Eu /*!< Pin 14 value */
#define PORTS_PIN_15_VAL      0x000Fu /*!< Pin 15 value */
/**
 * @}*/

/**
 * @defgroup    PORTS_Pin Pins masks
 *
 * Symbols to specify values of PORT pins when use in combination into the
 * Port_ConfigType structure with or operations.
 *
 * @{ */
#define PORTS_PIN_00          ( 1u << PORTS_PIN_00_VAL ) /*!< Pin 0 value mask */
#define PORTS_PIN_01          ( 1u << PORTS_PIN_01_VAL ) /*!< Pin 1 value mask */
#define PORTS_PIN_02          ( 1u << PORTS_PIN_02_VAL ) /*!< Pin 2 value mask */
#define PORTS_PIN_03          ( 1u << PORTS_PIN_03_VAL ) /*!< Pin 3 value mask */
#define PORTS_PIN_04          ( 1u << PORTS_PIN_04_VAL ) /*!< Pin 4 value mask */
#define PORTS_PIN_05          ( 1u << PORTS_PIN_05_VAL ) /*!< Pin 5 value mask */
#define PORTS_PIN_06          ( 1u << PORTS_PIN_06_VAL ) /*!< Pin 6 value mask */
#define PORTS_PIN_07          ( 1u << PORTS_PIN_07_VAL ) /*!< Pin 7 value mask */
#define PORTS_PIN_08          ( 1u << PORTS_PIN_08_VAL ) /*!< Pin 8 value mask */
#define PORTS_PIN_09          ( 1u << PORTS_PIN_09_VAL ) /*!< Pin 9 value mask */
#define PORTS_PIN_10          ( 1u << PORTS_PIN_10_VAL ) /*!< Pin 10 value mask */
#define PORTS_PIN_11          ( 1u << PORTS_PIN_11_VAL ) /*!< Pin 11 value mask */
#define PORTS_PIN_12          ( 1u << PORTS_PIN_12_VAL ) /*!< Pin 12 value mask */
#define PORTS_PIN_13          ( 1u << PORTS_PIN_13_VAL ) /*!< Pin 13 value mask */
#define PORTS_PIN_14          ( 1u << PORTS_PIN_14_VAL ) /*!< Pin 14 value mask */
#define PORTS_PIN_15          ( 1u << PORTS_PIN_15_VAL ) /*!< Pin 15 value mask */
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
#define PORTS_MODE_INPUT      0x00u /*!< Input mode value */
#define PORTS_MODE_OUTPUT     0x10u /*!< General purpose output mode value */
#define PORTS_MODE_ANALOG     0x30u /*!< Analog mode (reset state) value */
#define PORTS_MODE_ALT_AF0    0x20u /*!< Alternarive funcion 0 */
#define PORTS_MODE_ALT_AF1    0x21u /*!< Alternarive funcion 1 */
#define PORTS_MODE_ALT_AF2    0x22u /*!< Alternarive funcion 2 */
#define PORTS_MODE_ALT_AF3    0x23u /*!< Alternarive funcion 3 */
#define PORTS_MODE_ALT_AF4    0x24u /*!< Alternarive funcion 4 */
#define PORTS_MODE_ALT_AF5    0x25u /*!< Alternarive funcion 5 */
#define PORTS_MODE_ALT_AF6    0x26u /*!< Alternarive funcion 6 */
#define PORTS_MODE_ALT_AF7    0x27u /*!< Alternarive funcion 7 */
#define PORTS_MODE_ALT_AF8    0x25u /*!< Alternarive funcion 5 */
#define PORTS_MODE_ALT_AF9    0x26u /*!< Alternarive funcion 6 */
#define PORTS_MODE_ALT_AF10   0x27u /*!< Alternarive funcion 7 */
/**
 * @}*/

/**
 * @defgroup    PORTS_pull pull resistors
 *
 * Symbols to specify the ressitor pull configuration on each pin
 *
 * @{ */
#define PORTS_NOPULL          0x00u /*!< No pull-up, pull-down value */
#define PORTS_PULLUP          0x01u /*!< Pull-up */
#define PORTS_PULLDOWN        0x02u /*!< Pull-down */
/**
 * @}*/

/**
 * @defgroup    PORTS_ouput_drive ouput drive values
 *
 * Symbols to specify the output drives modes
 *
 * @{ */
#define PORTS_PUSH_PULL       0x00u /*!< Output push-pull (reset state) value */
#define PORTS_OPEN_COLECTOR   0x01u /*!< Output open-drain */
/**
 * @} */

/**
 * @defgroup    PORTS_speeds port speeds
 *
 * Symbols to specify the Speed value of PORT pins on init function.
 *
 * @{ */
#define PORTS_VERY_LOW_SPEED  0x00u /*!< Very low speed value */
#define PORTS_LOW_SPEED       0x01u /*!< Low speed value */
#define PORTS_HIGH_SPEED      0x02u /*!< High speed value */
#define PORTS_VERY_HIGH_SPEED 0x03u /*!< Very high speed value */
/**
 * @} */

/**
 * @defgroup    PORTS_direction port directions
 *
 * Symbols to specify the direction of the GPIO pins
 *
 * @{ */
#define PORTS_PIN_IN          (Port_PinDirectionType)0x00u /*!< Input mode value */
#define PORTS_PIN_OUT         (Port_PinDirectionType)0x01u /*!< General purpose output mode value */
/**
 * @} */

/**
 * @defgroup max_port_values  max number of Mcu ports, pins and altern modes
 *
 * @{ */
#define MAX_PORT_NUMBER       6u  /*!< Max number of port in Mcu */
#define MAX_PIN_NUMBER        16u /*!< Max number of pins on each port*/
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_PIN_MODES         4u /*!< Max values on pin modes */
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_ALT_MODES         11u /*!< Max values on altern modes */
/**
 * @}*/

void Port_Arch_Init( const Port_ConfigType *ConfigPtr );
void Port_Arch_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
void Port_Arch_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
void Port_Arch_RefreshPortDirection( void );

#endif /* PORT_ARCH_H__ */