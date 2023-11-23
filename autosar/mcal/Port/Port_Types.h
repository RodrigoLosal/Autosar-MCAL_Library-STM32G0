/**
 * @file    Port_Types.h
 * @brief   **  **
 * @author  Enrique Ortega
 *
 * This PORT driver module control the overall configuration and initialization of the port structure
 * which is used in the DIO driver module. Therefore, the DIO driver works on pins and ports which are
 * configured by the PORT driver.
 */
#ifndef PORT_TYPES_H__
#define PORT_TYPES_H__

#include "Std_Types.h"

/**
 * @brief **Definition of the external data structure containing the initialization data**
 *
 * The Port_PortsConfigType data structure holds the initialization information for each port available
 * on the microcontroller. An array of these structures must be defined in the Port_Cfg.c file, with
 * each entry representing a specific port.
 *
 * @note It is the responsibility of the user to ensure that the values defined in this structure are
 * valid and appropriate, as the Port Driver does not perform any validation. The values must be generated
 * and validated within the code generation tool.
 *
 * @reqs   SWS_Port_00228
 */
typedef struct _Port_ConfigType
{
    uint8 Port;        /*!< Port where the pin to config is grouped*/
    uint16 Pins;       /*!< Pins to configured*/
    uint8 Pull;        /*!< Pullup, pull down or no pull ressitor*/
    uint8 OutputDrive; /*!< Pus-Pull or Open conlector*/
    uint8 Speed;       /*!< Speed of the pin*/
    uint8 Mode;        /*!< Input, Output, analog or any of the altern modes*/
    uint8 DirChange;   /*!< Pin direction changeable during runtime*/
    uint8 ModeChange;  /*!< Pin mode changeable during runtime*/
} Port_ConfigType;


/**
 * @brief  Data type for the symbolic name of a port pin. the 8 most significant
 *         bits represent the port of the pin and the 4 least significatn bits
 *         represent the pin.
 *
 * @reqs   SWS_Port_00229
 */
typedef uint16 Port_PinType; /*!< Data type for the symbolic name of a port pin.*/

/**
 * @brief  Data type for the symbolic direction of a pin.
 *         range: PORT_PIN_IN and PORT_PIN_OUT
 *
 * @reqs   SWS_Port_00046
 */
typedef uint8 Port_PinDirectionType; /*!< Data type for the symbolic direction of a pin.*/

/**
 * @brief  Data type for the altern functions of a pin.
 *         range: PORT_PIN_MODE_AF0, PORT_PIN_MODE_AF1, PORT_PIN_MODE_AF2, PORT_PIN_MODE_AF3,
 *         PORT_PIN_MODE_AF4, PORT_PIN_MODE_AF5, PORT_PIN_MODE_AF6, PORT_PIN_MODE_AF7 and
 *         PORT_PIN_MODE_AF8.
 *
 * @reqs   SWS_Port_00231
 */
typedef uint8 Port_PinModeType; /*!< Data type for the symbolic mode of a pin.*/

/**
 * @defgroup get_bits  macros to extract certaing number of bits from a variable
 *
 * @{*/
#define GET_LOW_NIBBLE( x )            ( (x)&0xFu )    /*!< get the less significant bits */
#define GET_HIGH_NIBBLE( x )           ( ( x ) >> 4u ) /*!< get the four most significant nibble */
#define GET_HIGH_BYTE( x )             ( ( x ) >> 8u ) /*!< get hte MSB from and 16 bit variable */
/**
 * @}*/

/**
 * @defgroup    PORTS_values. Port values
 *
 * The symbols are use to represent each port of the microcontroller
 *
 * @{ */
#define PORTS_A                        0u /*!< Port A value */
#define PORTS_B                        1u /*!< Port B value */
#define PORTS_C                        2u /*!< Port C value */
#define PORTS_D                        3u /*!< Port D value */
#define PORTS_E                        4u /*!< Port E value */
#define PORTS_F                        5u /*!< Port F value */
/**
 * @} */

/**
 * @defgroup    PORTS_pins Pins values
 *
 * Symbols to specify the values of PORTS pins on any port, this needs to
 * be use in combination with ports when specify in Port_Cfg.h.
 *
 * @{ */
#define PORTS_PIN_00_VAL               0x0000u /*!< Pin 0 value */
#define PORTS_PIN_01_VAL               0x0001u /*!< Pin 1 value */
#define PORTS_PIN_02_VAL               0x0002u /*!< Pin 2 value */
#define PORTS_PIN_03_VAL               0x0003u /*!< Pin 3 value */
#define PORTS_PIN_04_VAL               0x0004u /*!< Pin 4 value */
#define PORTS_PIN_05_VAL               0x0005u /*!< Pin 5 value */
#define PORTS_PIN_06_VAL               0x0006u /*!< Pin 6 value */
#define PORTS_PIN_07_VAL               0x0007u /*!< Pin 7 value */
#define PORTS_PIN_08_VAL               0x0008u /*!< Pin 8 value */
#define PORTS_PIN_09_VAL               0x0009u /*!< Pin 9 value */
#define PORTS_PIN_10_VAL               0x000Au /*!< Pin 10 value */
#define PORTS_PIN_11_VAL               0x000Bu /*!< Pin 11 value */
#define PORTS_PIN_12_VAL               0x000Cu /*!< Pin 12 value */
#define PORTS_PIN_13_VAL               0x000Du /*!< Pin 13 value */
#define PORTS_PIN_14_VAL               0x000Eu /*!< Pin 14 value */
#define PORTS_PIN_15_VAL               0x000Fu /*!< Pin 15 value */
/**
 * @}*/

/**
 * @defgroup    PORTS_Pin Pins masks
 *
 * Symbols to specify values of PORT pins when use in combination into the
 * Port_ConfigType structure with or operations.
 *
 * @{ */
#define PORTS_PIN_00                   ( 1u << PORTS_PIN_00_VAL ) /*!< Pin 0 value mask */
#define PORTS_PIN_01                   ( 1u << PORTS_PIN_01_VAL ) /*!< Pin 1 value mask */
#define PORTS_PIN_02                   ( 1u << PORTS_PIN_02_VAL ) /*!< Pin 2 value mask */
#define PORTS_PIN_03                   ( 1u << PORTS_PIN_03_VAL ) /*!< Pin 3 value mask */
#define PORTS_PIN_04                   ( 1u << PORTS_PIN_04_VAL ) /*!< Pin 4 value mask */
#define PORTS_PIN_05                   ( 1u << PORTS_PIN_05_VAL ) /*!< Pin 5 value mask */
#define PORTS_PIN_06                   ( 1u << PORTS_PIN_06_VAL ) /*!< Pin 6 value mask */
#define PORTS_PIN_07                   ( 1u << PORTS_PIN_07_VAL ) /*!< Pin 7 value mask */
#define PORTS_PIN_08                   ( 1u << PORTS_PIN_08_VAL ) /*!< Pin 8 value mask */
#define PORTS_PIN_09                   ( 1u << PORTS_PIN_09_VAL ) /*!< Pin 9 value mask */
#define PORTS_PIN_10                   ( 1u << PORTS_PIN_10_VAL ) /*!< Pin 10 value mask */
#define PORTS_PIN_11                   ( 1u << PORTS_PIN_11_VAL ) /*!< Pin 11 value mask */
#define PORTS_PIN_12                   ( 1u << PORTS_PIN_12_VAL ) /*!< Pin 12 value mask */
#define PORTS_PIN_13                   ( 1u << PORTS_PIN_13_VAL ) /*!< Pin 13 value mask */
#define PORTS_PIN_14                   ( 1u << PORTS_PIN_14_VAL ) /*!< Pin 14 value mask */
#define PORTS_PIN_15                   ( 1u << PORTS_PIN_15_VAL ) /*!< Pin 15 value mask */
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
#define PORTS_MODE_INPUT               0x00u /*!< Input mode value */
#define PORTS_MODE_OUTPUT              0x10u /*!< General purpose output mode value */
#define PORTS_MODE_ANALOG              0x30u /*!< Analog mode (reset state) value */
#define PORTS_MODE_ALT_AF0             0x20u /*!< Alternarive funcion 0 */
#define PORTS_MODE_ALT_AF1             0x21u /*!< Alternarive funcion 1 */
#define PORTS_MODE_ALT_AF2             0x22u /*!< Alternarive funcion 2 */
#define PORTS_MODE_ALT_AF3             0x23u /*!< Alternarive funcion 3 */
#define PORTS_MODE_ALT_AF4             0x24u /*!< Alternarive funcion 4 */
#define PORTS_MODE_ALT_AF5             0x25u /*!< Alternarive funcion 5 */
#define PORTS_MODE_ALT_AF6             0x26u /*!< Alternarive funcion 6 */
#define PORTS_MODE_ALT_AF7             0x27u /*!< Alternarive funcion 7 */
#define PORTS_MODE_ALT_AF8             0x25u /*!< Alternarive funcion 5 */
#define PORTS_MODE_ALT_AF9             0x26u /*!< Alternarive funcion 6 */
#define PORTS_MODE_ALT_AF10            0x27u /*!< Alternarive funcion 7 */
/**
 * @}*/

/**
 * @defgroup    PORTS_pull pull resistors
 *
 * Symbols to specify the ressitor pull configuration on each pin
 *
 * @{ */
#define PORTS_NOPULL                   0x00u /*!< No pull-up, pull-down value */
#define PORTS_PULLUP                   0x01u /*!< Pull-up */
#define PORTS_PULLDOWN                 0x02u /*!< Pull-down */
/**
 * @}*/

/**
 * @defgroup    PORTS_ouput_drive ouput drive values
 *
 * Symbols to specify the output drives modes
 *
 * @{ */
#define PORTS_PUSH_PULL                0x00u /*!< Output push-pull (reset state) value */
#define PORTS_OPEN_COLECTOR            0x01u /*!< Output open-drain */
/**
 * @} */

/**
 * @defgroup    PORTS_speeds port speeds
 *
 * Symbols to specify the Speed value of PORT pins on init function.
 *
 * @{ */
#define PORTS_VERY_LOW_SPEED           0x00u /*!< Very low speed value */
#define PORTS_LOW_SPEED                0x01u /*!< Low speed value */
#define PORTS_HIGH_SPEED               0x02u /*!< High speed value */
#define PORTS_VERY_HIGH_SPEED          0x03u /*!< Very high speed value */
/**
 * @} */

/**
 * @defgroup    PORTS_direction port directions
 *
 * Symbols to specify the direction of the GPIO pins
 *
 * @{ */
#define PORTS_PIN_IN                   (Port_PinDirectionType)0x00u /*!< Input mode value */
#define PORTS_PIN_OUT                  (Port_PinDirectionType)0x01u /*!< General purpose output mode value */
/**
 * @} */


/**
 * @defgroup max_port_values  max number of Mcu ports, pins and altern modes
 *
 * @{ */
#define MAX_PORT_NUMBER                6u  /*!< Max number of port in Mcu */
#define MAX_PIN_NUMBER                 16u /*!< Max number of pins on each port*/
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_PIN_MODES                  4u /*!< Max values on pin modes */
/* cppcheck-suppress misra-c2012-2.5 ; use when DET is active */
#define MAX_ALT_MODES                  11u /*!< Max values on altern modes */
/**
 * @}*/

/**
 * @defgroup PORT_errors Driver erros
 *
 * PORTS Driver Errors messages, this values are intended to use with DET functionality
 *
 * @{ */
#define PORT_E_PARAM_PIN               0x0Au /*!< Invalid Port Pin ID requested        */
#define PORT_E_DIRECTION_UNCHANGEABLE  0x0Bu /*!< Port Pin not configured as changeable */
#define PORT_E_INIT_FAILED             0x0Cu /*!< Invalid configuration set            */
#define PORT_E_PARAM_INVALID_MODE      0x0Du /*!< Invalid Port Pin mode specified      */
#define PORT_E_MODE_UNCHANGEABLE       0x0Eu /*!< Port Pin mode is not configurable    */
#define PORT_E_UNINIT                  0x0Fu /*!< Port driver not initialized          */
#define PORT_E_PARAM_POINTER           0x10u /*!< Invalid Port Pin ID requested        */
/**
 * @} */

/**
 * @defgroup PORT_Ids Can Id number for module and each API
 *
 * @{ */
#define PORT_ID_INIT                   0x00u /*!< Port_Init() api service id */
#define PORT_ID_SET_PIN_DIRECTION      0x10u /*!< Port_SetPinDirection() api service id */
#define PORT_ID_SET_PIN_MODE           0x0fu /*!< Port_SetPinMode() api service id */
#define PORT_ID_GET_VERSION_INFO       0x03u /*!< Port_GetVersionInfo() api service id */
#define PORT_ID_REFRESH_PORT_DIRECTION 0x04u /*!< Port_RefreshPortDirection() api service id */
/**
 * @} */

#endif /* PORT_TYPES_H__ */